/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:17:53 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/15 17:27:33 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int8_t	file_loading_routine(t_file_data *file)
{
	int			fd;
	struct stat	file_stats;

	if ((fd = open(file->name, O_RDONLY)) < 0)
		return (print_loading_file_error(file->name));
	if (fstat(fd, &file_stats) < 0)
	{
		close(fd);
		return (print_loading_file_error(file->name));
	}
	file->size = (int32_t)(file_stats.st_size);
	if ((file->content = (uint8_t*)mmap(NULL, file->size, PROT_READ,
			MAP_PRIVATE, fd, 0) ) == MAP_FAILED)
	{
		close(fd);
		return (print_loading_file_error(file->name));
	}
	close (fd);
	return (SUCCESS);
}

int8_t			file_dispatcher(t_options *options, t_file_data *file)
{
	static t_dispatcher	dispatcher[NB_FORMATS] = {
		{MH_MAGIC, &handle_mh32},
		{MH_MAGIC_64, &handle_mh64},
		{FAT_MAGIC, &handle_fat32},
		{FAT_MAGIC_64, &handle_fat64}
	};
	uint32_t			magic;
	int					i;

	(void)options;
	if (is_inside_file_rel(file->size, 0, sizeof(uint32_t)) == FALSE)
		return (print_invalid_file_error(file->name));
	magic = *(uint32_t*)file->content;
	i = -1;
	while (++i < NB_FORMATS)
		if (dispatcher[i].magic == magic)
			return (dispatcher[i].fun(options, file));
	return (print_invalid_file_error(file->name));
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
		if ((tmp_ret = file_loading_routine(file)) == SUCCESS)
			tmp_ret = file_dispatcher(options, files->data);
		if (file->content && file->content != MAP_FAILED)
			if (munmap(file->content, file->size) < 0)
			{
				tmp_ret = ERROR;
				print_munmap_error();
			}
		if (tmp_ret && ret == SUCCESS)
			ret = ERROR;
		files = files->next;
	}
	return (ret);
}
