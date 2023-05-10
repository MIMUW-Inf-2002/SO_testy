//& Autor: Igor Kamiński`
#include <unistd.h>
#include "common.h"

int sender_end_of_money(pid_t recipient) {
    errno = 0;
    int balance = transfermoney(recipient, 1);
    if (errno != EINVAL) {
        printf("Account balanace cannot be less than 0\n");
        printf("Expected balance to be -1, but it is: %d\n", balance);
        return 0;
    }

    return 1;
}