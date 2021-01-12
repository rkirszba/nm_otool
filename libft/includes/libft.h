/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:32:42 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/12 20:08:48 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H


# include <stdlib.h>


typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}				t_list;


typedef struct	s_btree
{
	void			*data;
	struct s_btree	*left;
	struct s_btree	*right;
}				t_btree;


/*
** String Operations
*/

size_t			ft_strlen(const char *s);

/*
** Linked lists
*/

t_list			*ft_list_new(void *data);
void			ft_list_append(t_list **head, t_list *node);
void			list_prepend(t_list **head, t_list *node);
void			ft_list_free(t_list *head, void (*f)(void*));

/*
** Binary Trees
*/

t_btree			*ft_btree_new(void *data);
void			ft_btree_insert(t_btree **head, t_btree *node, int (*f)(void *, void *));
void			ft_btree_inorder(t_btree *node, void (*f)(void *));

#endif