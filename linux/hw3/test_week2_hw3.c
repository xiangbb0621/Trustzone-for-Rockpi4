#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define __NR_week2_add_one 501

int main() {
    int val = 5;
    long ret = syscall(__NR_week2_add_one, val);
    if (ret == -1) {
        perror("syscall failed");
        return 1;
    }
    printf("Result from week2_add_one(%d): %ld\n", val, ret);
    return 0;
}

