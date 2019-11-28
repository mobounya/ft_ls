/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:32:53 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/08 01:45:49 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_digits(uint n)
{
	int digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

void	ft_start(t_file **strt, t_file **fnsh, t_file *n, int start)
{
	if (n == NULL)
		return ;
	if (start == LEFT)
	{
		*strt = n->left;
		*fnsh = n->right;
	}
	else
	{
		*strt = n->right;
		*fnsh = n->left;
	}
}

char	*ft_get_path(char *filename)
{
	char	*path;

	if ((ft_strchr(filename, '/')) == NULL && \
	ft_strcmp(".", filename) && ft_strcmp("..", filename))
		path = ft_strjoin("./", filename);
	else
		path = ft_strdup(filename);
	return (path);
}

char	*ft_get_color(mode_t st_mode)
{
	mode_t			val;

	val = (st_mode & ~S_IFMT);
	if (S_ISDIR(st_mode))
		return (ft_strdup("\e[1;96m"));
	else if (S_ISCHR(st_mode))
		return (ft_strdup("\e[34;43m"));
	else if (S_ISBLK(st_mode))
		return (ft_strdup("\e[46;34m"));
	else if (S_ISFIFO(st_mode))
		return (ft_strdup("\e[33m"));
	else if (S_ISLNK(st_mode))
		return (ft_strdup("\e[35m"));
	else if (val & S_IXUSR)
		return (ft_strdup("\e[31m"));
	return (NULL);
}

void	ft_print_error(char *filename, char *error)
{
	ft_putstr("ft_ls: ");
	ft_putstr(filename);
	ft_putstr(": ");
	ft_putendl(error);
}
