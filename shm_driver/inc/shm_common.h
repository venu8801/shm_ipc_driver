/**
 * Header file for:
 * driver routine signatures
 * required structures
 * 
 * 
 */

ssize_t shm_drv_read(struct file *, char __user *, size_t, loff_t *);
ssize_t shm_drv_write(struct file *, const char __user *, size_t, loff_t *);
int shm_drv_open(struct inode *, struct file *);
int shm_drv_release(struct inode *, struct file *);
long shm_drv_ioctl(struct file *, unsigned int, unsigned long);
void shm_deinit(void);
static int shm_init(void);