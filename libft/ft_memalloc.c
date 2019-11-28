/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 06:51:43 by mobounya          #+#    #+#             */
/*   Updated: 2019/10/08 14:57:57 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*mem;

	i = 0;
	if ((mem = malloc(size)) == NULL)
		return (NULL);
	while (i < size)
	{
		((unsigned char*)mem)[i] = 0;
		i++;
	}
	return (mem);
}
