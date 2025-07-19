#ifndef _MY_IOCTL_H_
#define _MY_IOCTL_H_

#define MY_MAGIC 'M'
#define IOCTL_ADD_ONE _IOWR(MY_MAGIC, 0, struct my_data)

struct my_data {
    int value;
};

#endif

