/**
 * Header file for:
 * driver routine signatures
 * required structures
 * 
 * 
 */



/**
 * this driver was written to scale it to multiple devices
 * so the userspace can connect many apps to perform IPC
 */
#define DEVICE_MINOR_BEGIN 0  /* first minor num */
#define DEVICES_NUM 1         /* num of devices this driver handles */

#define DRV_NAME "shm_driver_venus"

#define SHM_DRV_CLS_NAME "shm_drv_class"

#define DEV_NAME "shm_drv_dev"

typedef struct device_info {
    unsigned int dminor;
    struct cdev shm_cdev;
    /* per device members to be added */
} devInfo;

typedef struct {
    devInfo *dv_ctx;                /* pointer to the per dev ctx array */
    unsigned int dev_minor_start;  /* first device start */
    unsigned int num_devs;         /* num of devices */
    struct class *shm_dev_cls;     /* device class common to all devs*/
    dev_t dev_num;                 /* device number MAJOR + MINOR */
} drv_ctx;

ssize_t shm_drv_read(struct file *, char __user *, size_t, loff_t *);
ssize_t shm_drv_write(struct file *, const char __user *, size_t, loff_t *);
int shm_drv_open(struct inode *, struct file *);
int shm_drv_release(struct inode *, struct file *);
long shm_drv_ioctl(struct file *, unsigned int, unsigned long);
void shm_deinit(void);
static int shm_init(void);