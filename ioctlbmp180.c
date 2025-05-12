//Tai lieu di kem:
//                  1.datasheet:    https://www.alldatasheet.com/datasheet-pdf/download/1132068/BOSCH/BMP180.html
//                  2.github:       https://github.com/torvalds/linux/blob/master/drivers/i2c/i2c-dev.c

//Thanh vien nhom:  Huynh Thi Thu Ha        22146299
//                  Dinh Gia Khanh          22146330
//                  Nguyen Phuong Nguyen    22146361

#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DRIVER_NAME "bmp180_driver"
#define CLASS_NAME "bmp180"
#define DEVICE_NAME "bmp180"

#define BMP180_ADDR 0x77

#define BMP180_REG_CONTROL 0xF4
#define BMP180_REG_TEMP 0x2E
#define BMP180_REG_PRESSURE 0x34
#define BMP180_REG_RESULT 0xF6

#define BMP180_IOCTL_MAGIC 'b'
#define BMP180_IOCTL_READ_TEMP _IOR(BMP180_IOCTL_MAGIC, 1, int)
#define BMP180_IOCTL_READ_PRESS _IOR(BMP180_IOCTL_MAGIC, 2, int)

static struct i2c_client *bmp180_client;
static int major_number;
static struct class* bmp180_class = NULL;
static struct device* bmp180_device = NULL;

static int bmp180_read_temp(void) {
    int msb, lsb, temp;

    i2c_smbus_write_byte_data(bmp180_client, BMP180_REG_CONTROL, BMP180_REG_TEMP);
    msleep(5); // Chờ đo

    msb = i2c_smbus_read_byte_data(bmp180_client, BMP180_REG_RESULT);
    lsb = i2c_smbus_read_byte_data(bmp180_client, BMP180_REG_RESULT + 1);

    temp = (msb << 8) | lsb;
    return temp;
}

static int bmp180_read_pressure(void) {
    int msb, lsb, xlsb, pressure;

    i2c_smbus_write_byte_data(bmp180_client, BMP180_REG_CONTROL, BMP180_REG_PRESSURE);
    msleep(8); // Chờ đo

    msb = i2c_smbus_read_byte_data(bmp180_client, BMP180_REG_RESULT);
    lsb = i2c_smbus_read_byte_data(bmp180_client, BMP180_REG_RESULT + 1);
    xlsb = i2c_smbus_read_byte_data(bmp180_client, BMP180_REG_RESULT + 2);

    pressure = ((msb << 16) + (lsb << 8) + xlsb) >> 8;
    return pressure;
}

static long bmp180_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    int val;

    switch (cmd) {
        case BMP180_IOCTL_READ_TEMP:
            val = bmp180_read_temp();
            break;
        case BMP180_IOCTL_READ_PRESS:
            val = bmp180_read_pressure();
            break;
        default:
            return -EINVAL;
    }

    if (copy_to_user((int __user *)arg, &val, sizeof(val)))
        return -EFAULT;

    return 0;
}

static int bmp180_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "BMP180 opened\n");
    return 0;
}

static int bmp180_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "BMP180 closed\n");
    return 0;
}

static struct file_operations fops = {
    .open = bmp180_open,
    .release = bmp180_release,
    .unlocked_ioctl = bmp180_ioctl,
};

static int bmp180_probe(struct i2c_client *client, const struct i2c_device_id *id) {
    bmp180_client = client;

    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) return major_number;

    bmp180_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(bmp180_class)) return PTR_ERR(bmp180_class);

    bmp180_device = device_create(bmp180_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(bmp180_device)) return PTR_ERR(bmp180_device);

    printk(KERN_INFO "BMP180 driver probed\n");
    return 0;
}

static void bmp180_remove(struct i2c_client *client) {
    device_destroy(bmp180_class, MKDEV(major_number, 0));
    class_destroy(bmp180_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "BMP180 driver removed\n");
}

static const struct i2c_device_id bmp180_id[] = {
    { "bmp180", 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, bmp180_id);

static struct i2c_driver bmp180_driver = {
    .driver = {
        .name = DRIVER_NAME,
        .owner = THIS_MODULE,
    },
    .probe = bmp180_probe,
    .remove = bmp180_remove,
    .id_table = bmp180_id,
};

module_i2c_driver(bmp180_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("BMP180 I2C Driver with IOCTL");
