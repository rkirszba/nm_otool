/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:32:42 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/19 20:53:06 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
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
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_strnchr(const char *s, int c, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/*
** Writing operations
*/

void			ft_putstr(const char *s);
void			ft_putstr_fd(const char *s, int fd);

/*
** Memory operations
*/

void			*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);


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
void			ft_btree_free(t_btree *node, void (*f)(void*));

#endif