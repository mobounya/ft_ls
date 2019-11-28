/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:41:23 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/09 18:49:14 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	execute(int flag, t_file *node, int rbit, int dir)
{
	if (node == NULL)
		return ;
	rbit = ft_check_bit(flag, REVERSE_BIT);
	if (ft_check_bit(flag, LONGF_BIT) && node->stat)
	{
		ft_print_total(node->max->st_blocks);
		t_file_apply(node, rbit, dir, node->max);
	}
	else if (!ft_check_bit(flag, LONGF_BIT))
		ft_ls(node, rbit, dir, node->max);
}

void	print_header(t_file **root, int *flag, int sort_option, int i)
{
	char		*path;

	path = ft_strjoin((*root)->path, "/");
	if (i != 1)
		ft_putchar('\n');
	ft_print_path((*root)->path + (*(*root)->path == '/'));
	if (ft_read_dir(&(*root)->dir_files, path, flag, sort_option) != 0)
	{
		ft_putstr("ft_ls: ");
		ft_putstr((*root)->filename);
		ft_putstr(": ");
		perror(NULL);
	}
	free(path);
}

void	ft_recursive(t_file **root, int *flag, t_width *max, int rbit)
{
	int			sort_option;
	t_file		*start;
	t_file		*finish;
	static int	i = 0;

	if (*root == NULL)
		return ;
	ft_set_option(flag, &sort_option);
	ft_start(&start, &finish, *root, rbit);
	ft_recursive(&start, flag, max, rbit);
	i++;
	if ((*root)->dir_files)
	{
		if (i != 1)
			ft_putchar('\n');
		if (max && max->dirs_count + max->files_count > 1)
			ft_print_path((*root)->filename);
	}
	else if ((*root)->stat && S_ISDIR((*root)->stat->st_mode) \
	&& S_CURRENT_ROOT((*root)->filename))
		print_header(root, flag, sort_option, i);
	execute(*flag, (*root)->dir_files, rbit, 3);
	ft_recursive(&(*root)->dir_files, flag, max, rbit);
	ft_recursive(&finish, flag, max, rbit);
	ft_free_tfile(root);
}
