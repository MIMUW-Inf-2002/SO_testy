//& Autor: Igor Kamiński
#include <unistd.h>
#include "common.h"

int test_negative_amount(pid_t invalid_pid, int amount) {
    int balance = transfermoney(invalid_pid, amount);

    if (errno == EINVAL)
        return 1;
    
    printf("Expected: %d\nBut errno is: %d\n", EINVAL, errno);
    return 0;
}

int negative_amount(pid_t recipient) {
    errno = 0;
    if (!test_negative_amount(recipient, -1)) {
        printf("Failed amount -1\n");
        return 0;
    }
    if (!test_negative_amount(recipient, -2147483648)) {
        printf("Failed amount MIN INT\n");
        return 0;
    }

    return 1;
}