/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:47:38 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/15 18:18:31 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int8_t	is_inside_file_rel(int32_t size, uint32_t offset, uint32_t to_read)
{
	return (!(offset + to_read < offset || size - (offset + to_read) < 0));
}

int8_t	is_inside_file_abs(void* addr1, int32_t size, void* addr2)
{
	void *eof;

	eof = addr1 + size;
	return (!(eof < addr1 || addr2 < addr1 || addr2 > eof));
}

int8_t	is_secure_str(void *addr, int32_t size, char *str)
{
	size_t	n;

	if (is_inside_file_abs(addr, size, (void*)str) ==  FALSE)
		return (FALSE);
	n = size - ((void*)str - addr);
	if (!ft_strnchr(str, 0, n))
		return (FALSE);
	return (TRUE);
}