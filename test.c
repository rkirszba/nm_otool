#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int	main(void)
{
	int			fd;
	struct stat	buf;
	char		*ptr;
	int			val;
	char		buf_read[1];

	fd = open("test", O_RDONLY);
	if (fd == -1)
	{
		printf("errno = %d\n", errno);
		perror(strerror(errno));
	}
	fstat(fd, &buf);
	printf("size = %lld\n", buf.st_size);
	if((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	close(fd);
//	if (read(fd, buf_read, 1) == -1)
//	{
//		printf("errno = %d\n", errno);
//		perror(strerror(errno));
//	}
	val = *(int*)ptr;
	printf("val = %0x\n", val);
	return (0);
}
