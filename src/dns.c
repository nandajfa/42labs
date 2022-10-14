/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dns.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:00:01 by jefernan          #+#    #+#             */
/*   Updated: 2022/10/14 11:17:42 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"
#include "../get_next_line/get_next_line.h"

int protocol_dns(char **line, t_dns *dns)
{
	int		pid;
	//int		status;
	int		fd[2];
	t_data	data;

	data.monitoring = fopen("monitoring.log", "at");
	init_sdns(line, dns);
	if (pipe(fd) == -1)
		perror("pipe");
	if ((pid = fork()) == -1)
		perror("fork");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execlp("dig", "dig", dns->address, NULL);
	}
	//waitpid(pid, &status, 0);
	close(fd[1]);
	read_dns(dns, fd[0], data.monitoring);
	close(fd[0]);
	fclose(data.monitoring);
	return (0);
}

void	init_sdns(char **line, t_dns *dns)
{
	dns->name = line[0];
	dns->protocol = line[1];
	dns->address = line[2];
	dns->interval = ft_atoi(line[3]);
	dns->dns_server = line[4];
}

void	read_dns(t_dns *dns, int fd, FILE *fp)
{
	char *line;

	line = get_next_line(fd);
	if (!line)
		printf("Error");
	fprintf(fp, "\n");
	while (line)
	{
		fprintf(fp, "%s", line);
		print_dns(dns, line, fp);
		free(line);
		line = get_next_line(fd);
	}
}

void	print_dns(t_dns *dns, char *line, FILE *fp)
{
	char	*header;
	char	*query_time;

	header = ft_strnstr(line, "HEADER", ft_strlen(line));
	query_time = ft_strnstr(line, "Query time", ft_strlen(line));
	if (query_time)
	{
		printf("DNS: %s", query_time);
		printf("%s==================================================================================\n\n%s", UNDER_BLUE, RESET);
		fprintf(fp, "DNS: %s", query_time);
		fprintf(fp, "==================================================================================\n\n");
	}
	if (header)
	{
		printf("%s==================================monitoring DNS=================================\n%s", UNDER_BLUE, RESET);
		printf("Name: %s\n", dns->name);
		printf("Protocol: %s\n", dns->protocol);
		printf("Address: %s\n", dns->address);
		printf("Interval: %d\n", dns->interval);
		printf("DNS server: %s\n", dns->dns_server);
		printf("%s\n", line);
		if (ft_strnstr(line, "NOERROR", ft_strlen(line)))
			printf("%s | Status: OK | %s\n", GREEN, RESET);
		else
			printf("%s | Status: KO | %s\n", RED, RESET);

		fprintf(fp, "==================================monitoring DNS=================================\n");
		fprintf(fp, "Name: %s\n", dns->name);
		fprintf(fp, "Protocol: %s\n", dns->protocol);
		fprintf(fp, "Address: %s\n", dns->address);
		fprintf(fp, "Interval: %d\n", dns->interval);
		fprintf(fp, "DNS server: %s\n", dns->dns_server);
		fprintf(fp, "%s\n", line);
		if (ft_strnstr(line, "NOERROR", ft_strlen(line)))
			fprintf(fp, " | Status: OK | \n");
		else
			fprintf(fp, " | Status: KO | \n");

	}
}