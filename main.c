/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:43:34 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/18 13:29:55 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(void)
{
	int fd;
	char *line;
	int r;

	r = 0;
	if (-1 == (fd = open("test.txt", O_RDONLY)))
		return (0);
	while ((r = get_next_line(fd, &line) == 1))
	{
		printf("(main) (r:%i) Line is: %s\n--\n",r,line);
		free(line);
	}
	printf("(main) (r:%i) Line is: %s\n--\n", r, line);
	free(line);
	close (fd);
}
