/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:45:33 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/19 20:53:14 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	
	if (!s1)
		return (NULL);
	if (!(dup = (char*)malloc(n + 1)))
		return (NULL);
	dup[n + 1] = '\0';
	return (ft_strncpy(dup, s1, n));
}
