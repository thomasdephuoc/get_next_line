/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:43:34 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/22 15:08:38 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

int main(void)
{
	int fd;
	char *line = NULL;
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
	system("leaks a.out");
	close (fd);
}

/*
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int fd;
	char **line;
	int ret;
	fd = open("test", O_RDONLY);
	fd = 0;
	if (!(line = malloc(sizeof(char *))))
		return (0);
	ret = 1;
	while ((ret = get_next_line(fd, line)) == 1)
	{
		printf("%d|%s|\n", ret, *line);
		free(*line);
	}
	printf("%d|%s|\n", ret, *line);
	free(*line);
	free(line);
	close(fd);
	system("leaks a.out");
}
*/
