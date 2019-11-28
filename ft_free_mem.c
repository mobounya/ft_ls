/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:42:01 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/08 03:28:54 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_tfile(t_file **node)
{
	if (node == NULL || *node == NULL)
		return ;
	ft_memdel((void*)&(*node)->filename);
	ft_memdel((void*)&(*node)->path);
	if ((*node)->stat)
	{
		ft_memdel((void*)&(*node)->stat->gname);
		ft_memdel((void*)&(*node)->stat->uname);
	}
	ft_memdel((void*)&(*node)->max);
	ft_memdel((void*)&(*node)->color);
	ft_memdel((void**)&(*node)->stat);
	ft_memdel((void**)&(*node)->error);
	if ((*node)->acl)
		acl_free((*node)->acl);
	ft_memdel((void**)node);
}

void	ft_free(t_file **root)
{
	if (*root == NULL)
		return ;
	ft_free(&(*root)->left);
	ft_free(&(*root)->right);
	if ((*root)->dir_files)
		ft_free(&(*root)->dir_files);
	ft_free_tfile(root);
}
