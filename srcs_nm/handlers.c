/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:12:51 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/14 19:17:18 by rkirszba         ###   ########.fr       */
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

	if (is_sane(file->size, 0, sizeof(*header)) == FALSE)
		return (print_corrupted_file_error(file->name));
	header = (struct mach_header *)(file->content);
	ncmds = header->ncmds;
	ret = symbols_get(options, file, ncmds);
	// if (ret == SUCCESS)
	// 	symbols_print32(file->symbols);
	ft_btree_free(file->symbols, &free_symbols);
	return (ret);
}

int8_t	handle_mh64(t_options *options, t_file_data *file)
{
	struct mach_header_64	*header;
	uint32_t				ncmds;
	int8_t					ret;

	if (is_sane(file->size, 0, sizeof(*header)) == FALSE)
		return (print_corrupted_file_error(file->name));
	header = (struct mach_header_64 *)(file->content);
	ncmds = header->ncmds;
	ret = symbols_get(options, file, ncmds);
	// if (ret == SUCCESS)
	// 	symbols_print64(file->symbols);
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