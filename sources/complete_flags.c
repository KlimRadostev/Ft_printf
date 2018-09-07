/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:55:26 by kradoste          #+#    #+#             */
/*   Updated: 2018/09/07 12:23:22 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	parse_width(char *str, t_printf *p, int max)
{
	int	i;

	i = 0;
	while (str[i] && i < max && p->width == 0)
	{
		if (ft_strchr("123456789", str[i]) && str[i - 1] != '.')
			p->width = ft_atoi(&str[i]);
		i++;
	}
}

void	parse_all(char *str, t_printf *p, int max)
{
	int	i;

	i = 0;
	while (str[i] && i < max)
	{
		(str[i] == '-') && (p->width *= -1);
		(str[i] == '#') && (p->hash = 1);
		(str[i] == '+') && (p->plus = 1);
		(str[i] == '.') && (p->dot = 1);
		(str[i] == ' ') && (p->space = 1);
		(!ft_strchr("123456789.", str[i - 1]) && str[i] == '0') && (p->zero = 1);
		(str[i] == '.' && ft_strchr("0123456789", str[i + 1])) && (p->pre = ft_atoi(&str[i + 1]));
		(str[i] == '.' && !ft_strchr("0123456789", str[i + 1]) && p->pre == -1) && (p->pre = 0);
		i++;
	}
}

char	*og_str(char c, int len)
{
	char	*str;
	int		i;

	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return ((void *)0);
	i = 0;
	while (i < len + 1)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

char	*str_append(char *s1, char *s2, int f1, int f2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (ft_strdup(""));
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return ((void *)0);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	(f1) ? (free(s1)) : 0;
	(f2) ? (free(s2)) : 0;
	return (str);
}

char	*str_appendneg(char *s1, char *s2)
{
	char	*str;
	char	*neg;

	if (s1 == NULL || s2 == NULL)
		return (ft_strdup(""));
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return ((void *)0);
	if (!(neg = ft_strnew(2)))
		return ((void *)0);
	neg[0] = '-';
	neg[1] = 0;
	ft_strcpy(str, s1);
	ft_strcat(str, &s2[1]);
	free(s1);
	free(s2);
	return (str_append(neg, str, 1, 1));
}

char	*str_cut(char *s1, int len)
{
	char	*str;

	if (!(str = ft_strnew(len + 1)))
		return (NULL);
	ft_strncpy(str, s1, len);
	free(s1);
	return (str);
}

void	precision_completion(char *str, t_printf *p, int m)
{
	int	l;

	l = ft_strlen(p->buf);
	if (NUM(str[m]))
	{
		if (p->pre == 0 && p->buf[0] == '0')
			p->buf = ft_strdup("");
		else if (p->pre > l || (p->pre >= l && p->buf[0] == '-'))
		{
			if (p->buf[0] != '-')
				p->buf = str_append(og_str('0', (p->pre - l) - 1), p->buf, 1, 1);
			else
				p->buf = str_appendneg(og_str('0', p->pre - l), p->buf);
		}
		else if (p->width >= l && p->buf[0] == '-' && p->zero)
			p->buf = str_appendneg(og_str('0', (p->width - l) - 1), p->buf);
	}
	else if (str[m] == 's' || str[m] == 'S')
		if (p->pre < l && p->pre != -1)
			p->buf = str_cut(p->buf, p->pre);
}


void	flags_completion(char *str, t_printf *p, int m)
{
	int	l;

	l = ft_strlen(p->buf);
	if (p->plus == 1)
		if (p->buf[0] != '-' && (str[m] == 'd' || str[m] == 'D' || str[m] == 'i'))
		{
			if (p->zero == 1 && p->width > 0)
			{
				p->buf = str_append(og_str('0', (p->width - l) - 2), p->buf, 1, 1);
				p->width = 0;
			}
			p->buf = str_append("+", p->buf, 0, 1);
		}
	if (p->hash == 1)
	{
		if (p->buf[0] != '0' && p->buf[0] && (str[m] == 'x' || str[m] == 'X'))
		{
			if (p->zero == 1 && p->width > 0)
            {
                p->buf = str_append(og_str('0', (p->width - l) - 3), p->buf, 1, 1);
                p->width = 0;
			}
			if (str[m] == 'x')
				p->buf = str_append("0x", p->buf, 0, 1);
			else if (str[m] == 'X')
				p->buf = str_append("0X", p->buf, 0, 1);
		}
		else if (str[m] == 'o' || str[m] == 'O')
			p->buf = str_append("0", p->buf, 0, 1);
	}
}
