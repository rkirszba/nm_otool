/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:47:38 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/14 17:56:08 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int8_t	is_sane(int32_t size, uint32_t offset, uint32_t to_read)
{
	if (size - (offset + to_read) >= 0)
		return (TRUE);
	return (FALSE);
}