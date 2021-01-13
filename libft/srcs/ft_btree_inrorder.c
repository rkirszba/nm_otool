/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_inrorder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:43:18 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/13 15:02:37 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_inrorder(t_btree *node, void (*f)(void *))
{
	if (!node)
		return ;
	ft_btree_inorder(node->right, f);
	f(node->data);
	ft_btree_inorder(node->left, f);
}
