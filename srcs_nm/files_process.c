/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:17:53 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/14 13:41:42 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int8_t	file_opening_routine(t_file_data *file)
{
	int			fd;
	struct stat	file_stats;

	if ((fd = open(file->name, O_RDONLY)) < 0)
		return (print_file_error(file->name));
	if (fstat(fd, &file_stats) < 0)
	{
		close(fd);
		return (print_file_error(file->name));
	}
	file->size = (int32_t)(file_stats.st_size);
	if ((file->content = (uint8_t*)mmap(NULL, file->size, PROT_READ,
			MAP_PRIVATE, fd, 0) ) == MAP_FAILED)
	{
		close(fd);
		return (print_file_error(file->name));
	}
	close (fd);
	return (SUCCESS);
}

#include <stdio.h>
int8_t			file_process(t_options *options, t_file_data *file)
{
	(void)options;
	printf("%s\n", file->name);
	return (SUCCESS);
}

int8_t			files_process(t_options *options, t_list *files)
{
	int8_t		ret;
	int8_t		tmp_ret;
	t_file_data	*file;

	ret = SUCCESS;
	while (files)
	{
		file = (t_file_data*)(files->data);
		if ((tmp_ret = file_opening_routine(file)) == SUCCESS)
			tmp_ret = file_process(options, files->data);
		if (file->content && file->content != MAP_FAILED)
			if (munmap(file->content, file->size) < 0)
			{
				tmp_ret = ERROR;
				print_munmap_error();
			}
		if (tmp_ret == ERROR && ret == SUCCESS)
			ret = tmp_ret;
		files = files->next;
	}
	return (ret);
}
