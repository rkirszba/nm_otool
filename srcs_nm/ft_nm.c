/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:27:04 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/13 19:39:33 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		free_file_data(void *data)
{
	free(((t_file_data*)data)->name);
	free(data);
}

static int		process_files(t_options *options, t_list *files)
{
	t_file_data	*data;

	ft_putstr("----- OPTIONS -----\n");
	if (options->a == TRUE)
		ft_putstr("a\n");
	if (options->b == TRUE)
		ft_putstr("b\n");
	if (options->c == TRUE)
		ft_putstr("c\n");
	if (options->d == TRUE)
		ft_putstr("d\n");
	if (options->e == TRUE)
		ft_putstr("e\n");
	if (options->f == TRUE)
		ft_putstr("f\n");
	
	ft_putstr("----- FILES -----\n");
	while (files)
	{
		data = (t_file_data*)(files->data);
		ft_putstr(data->name);
		ft_putstr("\n");
		files = files->next;
	}
	return (SUCCESS);
}

int				main(int ac, char **av)
{
	t_options		options;
	int				arg_offset;
	t_list			*files;
	int				ret;

	ft_bzero(&options, sizeof(options));
	if (get_options(ac, av, &options, &arg_offset) == ERROR)
		return (ERROR);
	if (get_files(&files, ac, av, arg_offset) == ERROR)
		return (ERROR);
	ret = process_files(&options, files);
	ft_list_free(files, &free_file_data);
	return (ret);
}
