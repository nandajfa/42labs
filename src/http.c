/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:23:37 by jefernan          #+#    #+#             */
/*   Updated: 2022/08/03 15:28:48 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"
#include "../get_next_line/get_next_line.h"

int protocol_http(char **line, t_http *http)
{
	CURL *curl;
	CURLcode response;
	FILE *fp;

	init_shttp(line, http);
	curl_global_init(CURL_GLOBAL_ALL);

	fp = fopen("monitoring.log", "at");
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, http->route);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(curl, CURLOPT_STDERR, fp);

		response = curl_easy_perform(curl);
		if (response != CURLE_OK)
			fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));

		curl_easy_cleanup(curl);
	}
	fclose(fp);
	curl_global_cleanup();
	print_log_http(http);
	return (0);
}

void init_shttp(char **line, t_http *http)
{
	http->name = line[0];
	http->protocol = line[1];
	http->route = line[2];
}

void	print_log_http(t_http *http)
{
	int fd;
	char	*temp;
	char	**str_line;

	fd = open("monitoring.log", O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Fail to read 'monitoring.log'\n");
		exit(EXIT_FAILURE);
	}
	printf("=================================monitoring http=================================\n");
	printf("Name: %s\n", http->name);
	printf("Protocol: %s\n", http->protocol);
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		str_line = ft_split(temp, '\n');
		if (ft_strncmp("< Location:", *str_line, ft_strlen("< Location:")) == 0)
			printf("Adress: %s\n", str_line[0]);
		if (ft_strncmp("> GET", str_line[0], ft_strlen("> GET")) == 0)
			printf("Method: %s\n", str_line[0]);
		if (ft_strncmp("< HTTP", str_line[0], ft_strlen("< HTTP")) == 0)
			printf("Status: %s\n", str_line[0]);
		free(temp);
		free_line(str_line);
	}
	close(fd);
}
