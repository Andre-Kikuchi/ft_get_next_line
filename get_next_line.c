/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahideo-k <ahideo-k@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 15:36:24 by ahideo-k          #+#    #+#             */
/*   Updated: 2026/07/20 18:08:46 by ahideo-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_file(int fd, char *stash, char *buffer);
static char	*ft_extract_line(char *stash);
static char	*ft_update_stash(char *stash);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	stash = ft_read_file(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	stash = ft_update_stash(stash);
	return (line);
}

static char	*ft_read_file(int fd, char *stash, char *buffer)
{
	ssize_t	num_bytes;

	num_bytes = 1;
	while (num_bytes != 0 && !ft_strchr(stash, '\n'))
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
		{
			free(stash);
			return (NULL);
		}
		buffer[num_bytes] = '\0';
		if (!stash)
		{
			stash = ft_calloc(1, sizeof(char));
			if (!stash)
				return (NULL);
		}
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*ft_extract_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		line = (char *)ft_calloc((i + 2), sizeof(char));
	else
		line = (char *)ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	if (stash[i] == '\n')
		line[j] = '\n';
	return (line);
}

static char	*ft_update_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	new_stash = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	if (!new_stash)
		return (free(stash), NULL);
	i++;
	j = 0;
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	free(stash);
	return (new_stash);
}
