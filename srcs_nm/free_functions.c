/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:16:49 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/21 16:55:23 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
