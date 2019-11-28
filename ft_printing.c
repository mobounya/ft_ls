/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:39:42 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/08 01:45:25 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_total(long st_blocks)
{
	ft_putstr("total ");
	ft_putnbr(st_blocks);
	ft_putchar('\n');
}

void	ft_print_path(const char *file)
{
	ft_putstr(file);
	ft_putendl(":");
}

void	ft_print_many(char c, int d)
{
	int		i;

	i = 0;
	while (i < d)
	{
		ft_putchar(c);
		i++;
	}
}

void	ft_print_color(t_file *node, int newline)
{
	if (node->color != NULL)
	{
		ft_putstr(node->color);
		ft_putstr(node->filename);
		RESET();
	}
	else
		ft_putstr(node->filename);
	if (newline)
		ft_putchar('\n');
}

void	ft_print_name(t_file *node, t_width *max)
{
	ft_print_many(' ', ft_digits(max->mx_links) - ft_digits(node->stat->nlink));
	ft_putnbr(node->stat->nlink);
	ft_putchar(' ');
	ft_putstr(node->stat->uname);
	ft_print_many(' ', max->mx_uname - ft_strlen(node->stat->uname) + 2);
	ft_putstr(node->stat->gname);
	ft_print_many(' ', max->mx_gname - ft_strlen(node->stat->gname) + 2);
}
