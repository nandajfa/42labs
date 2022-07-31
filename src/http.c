/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:23:37 by jefernan          #+#    #+#             */
/*   Updated: 2022/07/30 20:23:37 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"

int http(void)
{
    CURL *curl;
    CURLcode response;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://profile.intra.42.fr/");
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
        response = curl_easy_perform(curl);
        if (response != CURLE_OK)
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        else
            printf("%d\n", response);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return (0);
}
