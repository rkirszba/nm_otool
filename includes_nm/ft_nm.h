/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:24:12 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/15 20:03:33 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/errno.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include "libft.h"

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
# define NB_ERRORS			4


# define DEFAULT_FILE		"a.out"

# define OPTIONS			"agjnopruPU"

# define NB_FORMATS			4

typedef enum	e_arch
{
	x32,
	x64
}				t_arch;

typedef enum	e_section
{
	none,
	test,
	data,
	bss,
	other
}				t_section;

typedef struct	s_options
{
	u_int8_t	a;
	u_int8_t	g;
	u_int16_t	j;
	u_int8_t	n;
	u_int8_t	o;
	u_int8_t	p;
	u_int8_t	r;
	u_int8_t	u;
	uint8_t		P;
	u_int8_t	U;
}				t_options;

typedef struct	s_file_data
{
	char		*name;
	uint8_t		*content;
	t_arch		arch;
	int32_t		size;
	int32_t		off;
	char		*sym_str;
	t_btree		*symbols;
}				t_file_data;

typedef struct	s_symbol_data
{
	char		*name;
	uint64_t	value;
	uint8_t		type;
	uint8_t		ext;
	t_section	sect;
}				t_symbol_data;


typedef struct	s_dispatcher
{
	uint32_t	magic;
	int8_t		(*fun)(t_options*, t_file_data*);
}				t_dispatcher;

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
int8_t			file_dispatcher(t_options *options, t_file_data *file);

/*
** Handlers
*/

int8_t			handle_mh32(t_options *options, t_file_data *file);
int8_t			handle_mh64(t_options *options, t_file_data *file);
int8_t			handle_fat32(t_options *options, t_file_data *file);
int8_t			handle_fat64(t_options *options, t_file_data *file);


/*
** Symbols getter
*/

int8_t			symbols_get_symtab_cmd_off(t_file_data *file, uint32_t ncmds);
int8_t			symbols_get_each64(t_options *options, t_file_data *file);
int8_t			symbol_add(t_options *options, t_file_data *file, struct nlist_64 *sym);
int8_t			symbol_to_tree(t_options *options, t_btree **head, t_symbol_data *symbol);



/*
** Symbols sorting functions
*/

int				(*symbol_get_sort_fun(t_options *options))(void*, void*);
int				symbol_num_sort(void *curs_data, void *node_data);
int				symbol_alpha_sort(void *curs_data, void *node_data);
int				symbol_no_sort(void *curs_data, void *node_data);


/*
** Security checks
*/

int8_t			is_inside_file_rel(int32_t size, uint32_t offset, uint32_t to_read);
int8_t			is_inside_file_abs(void* addr1, int32_t size, void* addr2);
int8_t			is_secure_str(void *addr, int32_t size, char *str);

/*
** Error functions
*/

int8_t			print_malloc_error(void);
int8_t			print_munmap_error(void);
int8_t			print_options_error(char wrong_option);
int8_t			print_loading_file_error(char *file_name);
int8_t			print_invalid_file_error(char *file_name);
int8_t			print_corrupted_file_error(char *file_name);


#endif