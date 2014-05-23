/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 15:29:03 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/23 16:00:13 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "../includes/serveur.h"

int		read_client(int sock, char *buff)
{
	int n;

	n = 0;
	if ((n = recv(sock, buff, BUF_SIZE, 0)) < 0)
	{
		error("recv");
		n = 0;
	}
	buff[n] = 0;
	return (n);
}

void	write_client(int sock, const char *buff)
{
	if (send(sock, buff, ft_strlen((char *)buff), 0) < 0)
		exit_error("send");
}

void	srv_to_all(t_client *c, t_client s, int act, char *buff)
{
	int		i;
	char	*message;

	printf("%s\n", buff);
	i = 0;
	message = ft_strdup(buff);
	while (i < act)
	{
		if (s.sock != c[i].sock && check_channel(s, c[i]))
			write_client(c[i].sock, message);
		i++;
	}
}

void	send_to_all(t_client *c, t_client s, int act, char *buff)
{
	int		i;
	char	*message;

	printf("%s\n", buff);
	i = 0;
	message = ft_strdup(s.name);
	message = ft_strjoin(message, " : ");
	message = ft_strjoin(message, buff);
	while (i < act)
	{
		if (s.sock != c[i].sock && check_channel(s, c[i]))
			write_client(c[i].sock, message);
		i++;
	}
}

void	if_read(t_server *server, int *actual, char *buff, int i)
{
	t_client	client;

	client = server->clients[i];
	close(server->clients[i].sock);
	remove_client(server, i, actual);
	ft_strncpy(buff, client.name, NAME_LEN);
	ft_strncat(buff, " disconnected !", BUF_SIZE - ft_strlen(buff));
	srv_to_all(server->clients, client, *actual, buff);
	ft_bzero(client.name, NAME_LEN);
}
