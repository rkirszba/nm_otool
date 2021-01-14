/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:24:12 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/14 13:29:28 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/errno.h>
# include <libft.h>

/*
** Basics
*/	

# define ERROR				1
# define SUCCESS			0
# define TRUE				1
# define FALSE				0

/*
** Errors
*/

# define MALLOC_ERROR		-1
# define MUNMAP_ERROR		-1
# define NB_ERRORS			3


# define DEFAULT_FILE		"a.out"

# define OPTIONS			"abcdef"

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
	uint8_t		*content;
	int32_t		size;
}				t_file_data;

typedef struct	s_error
{
	int			nb;
	char		*message;
}				t_error;


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
** Files processing routine
*/

int8_t			files_process(t_options *options, t_list *files);
int8_t			file_process(t_options *options, t_file_data *file);

/*
** Error functions
*/

int8_t			print_malloc_error(void);
int8_t			print_munmap_error(void);
int8_t			print_options_error(char wrong_option);
int8_t			print_file_error(char *file_name);

#endif