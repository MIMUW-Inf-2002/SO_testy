//& Autor: Igor Kamiński
#include <unistd.h>
#include "common.h"

int related_recipient(pid_t related_pid) {
    errno = 0;
    int balance = transfermoney(related_pid, 0);

    if (errno == EPERM)
        return 1;
    
    printf("Expected: %d\nBut errno is: %d\n", EPERM, errno);
    return 0;
}