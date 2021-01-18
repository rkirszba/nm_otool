/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:09:03 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/18 19:53:40 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static uint32_t	byte_swap_u32(uint32_t nb)
{
	return (((nb >> 0x18) & 0xff)
		| ((nb >> 0x08) & 0xff00)
		| ((nb << 0x08) & 0xff0000)
		| ((nb << 0x18) & 0xff000000));
}

static uint64_t	byte_swap_u64(uint64_t nb)
{
	return (((nb >> 0x38) & 0xff)
		| ((nb >> 0x28) & 0xff00)
		| ((nb >> 0x18) & 0xff0000)
		| ((nb >> 0x08) & 0xff000000)
		| ((nb << 0x08) & 0xff00000000)
		| ((nb << 0x18) & 0xff0000000000)
		| ((nb << 0x28) & 0xff000000000000)
		| ((nb << 0x38) & 0xff00000000000000));
}

uint32_t		endian_wrap_32(uint32_t nb, t_endian endian)
{
	if (endian == little)
		return (nb);
	return (byte_swap_u32(nb));
}

uint64_t		endian_wrap_64(uint64_t nb, t_endian endian)
{
	if (endian == little)
		return (nb);
	return (byte_swap_u64(nb));
}
