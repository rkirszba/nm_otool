/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:32:05 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 16:28:25 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void		set_option(char option)
{
	t_options	*options;

	options = static_options();
	if (option == 'd')
		options->d = TRUE;
	if (option == 't')
		options->t = TRUE;
}

int8_t			get_options(int ac, char **av, int *arg_offset)
{
	char	*arg;
	size_t	i;

	*arg_offset = 0;
	while (++(*arg_offset) < ac)
	{
		arg = av[*arg_offset];
		if (arg[0] != '-')
			return (SUCCESS);
		if (!ft_strcmp(arg, "--"))
		{
			(*arg_offset)++;
			return (SUCCESS);
		}
		i = 0;
		while (arg[++i])
		{
			if (!ft_strchr(OPTIONS, (int)(arg[i])))
				return (print_options_error(arg[i], arg));
			set_option(arg[i]);
		}
	}
	return (SUCCESS);
}

static t_list	*create_new_file_node(char *file_name)
{
	char		*name_dup;
	t_file_data	*data;
	t_list		*new;

	if (!(data = (t_file_data*)malloc(sizeof(*data)))
		|| !(name_dup = ft_strdup(file_name)))
	{
		free(data);
		print_malloc_error();
		return (NULL);
	}
	ft_bzero(data, sizeof(*data));
	data->name = name_dup;
	if (!(new = ft_list_new((void*)data)))
	{
		// free_file_data(data);
		print_malloc_error();
		return (NULL);
	}
	new->data = (void*)data;
	return (new);
}

int8_t			get_files(t_list **list, int ac, char **av, int arg_offset)
{
	t_list		*new;

	while (arg_offset < ac)
	{
		if (!(new = create_new_file_node(av[arg_offset])))
			return (MALLOC_ERROR);
		ft_list_append(list, new);
		arg_offset++;
	}
	return (SUCCESS);
}
