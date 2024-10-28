/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:57:13 by dbatista          #+#    #+#             */
/*   Updated: 2024/10/27 00:33:15 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	*ft_free_mem(char **line_f, char **rest_f, char **buf_f)
{
	if (line_f)
	{
		if (*line_f)
			free(*line_f);
		*line_f = NULL;
	}
	if (rest_f)
	{
		if (*rest_f)
			free(*rest_f);
		*rest_f = NULL;
	}
	if (buf_f)
	{
		if (*buf_f)
			free(*buf_f);
		*buf_f = NULL;
	}
	return (NULL);
}

static	char	*ft_after_break_line(char *line)
{
	char	*after_line;
	size_t	size;
	int		pos;

	pos = ft_strchr(line);
	if (pos < 0)
		return (NULL);
	size = ft_strlen(line);
	after_line = malloc((size - pos) * sizeof(char));
	if (!after_line)
		return (NULL);
	after_line[size - pos - 1] = '\0';
	ft_strlcpy(after_line, (line + pos + 1), (size - pos));
	return (after_line);
}

static	char	*ft_before_break_line(char *line)
{
	int		pos;
	char	*before_line;

	pos = ft_strchr(line);
	if (!line)
		return (NULL);
	if (pos < 0)
		return (line);
	before_line = malloc((pos + 2) * sizeof(char));
	if (before_line == NULL)
		return (NULL);
	before_line[pos + 1] = '\0';
	ft_strlcpy(before_line, line, pos + 2);
	free(line);
	return (before_line);
}

static	char	*ft_get_line(char **r_line, char **buf, char **line, int buf_r)
{
	if (buf_r == 0)
	{
		ft_free_mem(NULL, r_line, buf);
		if (*line && **line)
			return (*line);
		return (ft_free_mem(line, NULL, NULL));
	}
	ft_free_mem(NULL, r_line, buf);
	*r_line = ft_after_break_line(*line);
	*line = ft_before_break_line(*line);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*rest_line;
	char		*line;
	char		*buf;
	int			buf_read;

	if (!rest_line)
		rest_line = ft_strdup("");
	line = ft_strdup(rest_line);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf_read = BUFFER_SIZE;
	while (buf_read == BUFFER_SIZE && ft_strchr(line) < 0)
	{
		buf_read = read(fd, buf, BUFFER_SIZE);
		if (buf_read < 0)
			return (ft_free_mem(&line, &rest_line, &buf));
		buf[buf_read] = '\0';
		line = ft_strjoin(line, buf);
	}
	return (ft_get_line(&rest_line, &buf, &line, buf_read));
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd = open("gnl.txt", O_RDONLY);
	char	*line;

	if(fd == -1)
	{
		printf("ERROR!");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/