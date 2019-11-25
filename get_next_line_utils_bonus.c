/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-phuo <tde-phuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:38:55 by tde-phuo          #+#    #+#             */
/*   Updated: 2019/11/25 12:54:07 by tde-phuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n - 1)
	{
		*(ptr + i) = 0;
		i++;
	}
	*(ptr + n - 1) = '\0';
}

/*
** To copy everything up to first instance of c
*/

char	*ft_strsub(char *str, char c)
{
	int		i;
	int		j;
	char	*return_str;

	if (str == NULL || c == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return_str = ft_calloc(i + 1, sizeof(char));
	while (j < i)
	{
		return_str[j] = str[j];
		j++;
	}
	return_str[j] = '\0';
	return (return_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	if (!(ptr = malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (NULL);
	while (i < len_s1)
	{
		ptr[i] = *s1++;
		i++;
	}
	while (i < len_s1 + len_s2)
	{
		ptr[i] = *s2++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
** Calculates length of string
*/

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
** Looks for element c in string s
** Returns portion of the string after first instance of c
** Returns NULL if c not found
*/

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (s == NULL || c == 0)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			break ;
		i++;
	}
	if (s[i] != (char)c)
		return (NULL);
	return ((char *)s + i);
}
