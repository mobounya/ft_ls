/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setuid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:31:42 by mobounya          #+#    #+#             */
/*   Updated: 2019/10/29 17:31:54 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_is_perm(mode_t val, int exec, int id_or_stic, char c)
{
	if ((val & id_or_stic) && (val & exec))
		ft_putchar(c);
	else if (val & id_or_stic)
		ft_putchar(c - 32);
	else
		(val & exec) ? ft_putchar('x') : ft_putchar('-');
}
