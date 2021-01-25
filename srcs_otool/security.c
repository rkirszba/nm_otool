/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:47:02 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 15:12:30 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int8_t	is_inside_file_rel(uint64_t size, uint64_t offset,
		uint64_t to_read)
{
	if (offset + to_read < offset)
		return (FALSE);
	if (size <= offset + to_read)
		return (FALSE);
	return (TRUE);
}

int8_t	is_inside_file_abs(void* addr1, uint64_t size, void* addr2)
{
	void *eof;

	eof = addr1 + size;
	return (!(eof < addr1 || addr2 < addr1 || addr2 >= eof));
}
