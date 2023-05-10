//& Autor: Igor Kamiński
#include <unistd.h>
#include "common.h"

int recipient_too_much_money(pid_t pid) {
    errno = 0;
    int balance = transfermoney(pid, 100);
    if (errno != EINVAL) {
        printf("Recipient balance cannot exceed 1000\n");
        return 0;
    }

    return 1;
}