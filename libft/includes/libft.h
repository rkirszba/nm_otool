/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:32:42 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/13 15:03:06 by rkirszba         ###   ########.fr       */
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
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char * dst, const char * src, size_t len);
char			*ft_strcat(char *restrict s1, const char *restrict s2);
char			*ft_strchr(const char *s, int c);

/*
** Memory operations
*/

void			*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

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
void			ft_btree_inrorder(t_btree *node, void (*f)(void *));

#endif