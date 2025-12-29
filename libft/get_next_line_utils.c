/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:15:45 by ltrillar          #+#    #+#             */
/*   Updated: 2025/08/15 03:39:14 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dup;

	if (!s1 || !s2)
		return (NULL);
	dup = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dup[i + j] = s2[j];
		j++;
	}
	dup[i + j] = '\0';
	return (dup);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (n > len)
		n = len;
	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
	{
		return (NULL);
	}
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
