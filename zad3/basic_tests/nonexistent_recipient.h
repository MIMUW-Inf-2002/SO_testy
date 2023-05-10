//& Autor: Igor Kamiński
#include <unistd.h>
#include "common.h"

#define AMOUNT 0

int test_invalid_pid(pid_t invalid_pid) {
    int balance = transfermoney(invalid_pid, AMOUNT);

    if (errno == ESRCH)
        return 1;
    
    printf("Expected: %d\nBut errno is: %d\n", ESRCH, errno);
    return 0;
}

int nonexistent_recipient(pid_t recipient) {
    errno = 0;
    if (!test_invalid_pid(recipient)) {
        printf("Failed child pid\n");
        return 0;
    }
    if (!test_invalid_pid(1234567)) {
        printf("Failed 1234567\n");
        return 0;
    }
    if (!test_invalid_pid(2147483647)) {
        printf("Failed MAX INT\n");
        return 0;
    }
    if (!test_invalid_pid(-2147483648)) {
        printf("Failed MIN INT\n");
        return 0;
    }
    if (!test_invalid_pid(-1)) {
        printf("Failed -1\n");
        return 0;
    }
    if (!test_invalid_pid(-2)) {
        printf("Failed -2\n");
        return 0;
    }
    if (!test_invalid_pid(-3)) {
        printf("Failed -3\n");
        return 0;
    }
    if (!test_invalid_pid(-4)) {
        printf("Failed -4\n");
        return 0;
    }

    return 1;
}