/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:39:47 by jefernan          #+#    #+#             */
/*   Updated: 2022/10/13 22:36:26 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitoring.h"
#include "../get_next_line/get_next_line.h"

int protocol_ping(char **line, t_ping *ping)
{
	int		pid;
	int		status;
	int		fd[2];
	t_data	data;

	data.monitoring = fopen("monitoring.log", "at");
	init_sping(line, ping);
	if (pipe(fd) == -1)
	{
		printf("Error pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Error fork");
		exit(1);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execlp("ping", "ping", ping->address, "-c", "1", NULL);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	read_ping(ping, fd[0], data.monitoring);
	close(fd[0]);
	fclose(data.monitoring);
	return (0);
}

void	init_sping(char **line, t_ping *ping)
{
	ping->name = line[0];
	ping->protocol = line[1];
	ping->address = line[2];
	ping->interval = ft_atoi(line[3]);
}

void	read_ping(t_ping *ping, int fd, FILE *fp)
{
	char *line;

	line = get_next_line(fd);
	if (!line)
		printf("Error");
	fprintf(fp, "\n");
	while (line)
	{
		fprintf(fp, "%s", line);
		print_ping(ping, line, fp);
		free(line);
		line = get_next_line(fd);
	}
}

void	print_ping(t_ping *ping, char *line, FILE *fp)
{
	char	*time;
	char	*statistic;

	statistic = ft_strnstr(line, "packets", ft_strlen(line));
	time = ft_strnstr(line, "time", ft_strlen(line));
	if (statistic)
	{

		printf("Name: %s\n", ping->name);
		printf("Protocol: %s\n", ping->protocol);
		printf("Address: %s\n", ping->address);
		printf("%s\n", line);
		if (ft_strnstr(line, "1 received", ft_strlen(line)))
			printf("%s | Status: OK | %s\n", GREEN, RESET);
		else
			printf("%s | Status: KO | %s\n", RED, RESET);
		printf("%s==================================================================================\n\n%s", UNDER_BLUE, RESET);

		fprintf(fp, "Name: %s\n", ping->name);
		fprintf(fp, "Name: %s\n", ping->protocol);
		fprintf(fp, "Name: %s\n", ping->address);
		fprintf(fp, "Name: %s\n", line);
		if (ft_strnstr(line, "1 received", ft_strlen(line)))
			fprintf(fp, " | Status: OK | \n");
		else
			fprintf(fp, " | Status: KO | \n");
		fprintf(fp, "==================================================================================\n\n");
	}
	else if (time)
	{
		printf("%s==================================monitoring ping=================================\n%s", UNDER_BLUE, RESET);
		printf("Ping: %s\n", time);
		fprintf(fp, "==================================monitoring ping=================================\n");
		fprintf(fp, "Time: %s\n", time);
	}
}

