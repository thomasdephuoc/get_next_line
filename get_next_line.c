/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:57 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/20 18:30:42 by tde-phuo         ###   ########.fr       */
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
	//printf("(1) Buffer is: %s\nmemory is: %s\n", buffer, *memory);
	//buffer = ft_strjoin(*memory, buffer);
	//printf("(1) Memory is: %s\n", memory[0]);
	while (memory[0][i] != '\0' && memory[0][i] != '\n')
		i++;
	//printf("(1) memory[0][i] when exiting loop is: %i, value of i is: %i\n", (int)memory[0][i], i);
	if (memory[0][i] == '\n')
	{
		*line = ft_strsub(memory[0], '\n');
		//*memory = ft_strjoin("", memory[0] + i + 1);
		tmp = ft_strjoin("", memory[0] + i + 1);
		free(*memory);
		*memory = tmp;
	}
	else if (memory[0][i] == '\0') // a else could do
	{
		*line = ft_strsub(memory[0], '\n');
	}
	//printf("(1) After strjoin, Memory is: %s\n", memory[0]);
	return (fd); // returning fd to silence warning
}


int get_next_line(int fd, char **line)
{
	char			bu[BUFFER_SIZE + 1];
	char			*tmp;
	static char		**memory; // instanciation ici autorisée dans le cas des static, nécessaire ? => non car calloc initialise
	int				r;

	if (fd < 0 || line == NULL || (ft_memset(bu, (char)0, BUFFER_SIZE + 1)!= bu))
		return (-1);
	r = 500; // if r is not initialised, it will be 0 so the if(r == 0) below will execute. Will it lead to pb that it's arbitrary?
	//*line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (memory == NULL)
	{
		memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char*));
		*memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	}
	//printf("(2) On gnl call memory is: %s\n", *memory);
	//printf("(2) memory + buffer is: %s\n", ft_strjoin(*memory, buffer));
	while (ft_strchr(*memory, '\n') == NULL) // Should the loop also look for a '\0'?
	{
		//printf("(2) Loop executes\n");
		if (((r = read(fd, bu, BUFFER_SIZE)) == 0))
			break;
		tmp = ft_strjoin(*memory, bu);
		free(*memory);
		*memory = tmp;
		//printf("(2) In loop, r is: %i\n", r);
	}
	//printf("(2) After loop, r is: %i\n", r);
	//printf("(2) After while, Buffer is: %s, Memory is:%s\n", buffer, *memory);
	check_get_line(fd, line, memory); // now both things are in memory
	if (r == 0)
		return (0);
	else if (r < 0)
		return (-1);
	else
		return (1);
}
