/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:31:41 by jefernan          #+#    #+#             */
/*   Updated: 2022/08/01 14:17:18 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MONITORING_H
# define MONITORING_H

#include <stdio.h>
#include <curl/curl.h>

typedef struct s_http
{
	char    *name;
    char    *protocol;
    char    *route;
    char    *method;
    int status;
    int interval;
}	t_http;

typedef struct s_ping
{
	char    *name;
    char    *protocol;
    char    *route;
    int     interval;
}	t_ping;

typedef struct s_dns
{
	char    *name;
    char    *protocol;
    char    *route;
    int     interval;
}	t_dns;

int main(void);
int http(void);

#endif