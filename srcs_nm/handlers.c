/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:12:51 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/15 20:06:43 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	free_symbols(void *content)
{
	(void)content;
	return ;
}

int8_t	handle_mh32(t_options *options, t_file_data *file)
{
	struct mach_header	*header;
	uint32_t			ncmds;
	int8_t				ret;

	(void)options;
	if (is_inside_file_rel(file->size, file->off, sizeof(*header)) == FALSE)
		return (print_corrupted_file_error(file->name));
	header = (struct mach_header *)(file->content + file->off);
	file->off += sizeof(struct mach_header);
	ncmds = header->ncmds;
	ret = symbols_get_symtab_cmd_off(file, ncmds);
	// if (ret == SUCCESS)
	// 	ret = symbols_get_each32(options, file);
	// if (ret == SUCCESS)
	// 	symbols_print32(file->symbols);
	ft_btree_free(file->symbols, &free_symbols);
	return (ret);
}


#include <stdio.h>
void	print_names(void *data)
{
	printf("%016llx %s\n", ((t_symbol_data*)data)->value, ((t_symbol_data*)data)->name);
}

int8_t	handle_mh64(t_options *options, t_file_data *file)
{
	struct mach_header_64	*header;
	uint32_t				ncmds;
	int8_t					ret;

	if (is_inside_file_rel(file->size, file->off, sizeof(*header)) == FALSE)
		return (print_corrupted_file_error(file->name));
	header = (struct mach_header_64 *)(file->content + file->off);
	file->off += sizeof(struct mach_header_64);
	ncmds = header->ncmds;
	ret = symbols_get_symtab_cmd_off(file, ncmds);
	if (ret == SUCCESS)
		ret = symbols_get_each64(options, file);
	// if (ret == SUCCESS)
	// 	symbols_print64(file->symbols);

	if (ret == SUCCESS)
		ft_btree_inorder(file->symbols, &print_names);
	else
		printf("FAILURE\n");


	ft_btree_free(file->symbols, &free_symbols);
	return (ret);
}

int8_t	handle_fat32(t_options *options, t_file_data *file)
{
	(void)options;
	(void)file;
	return (0);
}

int8_t	handle_fat64(t_options *options, t_file_data *file)
{
	(void)options;
	(void)file;
	return (0);
}
