/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:00:01 by jefernan          #+#    #+#             */
/*   Updated: 2022/08/02 21:42:23 by jefernan         ###   ########.fr       */
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
	int fd;
	char *temp;
	char	**line;

	fd = open("src/monitoring.db", O_RDONLY);

	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		line = ft_split(temp, '\t');
		if (ft_strncmp("HTTP", line[1], ft_strlen("HTTP")) == 0)
			protocol_http(line, http);
		if (ft_strncmp("PING", line[1], ft_strlen("PING")) == 0)
			printf("ping\n");
		if (ft_strncmp("DNS", line[1], ft_strlen("DNS")) == 0)
			printf("dns\n");

		free(temp);
	}
	close(fd);
}

int validation(char *line)
{
	int i;
	int len;
	char	*str;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t')
			printf("ok");
		i++;
	}

	return (0);
}

char	**str(char *input)
{
	printf("2\n");
	return (ft_split(input, ' '));
}
