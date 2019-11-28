/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagbits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:43:51 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/08 03:35:31 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_check_bit(int flag, uint postion)
{
	int mask;

	mask = flag >> postion;
	return (mask & 1);
}

void	ft_set_bit(int *flag, uint position)
{
	int mask;

	mask = 1 << position;
	*flag = *flag | mask;
}

void	ft_illegal_flag(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
	ft_putendl("usage: ft_ls [-alRrutG] [file ...]");
	exit(1);
}

int		ft_set_flags(int *flag, char *argv)
{
	uint	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i] == 'l')
			ft_set_bit(flag, LONGF_BIT);
		else if (argv[i] == 'R')
			ft_set_bit(flag, RECURSIVE_BIT);
		else if (argv[i] == 'a')
			ft_set_bit(flag, ALL_BIT);
		else if (argv[i] == 'r')
			ft_set_bit(flag, REVERSE_BIT);
		else if (argv[i] == 't')
			ft_set_bit(flag, TIME_MOD_BIT);
		else if (argv[i] == 'u')
			ft_set_bit(flag, TME_ACCESS_BIT);
		else if (argv[i] == 'G')
			ft_set_bit(flag, COLOR_BIT);
		else
			ft_illegal_flag(argv[i]);
		i++;
	}
	return (1);
}

void	ft_set_option(int *flag, int *option)
{
	*option = NAME;
	if (ft_check_bit(*flag, TME_ACCESS_BIT) && \
	ft_check_bit(*flag, TIME_MOD_BIT))
		*option = ACCESS_TIME;
	else if (ft_check_bit(*flag, TIME_MOD_BIT))
		*option = MOD_TIME;
}
