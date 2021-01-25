/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:28:18 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 17:03:04 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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

static int8_t	files_process(t_list *files)
{
	int8_t		ret;
	int8_t		tmp_ret;
	t_file_data	*file;

	if (!files)
		return (print_usage());
	ret = SUCCESS;
	while (files)
	{
		file = (t_file_data*)(files->data);
		if ((tmp_ret = file_loading_routine(file)) == SUCCESS)
			tmp_ret = dispatcher(files->data);
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

int8_t			dispatcher(t_file_data *file)
{
	// static int8_t (*tab[NB_HANDLERS])(t_file_data *) = {
	// 	&handle_mh_32,
	// 	&handle_mh_64,
	// 	&handle_fat_32,
	// 	&handle_fat_64
	// };
	// uint32_t			*magics_tab;
	// uint32_t			magic;
	// int					i;

	// if (is_inside_file_rel(file->size, file->off_header,
	// 		sizeof(uint32_t)) == FALSE)
	// 	return (print_invalid_file_error(file));
	// magic = *(uint32_t*)(file->content + file->off_header);
	// magics_tab = static_magics();
	// i = -1;
	// while (++i < (file->fat ? NB_MAGICS / 2 : NB_MAGICS))
	// 	if (magics_tab[i] == magic)
	// 		break ;
	// if (i == (file->fat ? NB_MAGICS / 2 : NB_MAGICS))
	// 	return (print_invalid_file_error(file));
	// file->endian = i % 2;
	// return (tab[i / 2](file));
	return (handle_mh_32(file));
}

int		main(int ac, char **av)
{
	int				arg_offset;
	t_list			*files;
	t_options		*options;
	int				ret;

	if (get_options(ac, av, &arg_offset) == ERROR)
		return (EXIT_FAILURE);
	options = static_options();
	if (options->d == FALSE)
		options->t = TRUE;
	files = NULL;
	if (get_files(&files, ac, av, arg_offset) == MALLOC_ERROR)
		return (EXIT_FAILURE);
	ret = files_process(files);
	// ft_list_free(files, &free_file_data);
	return ((int)ret);
}
