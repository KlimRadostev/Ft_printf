/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 21:24:35 by kradoste          #+#    #+#             */
/*   Updated: 2018/08/22 14:26:07 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	print_char(char c, t_printf *p)
{
	p->god++;
	write(0, &c, 1);
}

void	print_str(char *str, t_printf *p, int identity)
{
	int	i;

	i = 0;
	if (!str)
		print_str("(null)", p, 0);
	else if (!str[i] && !identity)
		print_char(0, p);
	else if (str[i] && !identity)
		while (str[i])
			print_char(str[i++], p);
}

//-fsanitize=address 

