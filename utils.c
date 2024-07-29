/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:26:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/29 14:53:47 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
//
static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	write(fd, &s[i], ft_strlen(s));
}
//
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

//ft_strcmp
int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
//

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char) c)
		return ((char *) &str[i]);
	return (0);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;

	dest = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	i;
	size_t	len;

	if (!src)
		return (NULL);
	if (ft_strlen(src) <= n)
		len = ft_strlen(src);
	else
		len = n;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

//split

// static size_t	ft_cw(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	cnt;

// 	i = 0;
// 	cnt = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 			cnt++;
// 		i++;
// 	}
// 	return (cnt);
// }

// static size_t	ft_fill(char **dest, char const *s, char c, size_t i)
// {
// 	size_t	j;

// 	j = i;
// 	while (s[j] && s[j] != c)
// 		j++;
// 	*dest = (char *)malloc((j - i + 1) * sizeof(char));
// 	if (!*dest)
// 		return (0);
// 	ft_strlcpy(*dest, s + i, j - i + 1);
// 	return (j);
// }

// static void	ft_free(char **dest, size_t w)
// {
// 	while (w > 0)
// 		free(dest[--w]);
// 	free(dest);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**dest;
// 	size_t	w;
// 	size_t	i;

// 	dest = (char **)malloc((ft_cw(s, c) + 1) * sizeof(char *));
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	w = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			i = ft_fill(&dest[w++], s, c, i);
// 			if (!i)
// 			{
// 				ft_free(dest, w);
// 				return (NULL);
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	dest[w] = NULL;
// 	return (dest);
// }

