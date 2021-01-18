/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:58:47 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/18 16:30:09 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_options		*static_options(void)
{
	static t_options	options;

	return (&options);
}

t_file_data		**static_file(void)
{
	static t_file_data *file;

	return (&file);
}
