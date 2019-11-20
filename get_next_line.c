/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:57 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/20 19:12:31 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Dynamically allocates count elements of size size, null-terminating the output
*/
void *ft_calloc(size_t count, size_t size)
{
	void *ptr;
	size_t i;

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
	size_t i;
	unsigned char *ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*(ptr + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

int check_get_line(int fd, char **line, char **memory)
{
	int		i;
	char	*tmp;

	i = 0;
	while (memory[0][i] != '\0' && memory[0][i] != '\n')
		i++;
	if (memory[0][i] == '\n')
	{
		*line = ft_strsub(memory[0], '\n');
		tmp = ft_strjoin("", memory[0] + i + 1);
		free(*memory);
		*memory = tmp;
	}
	else if (memory[0][i] == '\0')
	{
		*line = ft_strsub(memory[0], '\n');
	}
	return (fd);
}


int get_next_line(int fd, char **line)
{
	char			bu[BUFFER_SIZE + 1];
	char			*tmp;
	static char		**memory;
	int				r;

	if (fd < 0 || line == NULL || (ft_memset(bu, 0, BUFFER_SIZE + 1)!= bu))
		return (-1);
	r = 500;
	if (memory == NULL)
	{
		memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char*));
		*memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	}
	while (ft_strchr(*memory, '\n') == NULL)
	{
		if (((r = read(fd, bu, BUFFER_SIZE)) == 0))
			break;
		tmp = ft_strjoin(*memory, bu);
		free(*memory);
		*memory = tmp;
	}
	check_get_line(fd, line, memory);
	if (r == 0)
		return (0);
	else if (r < 0)
		return (-1);
	else
		return (1);
}
