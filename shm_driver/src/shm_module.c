/**
 * This is a kernel module to implement shared memory IPC
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <shm_utils.h>
#include <shm_error.h>
#include <shm_common.h>
/* shm_drv_ops routines */
struct file_operations shm_fops = {
    .open = shm_drv_open,
    .read = shm_drv_read,
    .write = shm_drv_write,
    .release = shm_drv_release,
    .owner = THIS_MODULE,
    .unlocked_ioctl = shm_drv_ioctl,
};

int shm_drv_open(struct inode *filenode, struct file *f_object) {
    printk(KERN_INFO "Shm driver file opened\n");
    return SHM_SUCCESS;
}

ssize_t shm_drv_read(struct file *f_object, char __user * usr_buff, size_t usr_bsize, loff_t * usr_ofst) {
    printk(KERN_INFO "Shm driver read triggered");
    return SHM_SUCCESS;
}

ssize_t shm_drv_write(struct file *f_object, const char __user *usr_buff, size_t usr_bsize, loff_t *usr_ofst)
{
    printk(KERN_INFO "Shm driver write triggered\n");
    return SHM_SUCCESS;
}

int shm_drv_release(struct inode *file_inode, struct file *f_object)
{
    printk(KERN_INFO "Shm driver relased\n");
    return SHM_SUCCESS;
}

long shm_drv_ioctl(struct file *f_object, unsigned int shm_cmd_id, unsigned long shm_arg){
    printk(KERN_INFO "Shm driver IOCTL cmd-id: [%d] \n", shm_cmd_id);
    return SHM_SUCCESS;
}
static int __init shm_init(void) {
    printk(KERN_INFO "shm init triggered\n");
    return SHM_SUCCESS;
}

void __exit shm_deinit(void) {
    printk(KERN_INFO "shm de-init triggered\n");
    return;
}

module_init(shm_init);
module_exit(shm_deinit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Venu Gopal Atchyutanna <venu.ark.prasad@gmail.com>");
MODULE_VERSION("0.1");