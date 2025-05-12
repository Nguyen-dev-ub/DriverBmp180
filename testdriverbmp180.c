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