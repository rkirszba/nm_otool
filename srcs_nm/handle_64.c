/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:30:53 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/19 11:33:44 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int8_t	load_commands_parse_64(t_file_data *file, uint32_t ncmds)
{
	uint32_t			i;
	int32_t				offset;
	struct load_command	*lc;
	uint32_t			cmd;	
	
	i = 0;
	offset = file->off_header + sizeof(struct mach_header_64);
	while (i < ncmds)
	{
		if (is_inside_file_rel(file->size, offset, sizeof(*lc)) == FALSE)
			return (print_corrupted_file_error(file->name));
		lc = (struct load_command*)(file->content + offset);
		cmd = endian_wrap_32(lc->cmd, file->endian);
		if (cmd == LC_SYMTAB)
			file->off_symtab = offset;
		if (cmd == LC_SEGMENT_64)
			if (segment_parse_64(file, offset) == ERROR)
				return (ERROR);
		offset += endian_wrap_32(lc->cmdsize, file->endian);
		i++;
	}
	return (file->off_symtab ? SUCCESS : print_corrupted_file_error(file->name));
}

int8_t			handle_mh_64(t_file_data *file)
{
	struct mach_header_64	*header;
	int8_t					ret;

	file->arch = x64;
	if (is_inside_file_rel(file->size, file->off_header, sizeof(*header)) == FALSE)
		return (print_corrupted_file_error(file->name));
	header = (struct mach_header_64 *)(file->content + file->off_header);
	ret = load_commands_parse_64(file,
		endian_wrap_32(header->ncmds, file->endian));
	if (ret == SUCCESS)
		ret = symbols_get_64(file);
	if (ret == SUCCESS)
		symbols_print(file);
	ft_btree_free(file->symbols, &free_symbol_data);
	return (ret);
}

int8_t			handle_fat_64(t_file_data *file)
{
	(void)file;
	return (SUCCESS);
}
