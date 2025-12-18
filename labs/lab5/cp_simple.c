#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int srcFd, destFd;
    struct stat sb;
    void *srcMap;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <src> <dest>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Բացում ենք source ֆայլը */
    srcFd = open(argv[1], O_RDONLY);
    if (srcFd == -1) {
        perror("Source file does not exist");
        exit(EXIT_FAILURE);
    }

    /* Ստանում ենք source ֆայլի չափը */
    if (fstat(srcFd, &sb) == -1) {
        perror("fstat error");
        close(srcFd);
        exit(EXIT_FAILURE);
    }

    /* Ստեղծում / բացում ենք destination ֆայլը */
    destFd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (destFd == -1) {
        perror("Destination open error");
        close(srcFd);
        exit(EXIT_FAILURE);
    }

    /* Սահմանում ենք destination ֆայլի չափը */
    if (ftruncate(destFd, sb.st_size) == -1) {
        perror("ftruncate error");
        close(srcFd);
        close(destFd);
        exit(EXIT_FAILURE);
    }

    /* mmap source ֆայլը */
    srcMap = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, srcFd, 0);
    if (srcMap == MAP_FAILED) {
        perror("mmap error");
        close(srcFd);
        close(destFd);
        exit(EXIT_FAILURE);
    }

    /* Պատճենում ենք տվյալները */
    if (write(destFd, srcMap, sb.st_size) != sb.st_size) {
        perror("write error");
    }

    munmap(srcMap, sb.st_size);

    close(srcFd);
    close(destFd);

    return EXIT_SUCCESS;
}
