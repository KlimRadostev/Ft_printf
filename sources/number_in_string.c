/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_in_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:19:11 by kradoste          #+#    #+#             */
/*   Updated: 2018/08/16 20:19:01 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "printf.h"

intmax_t		get_number(va_list arg, int flag)
{
	intmax_t	val;

	if (flag == 3)
		return (va_arg(arg, long long));
	else if (flag == 4)
		return (va_arg(arg, long));
	else if (flag == 5)
		return (va_arg(arg, intmax_t));
	else if (flag == 6)
		return (va_arg(arg, size_t));
	val = va_arg(arg, int);
	if (flag == 0)
		val = (int)val;
	else if (flag == 1)
		val = (char)val;
	else if (flag == 2)
		val = (short)val;
	return (val);
}

static size_t	ft_get_len(intmax_t n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa_base(intmax_t n)
{
	char		*str;
	size_t		len;
	intmax_t	tmp;

	if ((uintmax_t)n == -9223372036854775808ULL)
		return (ft_strdup("-9223372036854775808"));
	len = ft_get_len(n);
	tmp = n;
	if (n < 0)
	{
		tmp = -n;
		len++;
	}
	if (!(str = ft_strnew(len)))
		return (NULL);
	str[--len] = tmp % 10 + '0';
	while (tmp /= 10)
		str[--len] = tmp % 10 + '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}

uintmax_t	get_uflag(uintmax_t value, int flag)
{
	if (flag == 0)
		return ((unsigned int)value);
	else if (flag == 1)
		return ((unsigned char)value);
	else if (flag == 2)
		return ((unsigned short int)value);
	else if (flag == 3)
		return ((unsigned long long)value);
	else if (flag == 4)
		return ((unsigned long)value);
	else if (flag == 5)
		return ((uintmax_t)value);
	return ((size_t)value);
}

char		*ft_itoa_ubase(uintmax_t value, int base, int flag, int key)
{
	char		*s;
	uintmax_t	n;
	int			i;
	
	n = get_uflag(value, flag);
	i = 1;
	while ((n /= base) >= 1)
		i++;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	n = get_uflag(value, flag);
	while (i--)
	{
		if (key == 1)
			s[i] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
		else
			s[i] = (n % base < 10) ? n % base + '0' : n % base + 'a' - 10;			
		n /= base;
	}
	return (s);
}
