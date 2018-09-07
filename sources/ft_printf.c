/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 13:46:40 by kradoste          #+#    #+#             */
/*   Updated: 2018/09/07 12:39:03 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

int		parse_spec(t_printf *p, char *str)
{
	int	i;

	i = 0;
	p->width = 0;
	p->hash = 0;
	p->plus = 0;
	p->zero = 0;
	p->pre = -1;
	p->dot = 0;
	p->space = 0;
	while (!ft_strchr("sSdDioOuUxXcC%", str[i]))
		i++;
	p->len = parse_length(str, i);
	store_buffer(p, &str[i]);
	parse_width(str, p, i);
	parse_all(str, p, i);
	precision_completion(str, p, i);
	flags_completion(str, p, i);
	if (p->space && !p->plus && p->buf[0] != '-'
		&& (str[i] == 'd' || str[i] == 'D' || str[i] == 'i'))
		p->buf = str_append(" ", p->buf, 0, 1);
	print_str(p->buf, p);
	if (p->buf)
		free(p->buf);
	return (i);
}

int		ft_printf(const char *format, ...)
{
	t_printf	*p;
	int			i;

	if (!(p = (t_printf *)ft_memalloc(sizeof(t_printf) * 1)))
		return (0);
	i = 0;
	p->god = 0;
	p->key = 0;
	va_start(p->ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			i += parse_spec(p, (char *)&format[i]);
		}
		else
			print_char(format[i], p);
		i++;
	}
	return (p->god);
}
