/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:21:52 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/25 16:27:20 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/errno.h>
# include <mach-o/loader.h>
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

/*
** Section and segments name
*/

# define SEG_TEXT			"__TEXT"
# define SEG_DATA			"__DATA"

# define SECT_TEXT			"__text"
# define SECT_DATA			"__data"

/*
** Others
*/

# define BAD_STR_INDEX		"bad string index"

# define OPTIONS			"dt"

# define HEX_BASE			"0123456789abcdef"

# define NB_MAGICS			8
# define NB_HANDLERS		4


typedef enum	e_bits
{
	bits32,
	bits64
}				t_bits;

typedef enum	e_endian
{
	little	= 0,
	big		= 1 
}				t_endian;

typedef struct	s_options
{
	uint8_t	d;
	uint8_t	t;
}				t_options;

typedef struct	s_file_data
{
	char		*name;
	char		*arch;
	uint8_t		fat;
	uint8_t		multi_arch;
	uint8_t		*content;
	t_endian	endian;
	t_bits		bits;
	uint64_t	size;
	uint64_t	off_header;
	uint64_t	off_text;
	uint64_t	size_text;
	uint64_t	off_data;
	uint64_t	size_data;
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
** Static variables
*/

t_options		*static_options(void);
t_file_data		**static_file(void);
uint32_t		*static_magics(void);

/*
** Arguments parser functions
*/

int8_t			get_options(int ac, char **av, int *arg_offset);
int8_t			get_files(t_list **list, int ac, char **av, int arg_offset);

/*
** Handlers dispatcher
*/

int8_t			dispatcher(t_file_data *file);

/*
** Handlers
*/

// int8_t			handle_mh_32(t_file_data *file);
int8_t			handle_mh_64(t_file_data *file);
// int8_t			handle_fat_32(t_file_data *file);
// int8_t			handle_fat_64(t_file_data *file);

/*
** Print functions
*/

void			sections_print(t_file_data *file);

/*
** Security checks
*/

int8_t			is_inside_file_rel(uint64_t size, uint64_t offset,
				uint64_t to_read);
int8_t			is_inside_file_abs(void* addr1, uint64_t size, void* addr2);		

/*
** Endian wrappers
*/

uint32_t		endian_wrap_u32(uint32_t nb, t_endian endian);
uint64_t		endian_wrap_u64(uint64_t nb, t_endian endian);

/*
** Error functions
*/

int8_t			print_malloc_error(void);
int8_t			print_munmap_error(void);
int8_t			print_options_error(char wrong_option, char *flag);
int8_t			print_usage(void);
int8_t			print_loading_file_error(char *file_name);
int8_t			print_invalid_file_error(t_file_data *file);
int8_t			print_corrupted_file_error(t_file_data *file);

/*
** Free functions
*/

void			free_file_data(void *data);

#endif