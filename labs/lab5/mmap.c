#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#define MEM_SIZE 15

int main(int argc, char *argv[])
{
	char *addr;
	int fd;

	if (argc < 2) {
        fprintf(stderr, "Usage error: %s file [new-value]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	//file descriptor-integer that uniquely identifies an open file in a computer's operating system
	//O_RDWR-Open for reading and writing
	fd = open(argv[1], O_RDWR);

	if (fd == -1) {
		fprintf(stderr, "open error");
		exit(EXIT_FAILURE);
	}
	/* Map shared memory region */
	//OS creates a virtual memory region
	//NULL- Let the system choose the (page-aligned) address at which to create the mapping
	//MEM_SIZE- length of the mapping. should be multiple of the page size
	//PROT_READ | PROT_WRITE- Pages may be read and written
	//MAP_SHARED- Share this mapping with all other processes that map this file
	//fd- file descriptor of the file to be mapped
	//0- Offset within the file at which the mapping starts
	addr = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (addr == MAP_FAILED) {
		fprintf(stderr, "mmap error");
		exit(EXIT_FAILURE);
	}

	if (close(fd) == -1) { /* No longer need 'fd' */
		fprintf(stderr, "close error");
		exit(EXIT_FAILURE);
	}

	/* Secure practice: output at most MEM_SIZE bytes */
    printf("Current string=%.*s\n", MEM_SIZE, addr);

	if (argc > 2) { /* Update contents of region */
		if (strlen(argv[2]) >= MEM_SIZE) {
			fprintf(stderr, "'new-value' too large\n");
			exit(EXIT_FAILURE);
		}

		//Clears old content
		memset(addr, 0, MEM_SIZE); /* Zero out region */

		// last byte = '\0'
		strncpy(addr, argv[2], MEM_SIZE - 1);
		
		//Forces changes in the mapped memory to be written to disk
		if (msync(addr, MEM_SIZE, MS_SYNC) == -1) {
			fprintf(stderr, "msync");
			exit(EXIT_FAILURE);
		}

		printf("Copied \"%s\" to shared memory\n", argv[2]);
	}

	exit(EXIT_SUCCESS);
}
