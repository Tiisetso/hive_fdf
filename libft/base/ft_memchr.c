/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:15:33 by timurray          #+#    #+#             */
/*   Updated: 2025/05/07 13:58:57 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*stemp;

	stemp = (unsigned char *)s;
	while (n--)
	{
		if (*stemp == (unsigned char)c)
			return ((void *)stemp);
		stemp++;
	}
	return (NULL);
}
