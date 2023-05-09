#ifndef MINIX3_TASK1_COMMON_H
#define MINIX3_TASK1_COMMON_H

#include <unistd.h>

// Read exactly `count` bytes.
inline ssize_t read_n(int fd, void *buf, size_t count) {
    size_t read_count = 0;

    while (read_count < count) {
        ssize_t result = read(fd, (char *)buf + read_count, count - read_count);
        if (result < 0) {
            return result;
        }
        read_count += result;
    }

    return count;
}

// Write exactly `count` bytes.
inline ssize_t write_n(int fd, const void *buf, size_t count) {
    size_t written_count = 0;

    while (written_count < count) {
        ssize_t result = write(fd, (const char *)buf + written_count, count - written_count);
        if (result < 0) {
            return result;
        }
        written_count += result;
    }

    return count;
}


#endif // MINIX3_TASK1_COMMON_H
