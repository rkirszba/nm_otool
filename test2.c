#include <sys/mman.h>
#include <stdio.h>

int	main(void)
{
	if (munmap(0, 0) == -1)
		perror("munmap");
	return (0);
}
