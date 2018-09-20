/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:08:13 by kradoste          #+#    #+#             */
/*   Updated: 2018/09/20 12:25:53 by kradoste         ###   ########.fr       */
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
	int		width;
	int		hash;
	int		plus;
	int		zero;
	int		pre;
	int		dot;
	int		space;
	int		key;
}				t_printf;

# define UNS(x) (x == 'u' || x == 'U')
# define INT(x) (x == 'i' || x == 'd' || x == 'D')
# define HEO(x) (x == 'x' || x == 'X' || x == 'o' || x == 'O')
# define NUM(x) (UNS(x) || HEO(x) || INT(x))
# define LET(x) (x == 'c' || x == 'S' || x == 's' || x == 'C')

void			initialize_vars(t_printf *p);
uintmax_t		get_unumber(va_list arg, int len, int large);
intmax_t		get_number(va_list arg, int len, int large);
char			*ft_itoa_base(intmax_t n);
char			*ft_itoa_ubase(uintmax_t value, int base, int key);
void			parse_lag(t_printf *p);
void			print_str(char *str, t_printf *p);
void			print_char(char c, t_printf *p);
void			store_buffer2(t_printf *p, char *spec);
void			store_buffer(t_printf *p, char *spec);
int				parse_length(char *str, int max);
char			*ft_alloc(char *buf, char *str);
char			*ctos(char c);
int				ft_printf(const char *format, ...);
void			parse_width(char *str, t_printf *p, int max);
void			parse_all(char *str, t_printf *p, int max);
char			*og_str(char c, int len);
char			*str_cut(char *s1, int len);
void			precision_completion(char *str, t_printf *p, int m);
void			flags_completion(char *str, t_printf *p, int m);
void			plus_completion(char *str, t_printf *p, int m);
char			*str_append(char *s1, char *s2, int f1, int f2);
char			*str_appendneg(char *s1, char *s2);

#endif
