/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:57 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/15 17:28:38 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Using a buffer we'll trim to remove anything after \n and put that into line.
*/
int check_get_line(int fd, char *buffer, char **line, char *memory)
{
	int i;

	i = 0;
	printf("Buffer is %s\n", buffer);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	printf("buffer[i] when exiting loop is: %i, value of i is: %i\n", (int)buffer[i], i);
	if (buffer[i] == '\n')
	{
		*line = ft_strsub(buffer, '\n');
		memory = ft_strjoin("", buffer + i + 1); // this works: we save in memory characters that were read after \n. We add + 1 to skip \n. Won't this destroy memory later?
	}
	printf("After strjoin, Memory is: %s\n", memory);
	//else : si le buffer n'a pas suffi à atteindre la fin de la ligne, refaire un tour (exécuter get_next_line)
	return (fd); // returning fd to silence warning
}


int get_next_line(int fd, char **line)
{
	char			*buffer;
	static char		*memory = 0;
	int				r;

	*line = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // malloc de la taille de la ligne
	memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // au maximum, il y aura buffer_size + 1 dans memory car on ne lira jamais plus que buffer_size caractères
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while ((r = read(fd, buffer, BUFFER_SIZE) != 0) && ft_strchr(buffer, '\n') == NULL) // BUFFER = 20, doesn't get into the loop because buffer contains '\n' on first execution, so memory is still empty after the while
	{
		if (memory[0] == 0)
		{
			memory = buffer;
			printf("--\nThis is first execution\n");
		}
		else
		{
			memory = ft_strjoin(memory, buffer);
		}
	}
	if (r == 0)
		return (0); //besoin de finir buffer par un \0? => calloc le fait
	//if (memory[0] == 0) //testing for memory[0] == 0 because calloc initialised memory to 0
	//	memory = buffer;
	else
		check_get_line(fd, buffer, line, memory);
	return (1);
}
