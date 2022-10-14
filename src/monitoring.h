/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:31:41 by jefernan          #+#    #+#             */
/*   Updated: 2022/10/13 22:25:20 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
#define MONITORING_H

#include <stdio.h>
#include <curl/curl.h>
#include <fcntl.h> // open O_RDONLY
#include <stdlib.h> //malloc
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FILEDB		"./src/monitoring.db"
#define FILELOG		"monitoring.log"

//  - Colors
#define RED			"\e[0;31m"
#define GREEN		"\e[0;32m"

#define UNDER_BLUE	"\e[4;34m"
#define RESET		"\e[0m"

typedef struct s_http
{
	char	*name;
	char	*protocol;
	char	*address;
	char	*method;
	int		http_code;
	int		interval;
	long	response_code;

} t_http;

typedef struct s_ping
{
	char	*name;
	char	*protocol;
	char	*address;
	int		interval;
} t_ping;

typedef struct s_dns
{
	char	*name;
	char	*protocol;
	char	*address;
	int		interval;
	char	*dns_server;
} t_dns;

typedef struct s_data
{
	FILE	*monitoring;
	int		db;
} t_data;

int		open_file(t_http *http, t_ping *ping, t_dns *dns);
void	free_line(char **line);

// UTILS
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

// HTTP
int		protocol_http(char **line, t_http *http);
void	init_shttp(char **line, t_http *http);
void	print_http(t_http *http, FILE *fp);

// PING
int protocol_ping(char **line, t_ping *ping);
void	init_sping(char **line, t_ping *ping);
void	read_ping(t_ping *ping, int fd, FILE *fp);
void	print_ping(t_ping *ping, char *line, FILE *fp);

#endif