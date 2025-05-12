//Tài liệu đi kèm:
//                  1.datasheet:    https://www.alldatasheet.com/datasheet-pdf/download/1132068/BOSCH/BMP180.html
//                  2.github:       https://github.com/torvalds/linux/blob/master/drivers/i2c/i2c-dev.c

//Thành viên thực hiện
//• Huỳnh Thị Thu Hà      -    22146299
//• Đinh Gia Khánh        -    22146330
//• Nguyễn Phương Nguyên  -    22146361

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h> // Include errno header

#define DEVICE "/dev/i2c-1"

int main()
{
    int fd;

    printf("opem bmp180 device \n");
    fd = open(DEVICE, O_RDWR);
    if (fd < 0) {
        perror("Failed to open bmp180 device");
        return EXIT_FAILURE;
    }   
    printf("bmp180 device opened successfully \n");
    close(fd);
    printf("bmp180 device closed \n");
    return EXIT_SUCCESS;
}