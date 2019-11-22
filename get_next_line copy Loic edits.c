/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy Loic edits.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:57 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/22 15:14:49 by tde-phuo         ###   ########.fr       */
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
		//*line = ft_substr(mem[0], 0, i);
		tmp = ft_strjoin("", mem[0] + i + 1);
		free(mem[0]);
		mem[0] = tmp;
	}
	else if (mem[0][i] == '\0')
	{
		*line = ft_strsub(mem[0], '\n');
		//*line = ft_substr(mem[0], 0, i);
	}
	return (1);
}

int		get_next_line(int fd, char **line) // delete the memset
{
	char			bu[BUFFER_SIZE + 1];
	char			*tmp;
	static char		*mem;
	int				r;
	int				size;

	if (fd < 0 || line == NULL || (size = BUFFER_SIZE < 0))
		return (-1);
	if (mem == NULL)
		if (!(mem = ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
			return (-1);
	while (ft_strchr(mem, '\n') == NULL && ((r = read(fd, bu, BUFFER_SIZE)) != 0))
	{
		bu[r] = '\0';
		if (!(tmp = ft_strjoin(mem, bu)))
			return (-1);
		free(mem);
		mem = tmp;
	}
	if (r == 0 && check_get_line(line, &mem) == 1)
		return (0);
	else if (r > 0 && check_get_line(line, &mem) == 1)
		return (1);
	return (-1);
}
