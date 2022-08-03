/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:31:41 by jefernan          #+#    #+#             */
/*   Updated: 2022/08/02 22:12:59 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
#define MONITORING_H

#include <stdio.h>
#include <curl/curl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_http
{
	char *name;
	char *protocol;
	char *route;
	char *method;
	char *status;
	char *interval;
} t_http;

typedef struct s_ping
{
	char *name;
	char *protocol;
	char *route;
	int interval;
} t_ping;

typedef struct s_dns
{
	char *name;
	char *protocol;
	char *route;
	int interval;
} t_dns;

typedef struct s_data
{
	char *line;
} t_data;

int		open_file(t_http *http, t_ping *ping, t_dns *dns);
char	**ft_split(char const *s, char c);
int		validation(char *line);
char	**str(char *input);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		protocol_http(char **line, t_http *http);
void	init_shttp(char **line, t_http *http);

#endif