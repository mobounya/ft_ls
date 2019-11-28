/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:30:17 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/09 18:10:46 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <unistd.h>
# include <errno.h>
# include <time.h>

# define LONGF_BIT		0
# define RECURSIVE_BIT	1
# define ALL_BIT		2
# define REVERSE_BIT	3
# define TIME_MOD_BIT	4
# define TME_ACCESS_BIT	5
# define NOTSORT_BIT	6
# define GROUPNAME_BIT	7
# define LISTDIR_BIT	8
# define COLOR_BIT		9

# define ACCESS_TIME	1
# define MOD_TIME		2
# define NAME			3

# define RIGHT			1
# define LEFT			0

# define MAX_PATH		4097

# define S_CURRENT_ROOT(file)	(ft_strcmp(".", file) && ft_strcmp("..", file))
# define RESET() (ft_putstr("\e[0m"))

typedef unsigned int	t_uint;

typedef struct	s_stat
{
	mode_t		st_mode;
	nlink_t		nlink;
	uid_t		uid;
	char		*uname;
	gid_t		gid;
	char		*gname;
	time_t		atime;
	time_t		modtime;
	off_t		size;
	long		st_blocks;
	dev_t		num;
}				t_stat;

typedef struct	s_error
{
	char			*filename;
	char			*error;
	struct s_error	*left;
	struct s_error	*right;
}				t_error;

typedef struct	s_width
{
	uint		mx_links;
	uint		mx_uname;
	uint		mx_gname;
	uint		mx_size;
	long		st_blocks;
	uint		dirs_count;
	uint		files_count;
	acl_t		acl;
	int			major;
	int			minor;
	ssize_t		size;
	int			st_stat;
	t_error		*errors;
	int			flag;
}				t_width;

typedef struct	s_file
{
	char			*filename;
	char			*path;
	t_stat			*stat;
	char			*color;
	t_width			*max;
	acl_t			acl;
	ssize_t			size;
	char			*error;
	int				major;
	int				minor;
	struct s_file	*dir_files;
	struct s_file	*left;
	struct s_file	*right;
}				t_file;

int				ft_listing(t_file *node, t_width *max);
void			get_filename(char *pathname);
t_file			*btree_create_node(void *item);
void			ft_set_bit(int *flag, unsigned int position);
int				ft_set_flags(int *flag, char *argv);
int				ft_parse_argv(char **argv, int *flag,\
				t_file **root, int *option);
int				ft_check_bit(int flag, unsigned int postion);
void			ft_exec_l(t_file *root, int *flag);
t_file			*ft_read(char *filename, int option, int *flag, t_width *max);
void			ft_insert_data(t_file **root, t_file *new, int (*cmpf)\
				(t_file *file1, t_file *file2, int option), int option);
int				ft_compare(t_file *file1,\
				t_file *file2, int sort_option);
void			t_file_apply(t_file *root, int start_point,\
				int dir, t_width *max);
void			ft_set_option(int *flag, int *option);
int				ft_read_dir(t_file **node, char *dirpath,\
				int *flag, int option);
void			ft_start(t_file **strt, t_file **fnsh, t_file *n, int start);
void			ft_ls(t_file *root, int start_point, int dir, t_width *max);
int				ft_digits(uint n);
void			ft_print_many(char c, int d);
void			ft_print_color(t_file *node, int newline);
void			ft_print_path(const char *file);
void			ft_print_total(long st_blocks);
void			ft_free_tfile(t_file **node);
void			ft_free(t_file **root);
char			*ft_get_path(char *filename);
char			*ft_get_color(mode_t st_mode);
t_stat			*ft_getstat(struct stat file_info);
void			ft_get_max(t_width *max, t_file *node);
void			ft_recursive(t_file **root, int *flag, t_width *max, int rbit);
void			ft_print_name(t_file *node, t_width *max);
void			ft_print_size(t_file *node, t_width *max);
void			ft_print_maj_min(t_file *node,\
				t_width *max);
void			ft_set_mj_mn(t_file *file, struct stat file_info);
int				ft_compare(t_file *file1, t_file *file2,\
				int sort_option);
t_file			*ft_get_data(char **entrypath, int *flag,\
				char *d_name, t_width *max);
t_file			*ft_read_file(char *filename, t_width *max);
void			ft_get_xattr(const char *pathname, t_file *node);
void			execute(int flag, t_file *node, int rbit, int dir);
void			ft_recursive(t_file **root, int *flag, t_width *max, int rbit);
void			ft_sort_errors(char *error, char *filename, \
				t_width *max, t_file	**ptr);
void			ft_print_error(char *filename, char *error);
void			ft_get_time(time_t c_time, time_t modtime);
void			ft_is_perm(mode_t val, int exec, int id_or_stic, char c);
void			ft_print_errors(t_error **root);
#endif
