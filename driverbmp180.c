//Tài liệu đi kèm:
//                  1.datasheet:    https://www.alldatasheet.com/datasheet-pdf/download/1132068/BOSCH/BMP180.html
//                  2.github:       https://github.com/torvalds/linux/blob/master/drivers/i2c/i2c-dev.c

//Thành viên thực hiện
//• Huỳnh Thị Thu Hà      -    22146299
//• Đinh Gia Khánh        -    22146330
//• Nguyễn Phương Nguyên  -    22146361

#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define bmp180_addr                 0x77 //địa chỉ bmp180 trên i2c
#define bmp180_reg_control          0xF4 //thanh ghi diều khiển 
#define bmp180_reg_temp_data        0xF6 //thanh ghi đo dữ liệu nhiệt độ
#define bmp180_reg_pressure_data    0xF6 //thanh ghi do du lieu áp suất
#define bmp180_cmd_temp             0x2E //yêu cầu đo nhiệt độ với thời gian tối đa là 4,5ms
#define bmp180_cmd_pressure         0x34 // oss = 0
#define oss                         0

#define DRIVER_NAME "bmp180_driver"


static struct i2c_client *bmp180_client;

//hàm đọc nhiệt độ va ap suat của bmp180
static int bmp180_doc_nhietdo_va_apsuat(struct i2c_client *client)
{
    int ret;
    u8 msb, lsb, xlsb;
    s16 nhietdo;    
    s32 apsuat;    

    // doc nhiet do
    ret = i2c_smbus_write_byte_data(client, bmp180_reg_control, bmp180_cmd_temp);
    if (ret < 0) {
        printk(KERN_ERR "bmp180: Failed to start temperature measurement \n");
        return ret;
    }

    msleep(5);  // thời gian chờ ít nhất 4,5ms

    msb = i2c_smbus_read_byte_data(client, bmp180_reg_temp_data);
    lsb = i2c_smbus_read_byte_data(client, bmp180_reg_temp_data + 1);
    if (msb < 0 || lsb < 0) {
        printk(KERN_ERR "bmp180: Failed to read temperature data\n");
        return -EIO;
    }

    nhietdo = (msb << 8) | lsb;
    printk(KERN_INFO "bmp180: Temperature is %d\n", nhietdo);

    // doc ap suat
    ret = i2c_smbus_write_byte_data(client, bmp180_reg_control, bmp180_cmd_pressure);
    if (ret < 0) {
        printk(KERN_ERR "bmp180: Failed to start pressure measurement\n");
        return ret;
    }

    msleep(5);  // Thoi gian cho it nhat 4,5ms

    msb = i2c_smbus_read_byte_data(client, bmp180_reg_pressure_data);
    lsb = i2c_smbus_read_byte_data(client, bmp180_reg_pressure_data + 1);
    xlsb = i2c_smbus_read_byte_data(client, bmp180_reg_pressure_data + 2);
    if (msb < 0 || lsb < 0 || xlsb < 0) {
        printk(KERN_ERR "bmp180: Failed to read pressure data\n");
        return -EIO;
    }

    apsuat = ((msb << 16) | (lsb << 8) | xlsb) >> (8 - oss);
    printk(KERN_INFO "bmp180: Pressure is %d\n", apsuat);

    return 0;}

//probe
static int bmp180_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret;

    bmp180_client = client;

    // doc du lieu nhiet do tu bmp180
    ret = bmp180_doc_nhietdo_va_apsuat(client);
    if (ret < 0) {
        return ret;
    }

    printk(KERN_INFO "bmp180 driver installed\n");

    return 0;
}

//remove
static void bmp180_remove(struct i2c_client *client)
{
    printk(KERN_INFO "bmp180 driver removed \n");
}

static const struct i2c_device_id bmp180_id[] = {
    { "bmp180", 0 },
    { }
};

MODULE_DEVICE_TABLE(i2c, bmp180_id);

//Ham dinh nghia struct driver
static struct i2c_driver bmp180_driver = {
    .driver = {
        .name   = DRIVER_NAME,
        .owner  = THIS_MODULE,
    },
    .probe      = bmp180_probe,
    .remove     = bmp180_remove, 
    .id_table   = bmp180_id,
};

//load module
static int __init bmp180_init(void)
{
    printk(KERN_INFO "Initializing bmp180 driver\n");
    return i2c_add_driver(&bmp180_driver);}

//remove module
static void __exit bmp180_exit(void)
{
    printk(KERN_INFO "Exiting bmp180 driver\n");
    i2c_del_driver(&bmp180_driver);
}
module_init(bmp180_init);
module_exit(bmp180_exit);

MODULE_AUTHOR("Huynh Thi Thu Ha, Dinh Gia Khanh, Nguyen Phuong Nguyen");
MODULE_DESCRIPTION("bmp180 I2C Client Driver with IOCTL Interface");
MODULE_LICENSE("GPL");