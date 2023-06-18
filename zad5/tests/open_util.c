#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

// OPERATIONS
// NONE 0
// READ 1
// WRITE 2

int main(int argc, char *argv[]){
    if (argc != 7) {
        printf("Usage: %s <file> <sleep 1> <operation> <sleep 2> <expected result operation> <expected errno>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    printf("Opened file %s with fd %d\n", argv[1], fd);

    int sleep1 = atoi(argv[2]);
    int operation = atoi(argv[3]);
    int sleep2 = atoi(argv[4]);
    int exp_result = atoi(argv[5]);
    int exp_errno = atoi(argv[6]);
    int res = 0;

    sleep(sleep1);

    char buffer[2] = {0, 0};
    if (operation == 1){
        res = read(fd, &buffer, 1);
    }
    else if (operation == 2){
        res = write(fd, &buffer, 1);
    }
    
    sleep(sleep2);

    close(fd);
    printf("Closed file %s with fd %d\n", argv[1], fd);

    if (res != exp_result || errno != exp_errno){
        printf("[open_util] expected: res=%d errno=%d (%s, %s)\n", exp_result, exp_errno, errnoname(exp_errno), strerror(exp_errno));
        printf("[open_util] got: res=%d errno=%d (%s, %s)\n", res, errno, errnoname(errno), strerror(errno));
        return 1;
    }

    return 0;
}