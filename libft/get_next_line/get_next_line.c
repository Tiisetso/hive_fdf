/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:44:43 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 11:41:55 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_read_line_check(char *read_line)
{
	if (!read_line)
	{
		read_line = (char *)malloc(1);
		if (!read_line)
			return (NULL);
		read_line[0] = '\0';
	}
	return (read_line);
}

char	*ft_read_line(char *read_line, int fd)
{
	int		count;
	char	*temp;
	char	*buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	read_line = ft_read_line_check(read_line);
	while (!ft_n_exist(read_line, '\n'))
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count <= 0)
			break ;
		buf[count] = '\0';
		temp = ft_strjoin(read_line, buf);
		free(read_line);
		if (!temp)
		{
			free(buf);
			return (NULL);
		}
		read_line = temp;
	}
	free(buf);
	return (read_line);
}

int	ft_get_n_index(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (const char)c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_n_exist(const char *s, int c)
{
	while (*s)
	{
		if (*s == (const char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0' && *s == (const char)c)
		return ((char *)s);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*r;
	char		*line;
	char		*t;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	r = ft_read_line(r, fd);
	if (!r || *r == '\0')
	{
		free(r);
		r = NULL;
		return (NULL);
	}
	i = ft_get_n_index(r, '\n');
	line = ft_substr(r, 0, (size_t)i + 1);
	if (!line)
		return (NULL);
	if ((size_t)(i + 1) < ft_strlen(r))
		t = ft_substr(r, (unsigned int)(i + 1), ft_strlen(r) - (size_t)(i + 1));
	else
		t = NULL;
	free(r);
	r = t;
	return (line);
}
