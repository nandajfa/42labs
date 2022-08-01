/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:11:32 by jefernan          #+#    #+#             */
/*   Updated: 2021/11/14 18:06:20 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char **buffer, char **save);
char	*verify_line(char **save);
char	*make_line(char **save, int i);
void	free_str(char	**str);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	line = read_file(fd, &buffer, &save);
	free(buffer);
	return (line);
}

char	*read_file(int fd, char **buffer, char **save)
{
	int		ret;
	char	*temp;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, *buffer, BUFFER_SIZE);
		if (ret == -1 || ret == 0)
			return (verify_line(save));
		(*buffer)[ret] = '\0';
		temp = *save;
		*save = ft_strjoin(temp, *buffer);
		free(temp);
		if (ft_strchr(*save, '\n'))
			break ;
	}
	line = verify_line(save);
	return (line);
}

char	*verify_line(char **save)
{
	int		i;
	char	*line;

	i = 0;
	if (*save[0] == '\0')
	{
		free (*save);
		*save = NULL;
		return (NULL);
	}
	line = make_line(save, i);
	return (line);
}

char	*make_line(char **save, int i)
{
	char	*temp;
	char	*line;

	while ((*save)[i] != '\0' && (*save)[i] != '\n')
		i++;
	if (ft_strchr(*save, '\n'))
		line = ft_substr(*save, 0, i + 1);
	else
		line = ft_substr(*save, 0, i);
	if (ft_strchr(*save, '\n'))
	{
		i = ft_strlen(ft_strchr(*save, '\n'));
		if (i > 1)
		{
			temp = *save;
			*save = ft_substr (ft_strchr(temp, '\n'), 1, i - 1);
			free (temp);
		}
		else
			free_str(save);
	}
	else
		free_str(save);
	return (line);
}

void	free_str(char	**str)
{
	free(*str);
	*str = NULL;
}
