/**
 * Header file for:
 * driver routine signatures
 * required structures
 * 
 * 
 */


#define DEVICE_MINOR_BEGIN 0
#define DEVICES_NUM 1

#define DRV_NAME "shm_driver_venus"

typedef struct device_info {
    dev_t dev_num;
    unsigned int dev_minor_start;
    unsigned int num_devs;
    struct cdev shm_cdev;
}devInfo;

ssize_t shm_drv_read(struct file *, char __user *, size_t, loff_t *);
ssize_t shm_drv_write(struct file *, const char __user *, size_t, loff_t *);
int shm_drv_open(struct inode *, struct file *);
int shm_drv_release(struct inode *, struct file *);
long shm_drv_ioctl(struct file *, unsigned int, unsigned long);
void shm_deinit(void);
static int shm_init(void);