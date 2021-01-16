/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:30:53 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/16 18:41:03 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"



#include <stdio.h>
void	print_names(void *data)
{
	printf("%016llx %s\n", ((t_symbol_data*)data)->value, ((t_symbol_data*)data)->name);
}

static int8_t	load_commands_parse64(t_file_data *file, uint32_t ncmds)
{
	uint32_t			i;
	int32_t				offset;
	struct load_command	*lc;	
	
	i = 0;
	offset = file->off_header + sizeof(struct mach_header_64);
	while (i < ncmds)
	{
		if (is_inside_file_rel(file->size, offset, sizeof(*lc)) == FALSE)
			return (print_corrupted_file_error(file->name));
		lc = (struct load_command*)(file->content + offset);
		if (lc->cmd == LC_SYMTAB)
			file->off_symtab = offset;
		if (lc->cmd == LC_SEGMENT_64)
			if (segment_parse64(file, offset) == ERROR)
				return (ERROR);
		offset += lc->cmdsize;
		i++;
	}
	return (file->off_symtab ? SUCCESS : print_corrupted_file_error(file->name));
}

int8_t			handle_mh64(t_options *options, t_file_data *file)
{
	struct mach_header_64	*header;
	int8_t					ret;

	if (is_inside_file_rel(file->size, file->off_header, sizeof(*header)) == FALSE)
		return (print_corrupted_file_error(file->name));
	header = (struct mach_header_64 *)(file->content + file->off_header);
	ret = load_commands_parse64(file, header->ncmds);
	if (ret == SUCCESS)
		ret = symbols_get64(options, file);
	// if (ret == SUCCESS)
	// 	symbols_print64(file->symbols);
	//begin test
	if (ret == SUCCESS)
		ft_btree_inorder(file->symbols, &print_names);
	else
		printf("FAILURE\n");
	//end test

	ft_btree_free(file->symbols, &free_symbol_data);
	return (ret);
}

int8_t	handle_fat64(t_options *options, t_file_data *file)
{
	(void)options;
	(void)file;
	return (SUCCESS);
}
