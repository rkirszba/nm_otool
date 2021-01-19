/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:30:53 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/19 20:56:24 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int8_t	symbol_get_64(t_file_data *file, struct nlist_64 *sym)
{
	t_symbol_data	*new_symbol;
	char			*name;
	uint32_t		n_strx;
	int8_t			ret;

	n_strx = endian_wrap_u32(sym->n_un.n_strx, file->endian);
	name = file->sym_str + n_strx;
	if (is_secure_str(file->content, file->size, name) == FALSE)
		return (print_corrupted_file_error(file)); //revoir conditino copier dans du doc
	if (!(new_symbol = (t_symbol_data*)malloc(sizeof(*new_symbol))))
		return (print_malloc_error());
	ft_bzero(new_symbol, sizeof(*new_symbol));
	if (!(new_symbol->name = ft_strdup((n_strx) ? name : "")))
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

	if (is_inside_file_rel(file->size, file->off_symcmd, sizeof(*sym_cmd)) == FALSE)
		return (print_corrupted_file_error(file));
	sym_cmd = (struct symtab_command*)(file->content + file->off_symcmd);
	nsyms = endian_wrap_u32(sym_cmd->nsyms, file->endian);
	symoff = endian_wrap_u32(sym_cmd->symoff, file->endian) + file->off_header;
	if (is_inside_file_rel(file->size, symoff, sizeof(*sym_tab) * nsyms) == FALSE)
		return (print_corrupted_file_error(file));
	sym_tab = (struct nlist_64*)(file->content + symoff);
	file->sym_str = (char*)file->content
		+ endian_wrap_u32(sym_cmd->stroff, file->endian) + file->off_header;
	i = 0;
	while (i < nsyms)
	{
		if (symbol_get_64(file, &sym_tab[i]))
			return (ERROR);
		i++;
	}
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
	printf("HELLO\n");
	if (is_inside_file_rel(file->size, file->off_header, sizeof(*header))
		== FALSE)
		return (print_corrupted_file_error(file));
	header = (struct mach_header_64 *)(file->content + file->off_header);
	ret = load_commands_parse_64(file,
		endian_wrap_u32(header->ncmds, file->endian));
	printf("HELLO\n");
	if (ret == SUCCESS)
		ret = symbols_get_64(file);
	if (ret == SUCCESS)
		symbols_print(file);
	ft_btree_free(file->symbols, &free_symbol_data);
	return (ret);
}
