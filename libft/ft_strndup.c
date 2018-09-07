/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 18:07:19 by kradoste          #+#    #+#             */
/*   Updated: 2018/08/27 18:08:30 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*key;
	size_t	i;

	i = ft_strlen(s1);
	if (!(key = (char *)malloc(sizeof(char) * i + 1)))
		return ((void*)0);
	ft_strncpy(key, s1, n);
	return (key);
}
