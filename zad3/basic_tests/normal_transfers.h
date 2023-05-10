#include <unistd.h>
#include "common.h"

int update_balance(pid_t pid, int amount) {
    errno = 0;
    int balance = transfermoney(pid, amount);
    if (errno != 0)
        return -1;
    
    return balance;
}

int check_balance(int balance) {
    if (balance == -1)
        return 0;
    return 1;
}

int normal_transfers(pid_t recipient) {
    errno = 0;
    int balance = update_balance(getpid(), 0);
    if (balance != 100) {
        printf("Initial money balance should be 100, but it's:%d\n", balance);
        return 0;
    }
    if (!check_balance(balance)) {
        printf("Unexpected failure during normal transfer\n");
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        balance = update_balance(recipient, 10);
        if (!check_balance(balance)) {
            printf("Unexpected failure\n");
            return 0;
        }
    }

    if (balance != 0) {
        printf("Balance should be 0 by the end of this test, but it's: %d\n", balance);
        return 0;
    }

    return 1;
}