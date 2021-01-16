/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:27:04 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/16 18:19:25 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
// a remettre dnas le fichier free_functions.c
void	free_file_data(void *data)
{
	free(((t_file_data*)data)->name);
	free(data);
}

void	free_symbol_data(void *data)
{
	free(((t_symbol_data*)data)->name);
	free(data);
}


int				main(int ac, char **av)
{
	t_options		options;
	int				arg_offset;
	t_list			*files;
	int				ret;

	ft_bzero(&options, sizeof(options));
	if (get_options(ac, av, &options, &arg_offset) == ERROR)
		return (EXIT_FAILURE);
	if (get_files(&files, ac, av, arg_offset) == MALLOC_ERROR)
		return (EXIT_FAILURE);
	ret = files_process(&options, files);
	ft_list_free(files, &free_file_data);
	return ((int)ret);
}
