#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include "my_ioctl.h"

#define DEVICE_NAME "mydev"

static int major;
static struct class *my_class;
static struct cdev my_cdev;

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    struct my_data data;

    if (_IOC_TYPE(cmd) != MY_MAGIC) return -ENOTTY;
    if (_IOC_NR(cmd) > 1) return -ENOTTY;

    switch (cmd) {
        case IOCTL_ADD_ONE:
            if (copy_from_user(&data, (void __user *)arg, sizeof(data)))
                return -EFAULT;

            data.value += 1;

            if (copy_to_user((void __user *)arg, &data, sizeof(data)))
                return -EFAULT;

            return 0;
    }
    return -EINVAL;
}

static int my_open(struct inode *inode, struct file *file) {
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    return 0;
}

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .unlocked_ioctl = my_ioctl,
};

static int __init my_init(void) {
    dev_t dev;

    alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    major = MAJOR(dev);

    cdev_init(&my_cdev, &fops);
    cdev_add(&my_cdev, dev, 1);

    my_class = class_create(DEVICE_NAME);
    device_create(my_class, NULL, dev, NULL, DEVICE_NAME);

    printk(KERN_INFO "mydev loaded\n");
    return 0;
}

static void __exit my_exit(void) {
    dev_t dev = MKDEV(major, 0);
    device_destroy(my_class, dev);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "mydev unloaded\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");

