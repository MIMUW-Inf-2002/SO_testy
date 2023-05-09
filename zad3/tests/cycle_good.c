///
///
/// DISCLAIMER: The test has NOT been checked yet.
///             It may be flawed.
///
///

#include <unistd.h>     // fork(2), transfermoney
#include <signal.h>     // kill(2)
#include <sys/wait.h>   // wait(2)
#include <stdlib.h>     // exit(2)

#include "common.h"     // read_n, write_n

#include <errno.h>
#include <string.h>     // strerror(3)

#include <stdio.h>
#include <stddef.h>

#define PROC_NUM    (3)
#define INIT_MONEY  (100)
#define ITER_COUNT  (2)
#define OK          (0)

/////////////////////////////////
///
///       /// P0 \\\
///    ////   ||   \\\\
///  P1 ------++------ P3
///    \\\    ||    ///
///       \\\ P2 ///
///
/// Description:
///   Process 0 (parent) creates 3 processes
///   and provides them with a pipe for communication.
///
///   Process P1 sends `FIRST_TX` money to P2,
///   then P2 sends `FIRST_TX` money to P3,
///   and at last, when P2 is done, P3 sends `FIRST_TX`
///   money to P1.
///
///   To synchronize the exchanges and make sure the test
///   works correctly, processes P1, P2 and P3 are administered
///   by process P1. They can only initiate the transfer
///   after getting permission from P0.
///
/////////////////////////////////

#define RECEIVE_MSG(fd, ptr, count)         \
    do {                                    \
        if (read_n(fd, ptr, count) < 0) {   \
            exit(1);                        \
        }                                   \
    } while (0)

#define SEND_MSG(fd, ptr, count)            \
    do {                                    \
        if (write_n(fd, ptr, count) < 0) {  \
            exit(1);                        \
        }                                   \
    } while (0)


void child_routine(const int pipe) {
    pid_t next_p;       // Process to send money to.
    int money_to_send;  // How much money to send.
    int expected_money; // How much money should be left after the transfer.

    RECEIVE_MSG(pipe, &next_p, sizeof(next_p));

    for (size_t i = 0; i < ITER_COUNT; ++i) {
        int status = OK;

        RECEIVE_MSG(pipe, &money_to_send, sizeof(money_to_send));
        RECEIVE_MSG(pipe, &expected_money, sizeof(expected_money));

        // Receiving `next_p` and `expected_money` from the parent
        // indicates we can start transferring money.

        int result = transfermoney(next_p, money_to_send);
        if (result < 0 || result != expected_money) {
            status = 1; // Something went wrong.
        }

        SEND_MSG(pipe, &status, sizeof(status));
        if (status != 0) {
            close(pipe);
            exit(1);
        }
    }
}

void parent_fail(const pid_t *procs, const int *pipes, const int n) {
    for (size_t i = 0; i < n; ++i) {
        close(pipes[i]);
        kill(procs[i], SIGKILL);
    }
}

struct tx {
    const int money_to_send;
    const int expected_money;
};

int parent_routine(const pid_t *procs, const int *pipes) {
    const struct tx transactions[ITER_COUNT][PROC_NUM] = {
        {{.money_to_send =  60, .expected_money =  40},
         {.money_to_send =  30, .expected_money = 130},
         {.money_to_send = 120, .expected_money =  10}},
        
        {{.money_to_send = 160, .expected_money =   0},
         {.money_to_send = 290, .expected_money =   0},
         {.money_to_send = 300, .expected_money =   0}}
    };

    for (size_t i = 0; i < PROC_NUM; ++i) {
        SEND_MSG(pipes[i], &procs[(i + 1) % PROC_NUM], sizeof(procs[0]));
    }

    for (size_t it = 0; it < ITER_COUNT; ++it) {
        for (size_t i = 0; i < PROC_NUM; ++i) {
            const int money_to_send  = transactions[it][i].money_to_send;
            const int expected_money = transactions[it][i].expected_money;

            SEND_MSG(pipes[i], &money_to_send, sizeof(money_to_send));
            SEND_MSG(pipes[i], &expected_money, sizeof(expected_money));

            int status;
            RECEIVE_MSG(pipes[i], &status, sizeof(status));

            if (status != OK) {
                fprintf(stderr, "Something has gone wrong...\n");
                parent_fail(procs, pipes, PROC_NUM);
                exit(1);
            }
        }
    }

    int return_code = 0;

    for (size_t i = 0; i < PROC_NUM; ++i) {
        int status;

        if (waitpid(procs[i], &status, 0) < 0) {
            fprintf(stderr,
                    "An error occurred while waiting for process of id %zu. Status = %d; errno = %s\n",
                    i, status, strerror(errno));
            return_code = 1;
        }
    }

    return return_code;
}

int main() {
    pid_t procs[PROC_NUM] = {0};
    int pipes[PROC_NUM] = {0};
    
    int pipefd[2];

    for (size_t i = 0; i < PROC_NUM; ++i) {
        const size_t current_idx = i;

        if (pipe(pipefd) == -1) {
            fprintf(stderr, "Creating a pipe has failed. Stopping the program.\n");
            parent_fail(procs, pipes, i);
            return 1;
        }

        const pid_t p = fork();
        if (p == 0) {
            // Child process.
            close(pipefd[1]);           // Close the write end.
            child_routine(pipefd[0]);
            return 0;
        } else if (p > 0) {
            // Parent.
            close(pipefd[0]);           // Close the read end.
            pipes[i] = pipefd[1];
        } else {
            // An error has occurred.
            fprintf(stderr, "Forking has failed. Stopping the program.\n");
            parent_fail(procs, pipes, i);
            return 1;
        }
    }

    return parent_routine(procs, pipes);
}
