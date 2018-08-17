/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 21:24:35 by kradoste          #+#    #+#             */
/*   Updated: 2018/08/07 15:50:35 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	print_char(char c, t_printf *p)
{
	p->god++;
	write(1, &c, 1);
}

void	print_str(char *str, t_printf *p)
{
	int	i;

	i = 0;
	if (!str)
		print_str("(null)", p);
	else
		while (str[i])
			print_char(str[i++], p);
}

//-fsanitize=address 

