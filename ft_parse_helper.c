/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:08:02 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/08 01:45:43 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_maj_min(t_file *node, t_width *max)
{
	ft_print_many(' ', ft_digits(max->major) - ft_digits(node->major));
	ft_putnbr(node->major);
	ft_putchar(',');
	ft_print_many(' ', ft_digits(max->minor) - ft_digits(node->minor) + 1);
	ft_putnbr(node->minor);
	ft_putstr("  ");
}

void	ft_print_size(t_file *node, t_width *max)
{
	uint	total;

	total = 0;
	if (max->major >= 0 && max->minor >= 0)
		total = ft_digits(max->major) + ft_digits(max->minor) + 1;
	ft_print_many(' ', ft_digits(max->mx_size)\
		- ft_digits(node->stat->size) + total);
	ft_putnbr(node->stat->size);
	ft_putstr("  ");
}

int		ft_compare(t_file *file1, t_file *file2, int sort_option)
{
	if (sort_option == NAME)
		return (ft_strcmp(file1->filename, file2->filename));
	else if (!file1->stat && !file2->stat)
		return (ft_strcmp(file1->filename, file2->filename));
	else if (sort_option == ACCESS_TIME)
	{
		if (file1->stat->atime == file2->stat->atime)
			return (ft_compare(file1, file2, NAME));
		else
			return (file2->stat->atime - file1->stat->atime);
	}
	else if (sort_option == MOD_TIME)
	{
		if (file1->stat->modtime == file2->stat->modtime)
			return (ft_compare(file1, file2, NAME));
		else
			return (file2->stat->modtime - file1->stat->modtime);
	}
	return (sort_option);
}

void	ft_insert_data(t_file **root, t_file *new, \
		int (*cmpf)(t_file *file1, t_file *file2, int option), int option)
{
	if (new == NULL)
		return ;
	if ((*root) == NULL)
		(*root) = new;
	if ((cmpf)(new, *root, option) > 0)
		ft_insert_data(&(*root)->right, new, cmpf, option);
	else if ((cmpf)(new, *root, option) < 0)
		ft_insert_data(&(*root)->left, new, cmpf, option);
}

void	ft_set_mj_mn(t_file *file, struct stat file_info)
{
	file->minor = minor(file_info.st_rdev);
	file->major = major(file_info.st_rdev);
}
