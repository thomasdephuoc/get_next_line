/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:57 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/20 14:33:25 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
void	free_memory(int i, char *buffer, char **memory)
{
	if (i == 1)
	{
		free(buffer);
	}
}
*/

/*
** Using a buffer we'll trim to remove anything after \n and put that into line.
*/
int check_get_line(int fd, char *buffer, char **line, char **memory)
{
	int i;

	i = 0;
	//printf("(1) Buffer is: %s\nmemory is: %s\n", buffer, *memory);
	buffer = ft_strjoin(*memory, buffer);
	//printf("(1) After joining both: Buffer is: %s\n", buffer);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	//printf("(1) buffer[i] when exiting loop is: %i, value of i is: %i\n", (int)buffer[i], i);
	if (buffer[i] == '\n')
	{
		*line = ft_strsub(buffer, '\n');
		*memory = ft_strjoin("", buffer + i + 1);
	}
	if (buffer[i] == '\0') // a else could do
	{
		*line = ft_strsub(buffer, '\n');
	}
	//printf("(1) After strjoin, Memory is: %s\n", *memory);
	return (fd); // returning fd to silence warning
}


int get_next_line(int fd, char **line)
{
	char			*buffer;
	//char			buffer[BUFFER_SIZE + 1];
	char			*tmp;
	static char		**memory; // instanciation ici autorisée dans le cas des static, nécessaire ? => non car calloc initialise
	int				r;

	if (fd < 0 || line == NULL) // protege la fonction
		return (-1);
	r = 500; // if r is not initialised, it will be 0 so the if(r == 0) below will execute. Will it lead to pb that it's arbitrary?
	*line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	//buffer[BUFFER_SIZE] = '\0';
	if (memory == NULL)
	{
		memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char*)); // au maximum, il y aura buffer_size + 1 dans memory car on ne lira jamais plus que buffer_size caractères
		*memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // pb is HERE
		//printf("success hello\n");
	}
	//printf("(2) On gnl call memory is: %s\n", *memory);
	//printf("(2) memory + buffer is: %s\n", ft_strjoin(*memory, buffer));
	while (ft_strchr(ft_strjoin(*memory, buffer), '\n') == NULL) // Should the loop also look for a '\0'? => memory leak here from strjoin
	{
		//printf("(2) Loop executes\n");
		tmp = ft_strjoin(*memory, buffer); // 53 -> 48 leaks
		free(*memory);
		*memory = tmp;
		if (((r = read(fd, buffer, BUFFER_SIZE)) == 0))
		{
			buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); //reinitialise buffer to 0 to avoid problems for last instance
			//buffer[0] = '\0';
			break;
		}
		//printf("(2) In loop, r is: %i\n", r);
	}
	//printf("(2) After loop, r is: %i\n", r);
	//printf("(2) After while, Buffer is: %s\n", buffer);
	check_get_line(fd, buffer, line, memory);
	free(buffer); // 64 -> 53 leaks
	if (r == 0)
	{

		//printf("(2) gnl stops\n");
		return (0);
	}
	else if (r < 0)
		return (-1);
	else
		return (1);
}
