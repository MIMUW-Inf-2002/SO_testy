#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

// EXCL_LOCK 1
// EXCL_LOCK_NO_OTHERS 2
// EXCL_UNLOCK 3
// EXCL_UNLOCK_FORCE 4
// INCORRECT FLAG 5

int main(int argc, char *argv[]) {
    printf("Running %s: %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);
    if (argc != 5){
        printf("Usage: %s <file> <flag_no> <expected return value> <expected errno>\n", argv[0]);
        return 1;
    }
    int flag_no, flag;

    flag_no = atoi(argv[2]);
    assert(flag_no >= 1 && flag_no <= 5);

    flag = get_flag(flag_no);

    int res = vfs_exclusive(argv[1], flag);
    
    int exp_res = atoi(argv[3]), exp_errno = atoi(argv[4]);
    
    if (res != exp_res || errno != exp_errno){
        printf("Expected: res=%d errno=%d (%s, %s)\n", exp_res, exp_errno, errnoname(exp_errno), strerror(exp_errno));
        printf("Got: res=%d errno=%d (%s, %s)\n", res, errno, errnoname(errno), strerror(errno));
        return 1;
    }

    return 0;
}
