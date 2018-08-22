/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:08:13 by kradoste          #+#    #+#             */
/*   Updated: 2018/08/21 18:00:49 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <../libft/libft.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct	s_printf
{
	va_list	ap;
	char	*buf;
	int		god;
	int		len;
}				t_printf;

uintmax_t		get_unumber(va_list arg, int len, int large);
intmax_t		get_number(va_list arg, int len, int large);
char			*ft_itoa_base(intmax_t n);
char			*ft_itoa_ubase(uintmax_t value, int base, int key);
void			parse_lag(t_printf *p);
void			print_str(char *str, t_printf *p, int identity);
void			print_char(char c, t_printf *p);
int				ft_printf(const char *format, ...);

#endif
