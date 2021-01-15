/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:49:22 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/15 19:33:39 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		set_option(t_options *options, char option)
{
	if (option == 'a')
		options->a = TRUE;
	if (option == 'g')
		options->g = TRUE;
	if (option == 'j')
		options->j = TRUE;
	if (option == 'n')
		options->n = TRUE;
	if (option == 'o')
		options->o = TRUE;
	if (option == 'p')
		options->p = TRUE;
	if (option == 'r')
		options->r = TRUE;
	if (option == 'u')
		options->u = TRUE;
	if (option == 'P')
		options->U = TRUE;
	if (option == 'U')
		options->U = TRUE;
}

int8_t				get_options(int ac, char **av, t_options *options, int *arg_offset)
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
				return (print_options_error(arg[i]));
			set_option(options, arg[i]);
		}
	}
	return (SUCCESS);
}

static t_list	*create_new_file_node(char *file_name)
{
	char		*name_dup;
	t_file_data	*data;
	t_list		*new;

	name_dup = NULL;
	data = NULL;
	new = NULL;
	if (!(name_dup = ft_strdup(file_name))
		|| !(data = (t_file_data*)malloc(sizeof(*data)))
		|| !(new = (t_list*)malloc(sizeof(new))))
	{
		free(name_dup);
		free(data);
		free(new);
		print_malloc_error();
		return (NULL);
	}
	ft_bzero(data, sizeof(*data));
	data->name = name_dup;
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
	if (!(*list))
	{
		if (!(new = create_new_file_node(DEFAULT_FILE)))
			return (MALLOC_ERROR);
		ft_list_append(list, new);
	}
	return (SUCCESS);
}
