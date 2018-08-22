/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 13:46:40 by kradoste          #+#    #+#             */
/*   Updated: 2018/08/22 15:26:00 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

char	*ctos(char c)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * 2)))
		return ((void *)0);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_alloc(char *buf, char *str)
{
	int	len;

	if (str)
	{
		len = 0;
		while (str[len])
			len++;
		if (!(buf = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		len = -1;
		while (str[++len])
			buf[len] = str[len];
		buf[len] = str[len];
		return (buf);
	}
	else
		return (NULL);
}

int		parse_length(char *spec)
{
	if (*(spec - 2) == 'h' && *(spec - 1) == 'h')
		return (1);
	else if (*(spec - 1) == 'h')
		return (2);
	else if (*(spec - 2) == 'l' && *(spec - 1) == 'l')
		return (3);
	else if (*(spec - 1) == 'l')
		return (4);
	else if (*(spec - 1) == 'j')
		return (5);
	else if (*(spec - 1) == 'z')
		return (6);
	return (0);
}

void	store_buffer(t_printf *p, char *spec, int *identity)
{
	intmax_t	value;
	uintmax_t	valor;

	p->len = parse_length(spec);
	(*spec == 'c' || *spec == 'C') && (p->buf = ctos(va_arg(p->ap, int)));
	(*spec == '%') && (p->buf = ft_strdup("%"));
	if (*spec == 's' || *spec == 'S')
	{
		if (!(p->buf = ft_alloc(p->buf, va_arg(p->ap, char *))))
			p->buf = NULL;
		(p->buf && p->buf[0] == 0) && (*identity = 1);
	}
	else
	{
		if (*spec == 'd' || *spec == 'D' || *spec == 'i')
		{
			value = (*spec == 'D') ? get_number(p->ap, p->len, 1) : get_number(p->ap, p->len, 0);
			p->buf = ft_itoa_base(value);
		}
		else
		{
			valor = (*spec == 'U') ? get_unumber(p->ap, p->len, 1) : get_unumber(p->ap, p->len, 0);
			(*spec == 'o' || *spec == 'O') && (p->buf = ft_itoa_ubase(valor, 8, 0));
			(*spec == 'u' || *spec == 'U') && (p->buf = ft_itoa_ubase(valor, 10, 0));
			(*spec == 'x') && (p->buf = ft_itoa_ubase(valor, 16, 0));
			(*spec == 'X') && (p->buf = ft_itoa_ubase(valor, 16, 1));
		}
	}
}
/*
char	*parse_width(char *str)
{
	
}
*/
int		parse_spec(t_printf *p, char *str)
{
	int	i;
	int identity;

	i = 0;
	while (!ft_strchr("sSdDioOuUxXcC%", str[i]))
		i++;
	identity = 0;
	store_buffer(p, &str[i], &identity);
	// parse flags here
//	parse_width(str);
	// parse width here
	// parse precision here
    // last part
	print_str(p->buf, p, identity);
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
