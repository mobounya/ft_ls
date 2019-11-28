/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:30:11 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/09 22:18:14 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(t_file *root, int start_point, int dir, t_width *max)
{
	t_file		*start;
	t_file		*finish;
	static int	s = -1;

	if (root == NULL)
		return ;
	s = (s == -1) ? max->dirs_count : s;
	ft_start(&start, &finish, root, start_point);
	ft_ls(start, start_point, dir, max);
	if (((!dir) && !S_ISDIR(root->stat->st_mode)) || dir == 3)
		ft_print_color(root, 1);
	else if (dir && root->stat && S_ISDIR(root->stat->st_mode))
	{
		if (max && max->dirs_count + max->files_count > 1)
			ft_print_path(root->filename);
		if (root->error)
			ft_print_error(root->filename, root->error);
		else
		{
			s--;
			ft_ls(root->dir_files, start_point, 3, max);
			ft_putstr(s == 0 ? "" : "\n");
		}
	}
	ft_ls(finish, start_point, dir, max);
}

void	ft_exec_r(t_file **root, int flag)
{
	int		rbit;

	rbit = ft_check_bit(flag, REVERSE_BIT);
	if ((*root)->max && (*root)->max->files_count > 0)
		execute(flag, (*root), rbit, 0);
	if ((*root)->max && (*root)->max->files_count > 0
	&& (*root)->max->dirs_count > 0)
		ft_putchar('\n');
	if ((*root) && (*root)->max->dirs_count > 0)
		ft_recursive(root, &flag, (*root)->max, rbit);
}

void	ft_exec_ls(t_file *root, int flag)
{
	if (root->max && root->max->files_count > 0)
		ft_ls(root, ft_check_bit(flag, REVERSE_BIT), 0, root->max);
	if (root->max && root->max->files_count > 0 && root->max->dirs_count > 0)
		ft_putchar('\n');
	if (root->max && root->max->dirs_count > 0)
		ft_ls(root, ft_check_bit(flag, REVERSE_BIT), 1, root->max);
}

void	ft_read_insert(t_file **root, int option, int flag)
{
	t_file		*new;
	t_width		*max;

	if (!(max = ft_memalloc(sizeof(t_width))))
		return ;
	new = ft_read(".", option, &flag, max);
	new->max = max;
	ft_insert_data(root, new, ft_compare, option);
}

int		main(int argc, char **argv)
{
	int			flag;
	t_file		*root;
	int			option;

	root = NULL;
	flag = 0;
	if (argc < 2)
		ft_read_insert(&root, NAME, flag);
	else if (!ft_parse_argv(argv, &flag, &root, &option))
		return (1);
	if (root == NULL)
		ft_read_insert(&root, option, flag);
	if (ft_check_bit(flag, RECURSIVE_BIT))
	{
		ft_exec_r(&root, flag);
		return (0);
	}
	else if (ft_check_bit(flag, LONGF_BIT))
		ft_exec_l(root, &flag);
	else
		ft_exec_ls(root, flag);
	ft_free(&root);
	return (0);
}
