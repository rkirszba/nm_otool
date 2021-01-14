/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:40:57 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/14 18:45:25 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_free(t_btree *node, void (*f)(void*))
{
	if (!node)
		return ;
	ft_btree_free(node->left, f);
	f(node->data);
	free(node);
	ft_btree_free(node->right, f);
}