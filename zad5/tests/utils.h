#include <lib.h>
#include <minix/rs.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "serrno.h"

int vfs_exclusive(char *file, int flags){
    int ret;
    message m;
    endpoint_t vfs_ep;

    m.m_lc_vfs_exclusive.name = (vir_bytes)file;
    m.m_lc_vfs_exclusive.len = strlen(file) + 1;
    m.m_lc_vfs_exclusive.flags = flags;
    minix_rs_lookup("vfs", &vfs_ep);
    ret = _syscall(vfs_ep, VFS_EXCLUSIVE, &m);
    printf("Result VFS_EXCLUSIVE request: %d, errno: %d (%s, %s)\n", ret, errno, errnoname(errno), strerror(errno));
    return ret;
}

int vfs_fexclusive(int fd, int flags){
    int ret;
    message m;
    endpoint_t vfs_ep;

    m.m_lc_vfs_exclusive.fd = fd;
    m.m_lc_vfs_exclusive.flags = flags;
    minix_rs_lookup("vfs", &vfs_ep);
    ret = _syscall(vfs_ep, VFS_FEXCLUSIVE, &m);
    printf("Result VFS_FEXCLUSIVE request: %d, errno: %d (%s, %s)\n", ret, errno, errnoname(errno), strerror(errno));
    return ret;
}

int get_flag(int flag_no){
    if (flag_no == 1)
        return EXCL_LOCK;
    else if (flag_no == 2)
        return EXCL_LOCK_NO_OTHERS;
    else if (flag_no == 3)
        return EXCL_UNLOCK;
    else if (flag_no == 4)
        return EXCL_UNLOCK_FORCE;
    else
        return -1;
}