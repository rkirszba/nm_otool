/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:58:47 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/21 16:35:59 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_options	*static_options(void)
{
	static t_options	options;

	return (&options);
}

t_file_data	**static_file(void)
{
	static t_file_data *file;

	return (&file);
}

uint32_t	*static_magics(void)
{
	static uint32_t	magics_tab[NB_MAGICS] = {
		MH_MAGIC,
		MH_CIGAM,
		MH_MAGIC_64,
		MH_CIGAM_64,
		FAT_MAGIC,
		FAT_CIGAM,
		FAT_MAGIC_64,
		FAT_CIGAM_64
	};

	return (magics_tab);
}	
