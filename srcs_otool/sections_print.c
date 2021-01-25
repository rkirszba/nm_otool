/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:57:40 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 17:17:44 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_hex(uint64_t nb, uint32_t width)
{
	if (width == 0)
		return ;
	print_hex(nb / 16, width - 1);
	write(1, &HEX_BASE[nb % 16], 1);
}

//peut etre qu'il faudra ajouter size_header
static void	bytes_print(uint8_t *content, uint64_t addr, uint64_t offset,
		uint64_t size, t_bits bits)
{
	uint64_t	i;

	if (offset == 0)
		return ;
	i = -1;
	while (++i < size)
	{
		if (i % 16 == 0)
		{
			if (i != 0)
				ft_putstr("\n");
			print_hex(addr + i, (bits == bits64) ? 16 : 8);
			ft_putstr("\t");
		}
		print_hex(*(content + offset + i), 2);
		ft_putstr(" ");
	}
	ft_putstr("\n");
}

void	sections_print(t_file_data *file)
{
	t_options	*options;

	options = static_options();
	// voir avec differentes archis
	ft_putstr(file->name);
	write(1, ":\n", 2);
	if (options->t)
	{
		ft_putstr("Contents of (__TEXT,__text) section\n");
		bytes_print(file->content, file->addr_text, file->off_text, file->size_text, file->bits);
	}
	if (options->d)
	{
		ft_putstr("Contents of (__DATA,__data) section\n");
		bytes_print(file->content, file->addr_data, file->off_data, file->size_data, file->bits);
	}
}