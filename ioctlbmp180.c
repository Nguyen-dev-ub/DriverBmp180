#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_PATH "/dev/bmp180"
#define OSS 3

#define bmp180_ioctl_magic 'b'
#define bmp180_ioctl_nhietdo _IOR(bmp180_ioctl_magic,1, int)
#define bmp180_ioctl_apsuat _IOR(bmp180_ioctl_magic,2, int)
#define bmp180_ioctl_set_oss _IOW(bmp180_ioctl_magic,3, int) 

int main() {
    int fd;
    int data;
    int oss=OSS;
    // Mở thiết bị
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return errno;
    }
// Thiết lập OSS     
    if (ioctl(fd, bmp180_ioctl_set_oss, &oss) < 0) {
        perror("Failed to set OSS value");
        return errno;
    }

    if (ioctl(fd, bmp180_ioctl_nhietdo, &data) < 0) {
        perror("Failed to read temperature data");
        close(fd);
        return errno;
    }
    printf("The value of temperature is: %d (C)\n", data/10);

    if (ioctl(fd, bmp180_ioctl_apsuat, &data) < 0) {
        perror("Failed to read pressure data");
        close(fd);
        return errno;
    }  
    printf("The value of pressure is: %d (Pa)\n", data);

    // ĐÓng thiết bị
    close(fd);
    return 0;
}