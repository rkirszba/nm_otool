/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:57:40 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 20:12:24 by rkirszba         ###   ########.fr       */
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

static void	bytes_print(t_file_data *file, uint64_t addr, uint64_t offset,
			uint64_t size)
{
	uint64_t	i;

	i = -1;
	while (++i < size)
	{
		if (i % 16 == 0)
		{
			if (i != 0)
				ft_putstr("\n");
			print_hex(addr + i, (file->bits == bits64) ? 16 : 8);
			ft_putstr("\t");
		}
		print_hex(*(file->content + offset + i), 2);
		if (file->endian == little || (i + 1) % 4 == 0)
			ft_putstr(" ");
	}
	ft_putstr("\n");
}

void		sections_print(t_file_data *file)
{
	t_options	*options;

	options = static_options();
	ft_putstr(file->name);
	if (file->fat == TRUE && file->arch)
	{
		ft_putstr(" (architecture ");
		ft_putstr(file->arch);
		ft_putstr(")");
	}
	write(1, ":\n", 2);
	if (options->t && file->off_text)
	{
		ft_putstr("Contents of (__TEXT,__text) section\n");
		bytes_print(file, file->addr_text, file->off_text, file->size_text);
	}
	if (options->d && file->off_data)
	{
		ft_putstr("Contents of (__DATA,__data) section\n");
		bytes_print(file, file->addr_data, file->off_data, file->size_data);
	}
}