/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:24:12 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/13 19:44:05 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <libft.h>

/*
** Basics
*/	

# define ERROR				1
# define FAILURE			1
# define SUCCESS			0
# define TRUE				1
# define FALSE				0




# define DEFAULT_FILE	"a.out"

# define OPTIONS		"abcdef"

typedef struct	s_options
{
	u_int8_t	a;
	u_int8_t	b;
	u_int8_t	c;
	u_int8_t	d;
	u_int8_t	e;
	u_int8_t	f;
}				t_options;

typedef struct	s_file_data
{
	char		*name;
}				t_file_data;



/*
** Main
*/

int				main(int ac, char **av);

/*
** Arguments parser functions
*/

int8_t			get_options(int ac, char **av, t_options *options, int *arg_offset);
int8_t			get_files(t_list **list, int ac, char **av, int arg_offset);

/*
** Error functions
*/

int8_t	print_malloc_error(void);
int8_t	print_options_error(char wrong_option);

#endif