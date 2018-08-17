/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 13:46:40 by kradoste          #+#    #+#             */
/*   Updated: 2018/08/16 01:52:51 by kradoste         ###   ########.fr       */
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

int		parse_specifier(char *flag)
{
	if (*(flag - 2) == 'h' && *(flag - 1) == 'h')
		return (1);
	else if (*(flag - 1) == 'h')
		return (2);
	else if (*(flag - 2) == 'l' && *(flag - 1) == 'l')
		return (3);
	else if (*(flag - 1) == 'l')
		return (4);
	else if (*(flag - 1) == 'j')
		return (5);
	else if (*(flag - 1) == 'z')
		return (6);
	return (0);
}

void	store_buffer(t_printf *p, char *flag)
{
	intmax_t	value;

	p->spec = parse_specifier(flag);
	if (*flag == 's' || *flag == 'S')
	{
		if (!(p->buf = ft_alloc(p->buf, va_arg(p->ap, char *))))
			p->buf = NULL;
	}
	else if (*flag == 'd' || *flag == 'D' || *flag == 'i')
	{
		value = get_number(p->ap, p->spec);
		p->buf = ft_itoa_base(value);
	}
	else if (*flag == 'o' || *flag == 'O')
		p->buf = ft_itoa_ubase(va_arg(p->ap, uintmax_t), 8, p->spec, 0);
	else if (*flag == 'u' || *flag == 'U')
		p->buf = ft_itoa_ubase(va_arg(p->ap, uintmax_t), 10, p->spec, 0);
	else if (*flag == 'x')
		p->buf = ft_itoa_ubase(va_arg(p->ap, uintmax_t), 16, p->spec, 0);
	else if (*flag == 'X')
		p->buf = ft_itoa_ubase(va_arg(p->ap, uintmax_t), 16, p->spec, 1);
	else if (*flag == 'c' || *flag == 'C')
		p->buf = ctos(va_arg(p->ap, int));
	else if (*flag == '%')
		p->buf = ctos('%');
}

int		parse_flag(t_printf *p, char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr("sSdDioOuUxXcC%", str[i]))
		i++;
	store_buffer(p, &str[i]);
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
	va_start(p->ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			i += parse_flag(p, (char *)&format[i]);
		}
		else
			print_char(format[i], p);
		i++;
	}
	return (p->god);
}
