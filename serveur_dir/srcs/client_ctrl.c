/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 16:23:33 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/23 15:56:18 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "../includes/serveur.h"

void		clear_clients(t_client *clients, int actual)
{
	int		i;

	i = 0;
	while (i < actual)
	{
		close(clients[i].sock);
		i++;
	}
}

static void	init_client(t_server *server, int actual, char *name, int csock)
{
	int		i;

	i = 0;
	server->clients[actual].name = ft_strdup(name);
	server->clients[actual].sock = csock;
	server->clients[actual].nb_channel = 0;
	while (i < MAX_CHANNEL)
	{
		server->clients[actual].channel[i] = NULL;
		i++;
	}
}

int			new_client(t_server *server, int *actual, char *buff)
{
	int				csock;
	t_sockaddr_in	csin;
	socklen_t		sinsize;

	sinsize = sizeof(csin);
	csock = accept(server->sock, (t_sockaddr *)&csin, &sinsize);
	if (csock == SOCKET_ERROR)
	{
		error("accept");
		return (-1);
	}
	if (read_client(csock, buff) == -1)
		return (-1);
	while (check_pseudo(buff, server) == -1)
	{
		write_client(csock, "Pseudo already used");
		if (read_client(csock, buff) == -1)
			return (-1);
	}
	FD_SET(csock, &(server->rdfs));
	server->max = csock > server->max ? csock : server->max;
	init_client(server, *actual, buff, csock);
	(*actual)++;
	return (csock);
}

void		remove_client(t_server *serv, int rm, int *actual)
{
	t_client	*clt;

	clt = serv->clients;
	ft_memmove(clt + rm, clt + rm + 1, (*actual - rm - 1) * sizeof(t_client));
	(*actual)--;
}

void		client_talking(t_server *server, int *actual, char *buff)
{
	int			i;
	t_client	client;
	char		*tmp;

	i = 0;
	while (i < *actual)
	{
		if (FD_ISSET(server->clients[i].sock, &(server->rdfs)))
		{
			client = server->clients[i];
			if (read_client(server->clients[i].sock, buff) == 0)
			{
				if_read(server, actual, buff, i);
			}
			else if (buff[0] == '/')
			{
				if ((tmp = cmd(buff, &(server->clients[i]), server)))
					write_client(server->clients[i].sock, tmp);
			}
			else
				send_to_all(server->clients, client, *actual, buff);
			break ;
		}
		i++;
	}
}
