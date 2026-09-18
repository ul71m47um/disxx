#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include "../../modules/utility/public/file/mapped.h"

// If this file'll be compiled with C++ compiler
#ifdef __cplusplus
extern "C"
{
#endif

struct mapped_t mopen(const char *path)
{
	struct mapped_t mapped = { .mptr = NULL, .msize = 0 };

	int fd = open(path, O_RDWR);
    if (fd == -1)
        return mapped;

   	off_t size = lseek(fd, 0, SEEK_END);
	if (size == -1)
		return mapped;
	
    void *ptr = mmap
	(
		NULL,
		size,
		PROT_READ,
		MAP_FILE | MAP_PRIVATE,
		fd,
		0
	);
	
	close(fd);

	if (ptr == MAP_FAILED)
		return mapped;

	mapped.mptr = ptr;
	mapped.msize = size;
	return mapped;
}

signed long long int mclose(struct mapped_t mapped)
{
	if ((mapped.mptr != MAP_FAILED && mapped.mptr != NULL) && mapped.msize != -1)
		return munmap(mapped.mptr, mapped.msize);
	return -1;
}

#ifdef __cplusplus
}
#endif
