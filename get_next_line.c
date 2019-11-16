/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:57 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/16 12:14:11 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Using a buffer we'll trim to remove anything after \n and put that into line.
*/
int check_get_line(int fd, char *buffer, char **line, char **memory)
{
	int i;

	i = 0;
	printf("(1) Buffer is %s\n, memory is: %s\n", buffer, *memory); // why is memory empty?
	buffer = ft_strjoin(*memory, buffer); //doublon ?
	printf("After joining both: Buffer is: %s\n", buffer);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	printf("buffer[i] when exiting loop is: %i, value of i is: %i\n", (int)buffer[i], i);
	if (buffer[i] == '\n')
	{
		*line = ft_strsub(buffer, '\n');
		*memory = ft_strjoin("", buffer + i + 1); // this works: we save in memory characters that were read after \n. We add + 1 to skip \n. Won't this destroy memory later?
	}
	printf("After strjoin, Memory is: %s\n", *memory);
	//else : si le buffer n'a pas suffi à atteindre la fin de la ligne, refaire un tour (exécuter get_next_line)
	return (fd); // returning fd to silence warning
}


int get_next_line(int fd, char **line)
{
	char			*buffer;
	static char		**memory;
	int				r;

	*line = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // malloc de la taille de la ligne
	if (memory == NULL) // only malloc memory if memory is empty!
	{
		memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // au maximum, il y aura buffer_size + 1 dans memory car on ne lira jamais plus que buffer_size caractères
		*memory = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	printf("On gnl call memory is: %s\n", *memory);
	// mettre le read dans memory
	while ((r = read(fd, buffer, BUFFER_SIZE) != 0) && ft_strchr(ft_strjoin(*memory, buffer), '\n') == NULL) // Case if buffer is too short for line BUFFER = 20, doesn't get into the loop because buffer contains '\n' on first execution, so memory is still empty after the while
	{
		*memory = ft_strjoin(*memory, buffer);
	}
	if (r == 0)
		return (0);
	else
		check_get_line(fd, buffer, line, memory);
	return (1);
}
