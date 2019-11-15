/*

goal is to read fd, put something in line. Read a buffer of 1 to start with
Trying with a pointer to c (the whole function uses a pointer to a string, **line, so we should use a pointer to a char: *c)

PROGRAM

To read one character

int get_next_line(int fd, char *c)
{
	read(fd, c, 1);
	return (1);
}

Reading one line

int get_next_line(int fd, char **line)
{
	*line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read(fd, *line, BUFFER_SIZE);
	return (1);
}

MAIN


To read one character

int	main (void)
{
	int	fd;
	char *c;

	c = ft_calloc(1, sizeof(char));
	fd = open("test.txt", O_RDONLY);
	printf("fd is: %d\n", fd);
	get_next_line(fd, c);
	printf("%s\n", c);
	// display content of line
}

To read one line

int main(void)
{
	int fd;
	char **line;

	line = ft_calloc(1, sizeof(char*));
	*line = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // important to allocate an additional space for null-terminating character
	fd = open("test.txt", O_RDONLY);
	printf("fd is: %d\n", fd);
	get_next_line(fd, line);
	printf("%s\n", *line);
	free(*line);
	// display content of line
}

*/
