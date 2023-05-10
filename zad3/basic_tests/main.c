//& Autor: Igor Kamiński

#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "negative_amount.h"
#include "nonexistent_recipient.h"
#include "normal_transfers.h"
#include "recipient_too_much_money.h"
#include "related_recipient.h"
#include "sender_end_of_money.h"

//? Dead process
void child_process_1() {
    //? Exiting instantly to free the pid
    exit(0);
}

//? Only waits for transfers
void child_process_2(pid_t pid) {
    //! Querying parent (related)
    if (related_recipient(pid)) {
        printf("CHILD: Related processes passed!\n\n");
    } else {
        printf("CHILD: Related processes failed\n\n");
    }

    //? Waiting, to allow child3 to query this process
    //! You might need to increase this value
    sleep(2);
    exit(0);
}

//? Sends credits to child2
void child_process_3(pid_t pid) {
    //! Querying with negative amounts
    if (negative_amount(pid)) {
        printf("CHILD: Negative amount passed!\n\n");
    } else {
        printf("CHILD: Negative amount failed\n\n");
    }

    //! Transferring all money to child2 (not related)
    if (normal_transfers(pid)) {
        printf("CHILD: Normal transfers passed!\n\n");
    } else {
        printf("CHILD: Normal transfers failed\n\n");
    }

    //! Trying to transfer more money to child2 (current balance is 0)
    if (sender_end_of_money(pid)) {
        printf("CHILD: End of money passed!\n\n");
    } else {
        printf("CHILD: End of money failed\n\n");
    }
    exit(0);
}

//? Receives money until it reaches MAX_BALANCE
void child_receiver() {
    //? Waiting, to allow senders to query this process
    //! You might need to increase this value
    sleep(3);
    exit(0);
}

//? Sends money to receiver until it reaches MAX_BALANCE
void child_sender_OK(pid_t receiver) {
    //? Transfering all the money to receiver
    errno = 0;
    int balance = transfermoney(receiver, 100);
    if (errno != 0) {
        printf("CHILD: Unexpected errno error\n");
    }
    if (balance != 0) {
        printf("CHILD: Too much money sender_OK - Expected the balance to be 0\n");
    }
    exit(0);
}

//? Last sender will send money to child that has MAX_BALANCE credits
void child_sender_ERR(pid_t receiver) {
    //! Querying receiver (MAX_BALANCE)
    if (recipient_too_much_money(receiver)) {
        printf("CHILD: Too much money passed!\n\n");
    } else {
        printf("CHILD: Too much money failed\n\n");
    }
    exit(0);
}

int main() {
    pid_t pid1, pid2, pid3, pid4;

    //? First child
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        return 0;
    } else if (pid1 == 0) {
        child_process_1();
    }

    //? Second child
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        return 1;
    } else if (pid2 == 0) {
        child_process_2(getppid());
    }

    //? Third child
    pid3 = fork();
    if (pid3 < 0) {
        perror("fork");
        return 1;
    } else if (pid3 == 0) {
        child_process_3(pid2);
    }

    //? Parent process
    //? Waiting for the first child to terminate
    wait(NULL);

    //! Querying child1 (dead)
    if (nonexistent_recipient(pid1)) {
        printf("PARENT: Nonexistent recipient passed!\n\n");
    } else {
        printf("PARENT: Nonexistent recipient failed\n\n");
    }

    //! Querying child2 (related)
    if (related_recipient(pid2)) {
        printf("PARENT: Related processes passed!\n\n");
    } else {
        printf("PARENT: Related processes failed\n\n");
    }  

    //? Waiting for all the tests to pass to perform too much money tests
    wait(NULL);
    wait(NULL);

    //? Too much money tests
    //? Creating receiver
    pid_t receiver;
    receiver = fork();
    if (receiver < 0) {
        perror("fork");
        return 1;
    } else if (receiver == 0) {
        child_receiver();
    }

    //? Creating OK senders
    pid_t sender_OK;
    for (int i = 0; i < 9; i++) {
        sender_OK = fork();
        if (sender_OK < 0) {
            perror("fork");
            return 1;
        } else if (sender_OK == 0) {
            child_sender_OK(receiver);
        }
    }

    //? Creating ERR sender
    pid_t sender_ERR;
    sender_ERR = fork();
    if (sender_ERR < 0) {
        perror("fork");
        return 1;
    } else if (sender_ERR == 0) {
        child_sender_ERR(receiver);
    }

    for (int i = 0; i < 11; i++) {
        wait(NULL);
    }
    printf("Tests ended :]\n");

    return 0;
}