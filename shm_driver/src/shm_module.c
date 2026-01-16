/**
 * This is a kernel module to implement shared memory IPC
 */

#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <shm_common.h>
#include <shm_error.h>
#include <shm_utils.h>

/* global driver context */
drv_ctx shm_drv_ctx = {
    .dev_minor_start = DEVICE_MINOR_BEGIN,
    .num_devs = DEVICES_NUM,
};

/* shm_drv_ops routines */
struct file_operations shm_fops = {
    .open = shm_drv_open,
    .read = shm_drv_read,
    .write = shm_drv_write,
    .release = shm_drv_release,
    .owner = THIS_MODULE,
    .unlocked_ioctl = shm_drv_ioctl,
};

int shm_drv_open(struct inode *filenode, struct file *f_object)
{
    printk(KERN_INFO "Shm driver file opened\n");
    return SHM_SUCCESS;
}

ssize_t shm_drv_read(struct file *f_object, char __user *usr_buff, size_t usr_bsize, loff_t *usr_ofst)
{
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

long shm_drv_ioctl(struct file *f_object, unsigned int shm_cmd_id, unsigned long shm_arg)
{
    printk(KERN_INFO "Shm driver IOCTL cmd-id: [%d] \n", shm_cmd_id);
    return SHM_SUCCESS;
}
static int __init shm_init(void)
{
    printk(KERN_INFO "shm init triggered\n");
    int ret = SHM_SUCCESS;
    /* allocate per device ctx memory in kernel heap */
    shm_drv_ctx.dv_ctx = (devInfo *)kmalloc(sizeof(devInfo) * shm_drv_ctx.num_devs, GFP_KERNEL);
    if (!shm_drv_ctx.dv_ctx)
    {
        /* kmalloc error handle it */
        printk(KERN_ERR "failed to allocate memory for device context exiting ..");
        ret = -ENOMEM;
        goto exit;
    }

    ret = alloc_chrdev_region(&shm_drv_ctx.dev_num, shm_drv_ctx.dev_minor_start, shm_drv_ctx.num_devs, DRV_NAME);
    if (ret)
    {
        printk(KERN_INFO "alloc_chrdev_region failed ret: %d\n", ret);
        goto exit;
    }
    printk(KERN_INFO
           "char dev allocation successful Major: %d - Minor begin: %d - num "
           "devices: %d\n",
           MAJOR(shm_drv_ctx.dev_num), MINOR(shm_drv_ctx.dev_num), shm_drv_ctx.num_devs);
    // create device file and class
    shm_drv_ctx.shm_dev_cls = class_create(SHM_DRV_CLS_NAME);
    if (IS_ERR(shm_drv_ctx.shm_dev_cls))
    {
        printk(KERN_ERR "failed to create shm drv class");
        goto unregister_chrdev;
    }
    // initialize cdev for per device
    dev_t curr_dev_num;
    for (int8_t i = 0; i < shm_drv_ctx.num_devs; i++)
    {
        cdev_init(&shm_drv_ctx.dv_ctx[i].shm_cdev, &shm_fops);
        shm_drv_ctx.dv_ctx[i].shm_cdev.owner = THIS_MODULE;
        curr_dev_num = MKDEV(MAJOR(shm_drv_ctx.dev_num),
                             MINOR(shm_drv_ctx.dev_num) + i);
        ret = cdev_add(&shm_drv_ctx.dv_ctx[i].shm_cdev, curr_dev_num, 1);
        if (ret)
        {
            printk(KERN_INFO "cdev_add failed ret: %d\n", ret);
            goto unregister_chrdev;
        }
        /* create a device node for each device */
        device_create(shm_drv_ctx.shm_dev_cls,
                      NULL,
                      curr_dev_num,
                      NULL,
                      DEV_NAME "%d", i); /* dev_name[0 ... n]*/
        printk(KERN_INFO "device file created: %s\n", DEV_NAME);
    }

exit:
    return ret;
unregister_chrdev:
    unregister_chrdev_region(shm_drv_ctx.dev_num, shm_drv_ctx.num_devs);
    return ret;
}

void __exit shm_deinit(void)
{
    printk(KERN_INFO "shm de-init triggered\n");
    // de-register the devices
    for (int8_t i = 0; i < shm_drv_ctx.num_devs; i++)
    {
        device_destroy(shm_drv_ctx.shm_dev_cls,
                        MKDEV(MAJOR(shm_drv_ctx.dev_num),
                        MINOR(shm_drv_ctx.dev_num) + i));
        cdev_del(&shm_drv_ctx.dv_ctx[i].shm_cdev);
    }
    class_destroy(shm_drv_ctx.shm_dev_cls);
    unregister_chrdev_region(shm_drv_ctx.dev_num, shm_drv_ctx.num_devs);
    return;
}

module_init(shm_init);
module_exit(shm_deinit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Venu Gopal Atchyutanna <venu.ark.prasad@gmail.com>");
MODULE_VERSION("0.1");