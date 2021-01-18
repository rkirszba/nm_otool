/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_sort_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:14:43 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/18 16:26:54 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		symbol_no_sort(void *curs_data, void *node_data)
{
	(void)curs_data;
	(void)node_data;
	return (-1);
}

int		symbol_alpha_sort(void *curs_data, void *node_data)
{
	t_symbol_data	*curs;
	t_symbol_data	*node;

	curs = (t_symbol_data*)curs_data;
	node = (t_symbol_data*)node_data;
	return (ft_strcmp(curs->name, node->name));
}

int		symbol_num_sort(void *curs_data, void *node_data)
{
	t_symbol_data	*curs;
	t_symbol_data	*node;
	int32_t			diff;

	curs = (t_symbol_data*)curs_data;
	node = (t_symbol_data*)node_data;
	diff = curs->value - node->value;
	if (diff == 0)
		return (ft_strcmp(curs->name, node->name));
	return (diff > 0 ? 1 : -1);
}

int		(*symbol_get_sort_fun(void))(void*, void*)
{
	t_options	*options;

	options = static_options();
	if (options->n)
		return (&symbol_num_sort);
	if (options->p)
		return (&symbol_no_sort);
	return (&symbol_alpha_sort);
}
