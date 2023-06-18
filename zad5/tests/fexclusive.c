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
// UNLOCK on close 5

int main(int argc, char *argv[]) {
    if (argc != 9){
        printf("Usage: %s <file> <lock_flag_no> <unlock_flag_no> <seconds> <expected return value lock> <expected errno lock> <expected return value unlock> <expected errno unlock>\n", argv[0]);
        return 1;
    }
    int return_value = 0;
    printf("Running %s: %s %s %s %s %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5],argv[6],argv[7],argv[8]);
    int lock_flag_no = atoi(argv[2]), lock_flag, unlock_flag_no = atoi(argv[3]), unlock_flag;

    int sec = atoi(argv[4]);
    int res_lock = atoi(argv[5]), errno_lock = atoi(argv[6]);
    int res_unlock = atoi(argv[7]), errno_unlock = atoi(argv[8]);

    assert(lock_flag_no >= 1 && lock_flag_no <= 5);
    assert(unlock_flag_no >= 1 && unlock_flag_no <= 5);
    
    lock_flag = get_flag(lock_flag_no);
    unlock_flag = get_flag(unlock_flag_no);

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Cant open file %s (res: %d).\n", argv[1], fd);
        return 1;
    }

    int res = vfs_fexclusive(fd, lock_flag);

    if (res != res_lock || errno != errno_lock){
        printf("Lock, expected: res=%d errno=%d (%s, %s)\n", res_lock, errno_lock, errnoname(errno_lock), strerror(errno_lock));
        printf("Lock, got: res=%d errno=%d (%s, %s)\n", res, errno, errnoname(errno), strerror(errno));
        return_value = 1;
    }

    printf("Sleeping %d seconds...\n", sec);
    sleep(sec);

    if (unlock_flag_no == 5){
        printf("Closing file...\n");
        close(fd);
        return 0;
    }

    res = vfs_fexclusive(fd, unlock_flag);
    close(fd);

    if (res != res_unlock || errno != errno_unlock){
        printf("Unlock, expected: res=%d errno=%d (%s, %s)\n", res_unlock, errno_unlock, errnoname(errno_unlock), strerror(errno_unlock));
        printf("Unlock, got: res=%d errno=%d (%s, %s)\n", res, errno, errnoname(errno), strerror(errno));
        return_value = 1;
    }

    return return_value;
}
