/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 03:26:56 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/09 17:29:59 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_insert_errors(t_error **root, t_error *new)
{
	if (new == NULL)
		return ;
	if ((*root) == NULL)
		(*root) = new;
	if (ft_strcmp((*root)->filename, new->filename) < 0)
		ft_insert_errors(&(*root)->right, new);
	else if (ft_strcmp((*root)->filename, new->filename) > 0)
		ft_insert_errors(&(*root)->left, new);
}

void	ft_sort_errors(char *error, char *filename, t_width *max, t_file **ptr)
{
	char	buff[300];
	t_error *new;

	if (!(new = ft_memalloc(sizeof(t_error))))
		return ;
	if (ptr != NULL && *ptr != NULL)
	{
		ft_memdel((void*)&(*ptr)->path);
		ft_memdel((void**)&(*ptr)->error);
		ft_memdel((void**)&(*ptr)->filename);
		ft_memdel((void*)ptr);
	}
	ft_memset(buff, 0, 300);
	ft_strlcat(buff, "ft_ls: ", sizeof(buff));
	ft_strlcat(buff, filename, sizeof(buff));
	ft_strlcat(buff, ": ", sizeof(buff));
	ft_strlcat(buff, error, sizeof(buff));
	free(error);
	new->filename = ft_strdup(filename);
	new->error = ft_strdup(buff);
	ft_insert_errors(&(max->errors), new);
}

void	ft_print_errors(t_error **root)
{
	if (root == NULL || *root == NULL)
		return ;
	ft_print_errors(&(*root)->left);
	ft_putendl((*root)->error);
	ft_print_errors(&(*root)->right);
	ft_memdel((void**)&(*root)->error);
	ft_memdel((void**)&(*root)->filename);
	ft_memdel((void**)root);
}
