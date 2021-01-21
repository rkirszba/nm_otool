/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:30:53 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/21 16:31:57 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	*symbol_get_name_64(t_file_data *file, struct nlist_64 *sym)
{
	char		*name;
	uint32_t	n_strx;
	uint32_t	n;

	n_strx = endian_wrap_u32(sym->n_un.n_strx, file->endian);
	if (n_strx == 0)
		return (ft_strdup(""));
	if (n_strx > file->str_size)
		return (ft_strdup(BAD_STR_INDEX));
	name = file->sym_str + n_strx;
	if (is_inside_file_abs(file->content, file->size, (void*)name) == FALSE)
		return (ft_strdup(BAD_STR_INDEX));
	n = distance_to_eof(file->content, file->size, (void*)name);
	return (ft_strndup(name, n -1));
}

static int8_t	symbol_get_64(t_file_data *file, struct nlist_64 *sym)
{
	t_symbol_data	*new_symbol;
	int8_t			ret;

	if (!(new_symbol = (t_symbol_data*)malloc(sizeof(*new_symbol))))
		return (print_malloc_error());
	ft_bzero(new_symbol, sizeof(*new_symbol));
	if (!(new_symbol->name = symbol_get_name_64(file, sym)))
	{
		free(new_symbol);
		return (print_malloc_error());
	}
	new_symbol->value = endian_wrap_u64(sym->n_value, file->endian);
	new_symbol->debug = sym->n_type & N_STAB;
	new_symbol->type = sym->n_type & N_TYPE;
	new_symbol->ext = sym->n_type & N_EXT;
	symbol_get_section(file, new_symbol, sym->n_sect);
	ret = symbol_to_tree(&file->symbols, new_symbol);
	if (ret == MALLOC_ERROR)
		free_symbol_data(new_symbol);
	return (ret ? ERROR : SUCCESS);
}

static int8_t		symbols_get_64(t_file_data *file)
{
	struct symtab_command	*sym_cmd;
	struct nlist_64			*sym_tab;
	uint32_t				i;
	uint32_t				nsyms;
	uint32_t				symoff;

	if (is_inside_file_rel(file->size, file->off_symcmd,
			sizeof(*sym_cmd)) == FALSE)
		return (print_corrupted_file_error(file));
	sym_cmd = (struct symtab_command*)(file->content + file->off_symcmd);
	nsyms = endian_wrap_u32(sym_cmd->nsyms, file->endian);
	symoff = endian_wrap_u32(sym_cmd->symoff, file->endian) + file->off_header;
	if (is_inside_file_rel(file->size, symoff,
			sizeof(*sym_tab) * nsyms) == FALSE)
		return (print_corrupted_file_error(file));
	sym_tab = (struct nlist_64*)(file->content + symoff);
	file->sym_str = (char*)file->content
		+ endian_wrap_u32(sym_cmd->stroff, file->endian) + file->off_header;
	file->str_size = endian_wrap_u32(sym_cmd->strsize, file->endian);
	i = -1;
	while (++i < nsyms)
		if (symbol_get_64(file, &sym_tab[i]))
			return (ERROR);
	return (SUCCESS);
}

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
			return (print_corrupted_file_error(file));
		lc = (struct load_command*)(file->content + offset);
		cmd = endian_wrap_u32(lc->cmd, file->endian);
		if (cmd == LC_SYMTAB)
			file->off_symcmd = offset;
		if (cmd == LC_SEGMENT_64)
			if (segment_parse_64(file, offset) == ERROR)
				return (ERROR);
		offset += endian_wrap_u32(lc->cmdsize, file->endian);
		i++;
	}
	return (file->off_symcmd ? SUCCESS : print_corrupted_file_error(file));
}

int8_t			handle_mh_64(t_file_data *file)
{
	struct mach_header_64	*header;
	int8_t					ret;

	file->bits = bits64;
	if (is_inside_file_rel(file->size, file->off_header, sizeof(*header))
		== FALSE)
		return (print_corrupted_file_error(file));
	header = (struct mach_header_64 *)(file->content + file->off_header);
	ret = load_commands_parse_64(file,
		endian_wrap_u32(header->ncmds, file->endian));
	if (ret == SUCCESS)
		ret = symbols_get_64(file);
	if (ret == SUCCESS)
		symbols_print(file);
	ft_btree_free(file->symbols, &free_symbol_data);
	return (ret);
}
