/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:23:37 by jefernan          #+#    #+#             */
/*   Updated: 2022/08/03 11:59:02 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

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
	return (0);
}

void init_shttp(char **line, t_http *http)
{
	http->name = line[0];
	http->protocol = line[1];
	http->route = line[2];
	http->method = line[3];
	http->status = line[4];
	http->interval = line[5];
}
