/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:57 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/21 12:08:06 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Dynamically allocates count elements of size size, null-terminates the output
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
		free(*mem);
		*mem = tmp;
	}
	else if (mem[0][i] == '\0')
	{
		*line = ft_strsub(mem[0], '\n');
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char			bu[BUFFER_SIZE + 1];
	char			*tmp;
	static char		**mem;
	int				r;

	if (fd < 0 || line == NULL || (ft_memset(bu, 0, BUFFER_SIZE + 1) != bu))
		return (-1);
	r = 500;
	if (mem == NULL)// faire malloc ici permet de le proteger
	{
		mem = ft_calloc(1, sizeof(char*));
		*mem = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // a proteger
	}
	while (ft_strchr(*mem, '\n') == NULL && ((r = read(fd, bu, BUFFER_SIZE)) != 0))
	{
		tmp = ft_strjoin(*mem, bu);
		free(*mem);
		*mem = tmp;
	}
	if (r == 0 && check_get_line(line, mem) == 1)
		return (0);
	else if (r > 0 && check_get_line(line, mem) == 1)
		return (1);
	return (-1);
}
