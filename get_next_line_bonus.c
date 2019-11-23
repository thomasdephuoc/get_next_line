/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:57 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/23 13:00:13 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
** Dynamically allocates count elements of size, null-terminates the output
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
		return (NULL);
	if (!(ptr = malloc(count * size)))
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*(ptr + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

int		check_get_line(char **line, char **mem)
{
	int		i;
	char	*tmp;

	i = 0;
	while (mem[0][i] != '\0' && mem[0][i] != '\n')
		i++;
	if (mem[0][i] == '\n')
	{
		*line = ft_strsub(mem[0], '\n');
		tmp = ft_strjoin("", mem[0] + i + 1);
		free(mem[0]);
		mem[0] = tmp;
	}
	else if (mem[0][i] == '\0')
	{
		*line = ft_strsub(mem[0], '\n');
	}
	return (1);
}

int		while_gnl(int fd, char **mem, int buf_size, int *r)
{
	char	bu[buf_size + 1];
	char	*tmp;

	while (ft_strchr(mem[0], '\n') == NULL
	&& (ft_memset(bu, 0, buf_size + 1) == bu)
	&& ((*r = read(fd, bu, buf_size)) != 0))
	{
		if (*r < 0)
			return (-1);
		if (!(tmp = ft_strjoin(mem[0], bu)))
			return (-1);
		free(mem[0]);
		mem[0] = tmp;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		*mem;
	int				r;
	int				buf_size;

	r = 1;
	buf_size = BUFFER_SIZE;
	if (fd < 0 || line == NULL || buf_size < 0)
		return (-1);
	if (mem == NULL)
		if (!(mem = ft_calloc(buf_size + 1, sizeof(char))))
			return (-1);
	if (while_gnl(fd, &mem, buf_size, &r) == -1)
		return (-1);
	if (r == 0 && check_get_line(line, &mem) == 1)
	{
		mem[0] = '\0';
		return (0);
	}
	else if (r > 0 && check_get_line(line, &mem) == 1)
		return (1);
	return (-1);
}
