/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:23:37 by jefernan          #+#    #+#             */
/*   Updated: 2022/10/13 19:37:18 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"
#include "../get_next_line/get_next_line.h"

int protocol_http(char **line, t_http *http)
{
	CURL		*curl;
	CURLcode	response;
	t_data		data;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	data.monitoring = fopen("monitoring.log", "at");
	init_shttp(line, http);
	if (curl)
	{

		curl_easy_setopt(curl, CURLOPT_URL, http->address);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, data.monitoring);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_STDERR, data.monitoring);
		response = curl_easy_perform(curl);
		if (response != CURLE_OK)
			fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http->response_code);
		curl_easy_cleanup(curl);
	}
	print_http(http, data.monitoring);
	fclose(data.monitoring);
	curl_global_cleanup();
	//sleep(http->interval);
	return (0);
}

void init_shttp(char **line, t_http *http)
{
	http->name = line[0];
	http->protocol = line[1];
	http->address = line[2];
	http->method = line[3];
	http->http_code = ft_atoi(line[4]);
	http->interval = ft_atoi(line[5]);
}

void	print_http(t_http *http, FILE *fp)
{
	printf("%s==================================monitoring http=================================\n%s", UNDER_BLUE, RESET);
	printf("Name: %s\n", http->name);
	printf("Protocol: %s\n", http->protocol);
	printf("Address: %s\n", http->address);
	printf("Method: %s\n", http->method);
	printf("Expected code: %d\n", http->http_code);
	if (http->response_code != 200)
		printf("%s | Status: KO | %s\n", RED, RESET);
	else
		printf("%s  | Status: OK | %s\n", GREEN, RESET);
	printf("%s==================================================================================\n\n%s", UNDER_BLUE, RESET);

	fprintf(fp, "==================================monitoring http=================================\n");
	fprintf(fp, "Name: %s\n", http->name);
	fprintf(fp, "Protocol: %s\n", http->protocol);
	fprintf(fp, "Address: %s\n", http->address);
	fprintf(fp, "Method: %s\n", http->method);
	fprintf(fp, "Expected code: %d\n", http->http_code);
	if (http->response_code != 200)
		fprintf(fp, " | Status: KO | \n");
	else
		fprintf(fp, " | Status: OK | \n");
	fprintf(fp, "==================================================================================\n\n");
}

