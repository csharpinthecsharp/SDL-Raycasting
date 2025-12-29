/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:15:18 by ltrillar          #+#    #+#             */
/*   Updated: 2025/08/18 21:18:29 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*extract_line(char **reste, char *newline)
{
	size_t	line_len;
	char	*line;
	char	*temp;

	line_len = newline - *reste + 1;
	line = ft_strndup(*reste, line_len);
	temp = *reste;
	*reste = ft_strdup(newline + 1);
	free(temp);
	return (line);
}

char	*update_reste(char **reste, char *buffer)
{
	char	*temp;

	if (!*reste)
		*reste = ft_strdup(buffer);
	else
	{
		temp = *reste;
		*reste = ft_strjoin(*reste, buffer);
		free(temp);
	}
	return (*reste);
}

char	*handle_error(char **reste)
{
	free(*reste);
	*reste = NULL;
	return (NULL);
}

char	*final_return(char **reste, ssize_t bytes_read)
{
	char	*line;

	if (bytes_read == -1 || !(*reste) || !**reste)
		return (handle_error(reste));
	line = ft_strdup(*reste);
	free(*reste);
	*reste = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*newline;
	static char	*reste;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (reste)
	{
		newline = ft_strchr(reste, '\n');
		if (newline)
			return (extract_line(&reste, newline));
	}
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		reste = update_reste(&reste, buffer);
		newline = ft_strchr(reste, '\n');
		if (newline)
			return (extract_line(&reste, newline));
	}
	return (final_return(&reste, bytes_read));
}
