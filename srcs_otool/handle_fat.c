/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:02:08 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/27 12:37:29 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			file_reinit(t_file_data *file)
{
	file->off_text = 0;
	file->size_text = 0;
	file->addr_text = 0;
	file->off_data = 0;
	file->size_data = 0;
	file->addr_data = 0;
}

static int8_t	handle_multi_arch_64(t_file_data *file,
				struct fat_arch_64 *arch, uint32_t nfat_arch)
{
	t_endian	endian;
	uint32_t	i;
	uint8_t		ret;
	uint8_t		tmp_ret;

	file->multi_arch = TRUE;
	endian = file->endian;
	ret = SUCCESS;
	i = -1;
	while (++i < nfat_arch)
	{
		tmp_ret = SUCCESS;
		file->arch = get_file_arch_64(&arch[i], endian);
		file->off_header = endian_wrap_u32(arch[i].offset, endian);
		if (is_inside_file_rel(file->size, file->off_header, 0) == FALSE)
			tmp_ret = print_corrupted_file_error(file);
		if (tmp_ret == SUCCESS)
			tmp_ret = dispatcher(file);
		if (tmp_ret && ret == SUCCESS)
			ret = ERROR;
		file_reinit(file);
	}
	return (ret);
}

int8_t			handle_fat_64(t_file_data *file)
{
	struct fat_header	*header;
	struct fat_arch_64	*arch;
	uint32_t			nfat;
	uint32_t			i;

	file->fat = TRUE;
	if (is_inside_file_rel(file->size, 0, sizeof(*header)) == FALSE)
		return (print_corrupted_file_error(file));
	header = (struct fat_header*)file->content;
	nfat = endian_wrap_u32(header->nfat_arch, file->endian);
	if (!nfat)
		return (SUCCESS);
	if (!is_inside_file_rel(file->size, sizeof(*header), nfat * sizeof(*arch)))
		return (print_corrupted_file_error(file));
	arch = (struct fat_arch_64*)(file->content + sizeof(*header));
	i = -1;
	while (++i < nfat)
		if (endian_wrap_u32(arch[i].cputype, file->endian) == CPU_TYPE_X86_64)
		{
			file->off_header = endian_wrap_u32(arch[i].offset, file->endian);
			if (!is_inside_file_rel(file->size, file->off_header, 0))
				return (print_corrupted_file_error(file));
			return (dispatcher(file));
		}
	return (handle_multi_arch_64(file, arch, nfat));
}

static int8_t	handle_multi_arch_32(t_file_data *file, struct fat_arch *arch,
				uint32_t nfat_arch)
{
	t_endian	endian;
	uint32_t	i;
	uint8_t		ret;
	uint8_t		tmp_ret;

	file->multi_arch = TRUE;
	endian = file->endian;
	ret = SUCCESS;
	i = -1;
	while (++i < nfat_arch)
	{
		tmp_ret = SUCCESS;
		file->arch = get_file_arch_32(&arch[i], endian);
		file->off_header = endian_wrap_u32(arch[i].offset, endian);
		if (is_inside_file_rel(file->size, file->off_header, 0) == FALSE)
			tmp_ret = print_corrupted_file_error(file);
		if (tmp_ret == SUCCESS)
			tmp_ret = dispatcher(file);
		if (tmp_ret && ret == SUCCESS)
			ret = ERROR;
		file_reinit(file);
	}
	return (ret);
}

int8_t			handle_fat_32(t_file_data *file)
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	uint32_t			nfat;
	uint32_t			i;

	file->fat = TRUE;
	if (is_inside_file_rel(file->size, 0, sizeof(*header)) == FALSE)
		return (print_corrupted_file_error(file));
	header = (struct fat_header*)file->content;
	nfat = endian_wrap_u32(header->nfat_arch, file->endian);
	if (!nfat)
		return (SUCCESS);
	if (!is_inside_file_rel(file->size, sizeof(*header), nfat * sizeof(*arch)))
		return (print_corrupted_file_error(file));
	arch = (struct fat_arch*)(file->content + sizeof(*header));
	i = -1;
	while (++i < nfat)
		if (endian_wrap_u32(arch[i].cputype, file->endian) == CPU_TYPE_X86_64)
		{
			file->off_header = endian_wrap_u32(arch[i].offset, file->endian);
			if (!is_inside_file_rel(file->size, file->off_header, 0))
				return (print_corrupted_file_error(file));
			return (dispatcher(file));
		}
	return (handle_multi_arch_32(file, arch, nfat));
}
