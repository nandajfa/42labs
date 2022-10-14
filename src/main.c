/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:00:01 by jefernan          #+#    #+#             */
/*   Updated: 2022/10/13 21:27:23 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"
#include "../get_next_line/get_next_line.h"

int main(void)
{
	t_http http;
	t_ping ping;
	t_dns dns;

	open_file(&http, &ping, &dns);
	return (0);
}

int open_file(t_http *http, t_ping *ping, t_dns *dns)
{
	t_data data;
	char *temp;
	char	**line;

	data.db = open(FILEDB, O_RDONLY);
	if (data.db < 0)
	{
		fprintf(stderr, "Fail to read 'monitoring.db'\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		temp = get_next_line(data.db);
		if (temp == NULL)
			break ;
		line = ft_split(temp, '\t');
		if (ft_strncmp("HTTP", line[1], ft_strlen("HTTP")) == 0)
			protocol_http(line, http);
		if (ft_strncmp("PING", line[1], ft_strlen("PING")) == 0)
			protocol_ping(line, ping);
		if (ft_strncmp("DNS", line[1], ft_strlen("DNS")) == 0)
			printf("dns\n");
		free(temp);
		free_line(line);
	}
	close(data.db);
	return (0);
}

void	free_line(char **line)
{
	int	i;

	if (line == NULL)
		return ;
	i = 0;
	while (line[i] != NULL)
		free(line[i++]);
	free(line);
}