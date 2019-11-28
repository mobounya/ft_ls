/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:04:35 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/09 19:43:51 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	t_file_apply(t_file *root, int start_point,\
		int dir, t_width *max)
{
	t_file		*start;
	t_file		*finish;
	static int	s = -1;

	if (root == NULL)
		return ;
	s = (s == -1) ? max->dirs_count : s;
	ft_start(&start, &finish, root, start_point);
	t_file_apply(start, start_point, dir, max);
	if ((!dir && !S_ISDIR(root->stat->st_mode)) || dir == 3)
		ft_listing(root, max);
	else if (dir && S_ISDIR(root->stat->st_mode))
	{
		if (s-- && max && max->dirs_count + max->files_count > 1)
			ft_print_path(root->filename);
		if (root->error)
			ft_print_error(root->filename, root->error);
		else if (root->dir_files && root->dir_files->max->st_stat > 0)
		{
			ft_print_total(root->dir_files->max->st_blocks);
			t_file_apply(root->dir_files, start_point, 3, root->dir_files->max);
		}
		ft_putstr(s == 0 ? "" : "\n");
	}
	t_file_apply(finish, start_point, dir, max);
}

void	ft_print(t_file *node, t_width *max)
{
	char		*get_time;
	char		link[MAX_PATH];
	ssize_t		len;
	time_t		c_time;

	len = 0;
	ft_print_name(node, max);
	if (S_ISCHR(node->stat->st_mode) || S_ISBLK(node->stat->st_mode))
		ft_print_maj_min(node, max);
	else
		ft_print_size(node, max);
	time(&c_time);
	get_time = ctime(&(node->stat->modtime));
	get_time[10] = '\0';
	ft_putstr(get_time + 4);
	ft_get_time(c_time, node->stat->modtime);
	ft_print_color(node, 0);
	if (((len = readlink(node->path, link, 4096)) != -1))
	{
		ft_putstr(" -> ");
		link[len] = '\0';
		ft_putstr(link);
	}
	ft_putchar('\n');
}

void	ft_file(mode_t st_mode)
{
	if (S_ISDIR(st_mode))
		ft_putchar('d');
	else if (S_ISCHR(st_mode))
		ft_putchar('c');
	else if (S_ISBLK(st_mode))
		ft_putchar('b');
	else if (S_ISFIFO(st_mode))
		ft_putchar('p');
	else if (S_ISLNK(st_mode))
		ft_putchar('l');
	else
		ft_putchar('-');
}

int		ft_listing(t_file *node, t_width *max)
{
	mode_t			val;

	if (node->stat == NULL)
		return (-1);
	ft_file(node->stat->st_mode);
	val = (node->stat->st_mode & ~S_IFMT);
	(val & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	ft_is_perm(val, (val & S_IXUSR), (val & S_ISUID), 's');
	(val & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	ft_is_perm(val, (val & S_IXGRP), (val & S_ISGID), 's');
	(val & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	ft_is_perm(val, (val & S_IXOTH), (val & S_ISVTX), 't');
	if (node->size > 0)
		ft_putstr("@");
	else if (node->acl)
		ft_putstr("+");
	else if (max->acl || max->size)
		ft_putstr(" ");
	ft_putstr("  ");
	ft_print(node, max);
	return (0);
}

void	ft_exec_l(t_file *root, int *flag)
{
	int		rbit;

	rbit = ft_check_bit(*flag, REVERSE_BIT);
	if (root->max && root->max->files_count > 0)
		t_file_apply(root, rbit, 0, root->max);
	if (root->max && root->max->files_count > 0 && root->max->dirs_count > 0)
		ft_putchar('\n');
	if (root->max && root->max->dirs_count > 0)
		t_file_apply(root, rbit, 1, root->max);
}
