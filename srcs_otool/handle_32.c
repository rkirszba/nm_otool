/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:49:45 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 17:15:16 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int8_t	section_parse_32(t_file_data *file, struct section *sect_tab,
				uint32_t index)
{
	// peut etre qu'il faudra ajouter file->off_header
	if (!ft_strncmp(sect_tab[index].segname, SEG_TEXT, 16)
		&& !ft_strncmp(sect_tab[index].sectname, SECT_TEXT, 16))
	{
		file->off_text = endian_wrap_u32(sect_tab[index].offset, file->endian)
		+ file->off_header;
		file->addr_text = endian_wrap_u32(sect_tab[index].addr, file->endian);
		file->size_text = endian_wrap_u32(sect_tab[index].size, file->endian);
		if (is_inside_file_rel(file->size, file->off_text, file->size_text)
			== FALSE)
			return (print_corrupted_file_error(file));
	}
	if (!ft_strncmp(sect_tab[index].segname, SEG_DATA, 16)
		&& !ft_strncmp(sect_tab[index].sectname, SECT_DATA, 16))
	{
		file->off_data = endian_wrap_u32(sect_tab[index].offset, file->endian)
		+ file->off_header;
		file->addr_data = endian_wrap_u32(sect_tab[index].addr, file->endian);
		file->size_data = endian_wrap_u32(sect_tab[index].size, file->endian);
		if (is_inside_file_rel(file->size, file->off_data, file->size_data)
			== FALSE)
			return (print_corrupted_file_error(file));
	}
	return (SUCCESS);
}	

static int8_t	segment_parse_32(t_file_data *file, uint64_t offset)
{
	struct segment_command	*seg_cmd;
	struct section			*sect_tab;
	uint32_t				i;
	uint32_t				nsects;

	if (is_inside_file_rel(file->size, offset, sizeof(*seg_cmd)) == FALSE)
		return (print_corrupted_file_error(file));
	seg_cmd = (struct segment_command*)(file->content + offset);
	offset += sizeof(*seg_cmd);
	nsects = endian_wrap_u32(seg_cmd->nsects, file->endian);
	if (is_inside_file_rel(file->size, offset,
			sizeof(*sect_tab) * nsects) == FALSE)
		return (print_corrupted_file_error(file));
	sect_tab = (struct section*)(file->content + offset);
	i = -1;
	while (++i < nsects)
		section_parse_32(file, sect_tab, i);
	return (SUCCESS);
}

static int8_t	load_commands_parse_32(t_file_data *file, uint32_t ncmds)
{
	uint32_t			i;
	uint64_t			offset;
	struct load_command	*lc;
	uint32_t			cmd;	
	
	i = 0;
	offset = file->off_header + sizeof(struct mach_header);
	while (i < ncmds)
	{
		if (is_inside_file_rel(file->size, offset, sizeof(*lc)) == FALSE)
			return (print_corrupted_file_error(file));
		lc = (struct load_command*)(file->content + offset);
		cmd = endian_wrap_u32(lc->cmd, file->endian);
		if (cmd == LC_SEGMENT)
			if (segment_parse_32(file, offset) == ERROR)
				return (ERROR);
		offset += endian_wrap_u32(lc->cmdsize, file->endian);
		i++;
	}
	return (SUCCESS);
}

int8_t			handle_mh_32(t_file_data *file)
{
	struct mach_header	*header;
	int8_t					ret;

	file->bits = bits32;
	if (is_inside_file_rel(file->size, file->off_header, sizeof(*header))
		== FALSE)
		return (print_corrupted_file_error(file));
	header = (struct mach_header *)(file->content + file->off_header);
	ret = load_commands_parse_32(file,
		endian_wrap_u32(header->ncmds, file->endian));
	if (ret == SUCCESS)
		sections_print(file);
	return (ret);
}
