/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 21:24:35 by kradoste          #+#    #+#             */
/*   Updated: 2018/09/07 12:42:28 by kradoste         ###   ########.fr       */
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
	int	l;
	int	key;

	key = p->key;
	i = 0;
	l = ft_strlen(str);
	while (p->width > (l + p->key))
	{
		(p->zero && !p->dot) ? (print_char('0', p)) : (print_char(' ', p));
		p->width--;
	}
	if (str[i] || p->key)
		while (str[i] || p->key)
		{
			(p->key) && (p->key = 0);
			print_char(str[i++], p);
		}
	if (p->width < 0)
		while (p->width < (l * -1) - key)
		{
			print_char(' ', p);
			p->width++;
		}
}
