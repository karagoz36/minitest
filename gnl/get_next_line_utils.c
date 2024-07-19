/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:13 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/06/03 14:05:37 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;
	int	len;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
	{
		len = ft_strlen(str);
		return ((char *)&str[len]);
	}
	while (str[i])
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_calloc(size_t n, size_t size)
{
	size_t		i;
	char		*allocated;

	if (n * size != 0 && n * size < size)
		return (NULL);
	allocated = (char *)malloc (n * size);
	if (!allocated)
		return (NULL);
	i = 0;
	while (i < n)
		allocated[i++] = '\0';
	return (allocated);
}

char	*ft_gnljoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 || !s2)
		return (NULL);
	dest = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), 1);
	if (!dest)
		return (free(s1), NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			dest[i] = s1[i];
	while (s2[j])
		dest[i++] = s2[j++];
	free(s1);
	return (dest);
}
