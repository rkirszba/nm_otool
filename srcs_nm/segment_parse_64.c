/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_parse64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:55:09 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/19 11:09:38 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	section_actualize_64(t_file_data *file, struct section_64 *sect_tab,
			uint32_t index)
{
	//peut etre besoin de l'endianness
	if (!ft_strncmp(sect_tab[index].segname, SEG_TEXT, 16)
		&& !ft_strncmp(sect_tab[index].sectname, SECT_TEXT, 16))
		file->text_nb = file->sect_nb + index + 1;
	if (!ft_strncmp(sect_tab[index].segname, SEG_DATA, 16)
		&& !ft_strncmp(sect_tab[index].sectname, SECT_DATA, 16))
		file->data_nb = file->sect_nb + index + 1;
	if (!ft_strncmp(sect_tab[index].segname, SEG_DATA, 16)
		&& !ft_strncmp(sect_tab[index].sectname, SECT_BSS, 16))
		file->bss_nb = file->sect_nb + index + 1;
}

int8_t		segment_parse_64(t_file_data *file, int32_t offset)
{
	struct segment_command_64	*seg_cmd;
	struct section_64			*sect_tab;
	uint32_t					i;
	uint32_t					nsects;

	if (is_inside_file_rel(file->size, offset, sizeof(*seg_cmd)) == FALSE)
		return (print_corrupted_file_error(file->name));
	seg_cmd = (struct segment_command_64*)(file->content + offset);
	offset += sizeof(*seg_cmd);
	nsects = endian_wrap_32(seg_cmd->nsects, file->endian);
	if (is_inside_file_rel(file->size, offset,
			sizeof(*sect_tab) * nsects) == FALSE)
		return (print_corrupted_file_error(file->name));
	sect_tab = (struct section_64*)(file->content + offset);
	i = 0;
	while (i < nsects)
	{
		section_actualize_64(file, sect_tab, i);
		i++;
	}
	file->sect_nb += nsects;
	return (SUCCESS);
}