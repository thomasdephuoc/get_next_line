/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:53 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/20 16:55:01 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	free_memory(int i, char *buffer, char **memory);
int		get_next_line(int fd, char **line);
int		check_get_line(int fd, char **line, char **memory);
void	*ft_memset(void *b, int c, size_t len);
void *ft_calloc(size_t count, size_t size);

void	ft_bzero(void *s, size_t n);
char	*ft_strsub(char *str, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);

#endif
