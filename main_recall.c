/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_recall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:43:34 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/25 11:45:45 by tde-phuo         ###   ########.fr       */
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
	printf("fd is: %i\n", fd);
	while ((r = get_next_line(fd, &line) == 1))
	{
		printf("(main) (r:%i) Line is: %s\n--\n", r, line);
		free(line);
	}
	printf("(main) (r:%i) Line is: %s\n--\n", r, line);
	free(line);
	close(fd);
	if (-1 == (fd = open("test2.txt", O_RDONLY)))
	{
		printf("problem, fd is: %i", fd);
		return (0);
	}
	printf("fd is: %i\n", fd);
	while ((r = get_next_line(fd, &line) == 1))
	{
		printf("(main) (r:%i) Line is: %s\n--\n", r, line);
		free(line);
	}
	printf("(main) (r:%i) Line is: %s\n--\n", r, line);
	free(line);
	close(fd);
	system("leaks a.out");
	//(r = get_next_line(fd, &line));
	//printf("Recalling gnl after fd closed: (main) (r:%i) Line is: %s\n--\n", r, line);
	//free(line);
}

/*

// jraleman main

int main(void)
{
	int fd;
	int ret;
	int line;
	char *buff;

	line = 0;
	fd = open("test.txt", O_RDONLY);
	while ((ret = get_next_line(fd, &buff)) > 0)
	{
		printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
		free(buff);
	}
	printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
	free(buff);
	if (ret == -1)
		printf("-----------\nError\n");
	else if (ret == 0)
		printf("-----------\nEnd of file\n");
	close(fd);
	//while ((ret = get_next_line(0, &buff)) > 0)
		//printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
	//if (ret == -1)
		//printf("-----------\nError\n");
	//else if (ret == 0)
		//printf("-----------\nEnd of stdin\n");
	//close(fd);
	return (0);
}


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
