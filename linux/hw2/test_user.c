#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "my_ioctl.h"

int main() {
    int fd = open("/dev/mydev", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct my_data data = { .value = 42 };

    if (ioctl(fd, IOCTL_ADD_ONE, &data) == -1) {
        perror("ioctl");
        close(fd);
        return 1;
    }

    printf("Received value: %d\n", data.value);
    close(fd);
    return 0;
}

