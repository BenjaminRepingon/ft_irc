/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 14:49:09 by mgarcin           #+#    #+#             */
/*   Updated: 2014/05/23 15:32:47 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/serveur.h"

char		*ft_who(char *buff, t_client *client, t_server *server)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	(void)buff;
	while (i < MAX_CLIENTS)
	{
		if (server->clients[i].name)
		{
			if (check_channel(*client, server->clients[i]))
			{
				if (count)
					write_client(client->sock, "\n");
				write_client(client->sock, server->clients[i].name);
				count++;
			}
		}
		i++;
	}
	return (NULL);
}

char		*ft_channels(char *buff, t_client *client)
{
	int		i;
	char	*tmp;

	i = 0;
	if (buff[6] != ' ')
		return ("Invalid command");
	tmp = ft_strsub(buff, 7, ft_strlen(buff) - 7);
	while (i < MAX_CHANNEL)
	{
		if (client->channel[i] && tmp)
		{
			if (ft_strcmp(client->channel[i], tmp) == 0)
			{
				client->channel[i] = NULL;
				client->nb_channel--;
				return ("Leave success");
			}
		}
		i++;
	}
	return ("Channel not found");
}

char		*ft_leave(char *buff, t_client *client, t_server *server)
{
	int		i;

	i = 0;
	(void)server;
	if (ft_strlen(buff) > 6)
	{
		ft_channels(buff, client);
	}
	else
	{
		while (i < MAX_CHANNEL)
			client->channel[i++] = NULL;
		client->nb_channel = 0;
	}
	return ("All channels leaved");
}
