/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 14:08:18 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/23 14:38:56 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/client.h"

int			read_server(int sock, char *buffer)
{
	int		r;

	r = 0;
	if ((r = recv(sock, buffer, BUF_SIZE, 0)) < 0)
		exit_error("recv");
	buffer[r] = 0;
	return (r);
}

void		write_server(int sock, const char *buffer)
{
	if (send(sock, buffer, ft_strlen((char *)buffer), 0) < 0)
		exit_error("send");
}

void		read_msg(char *buff)
{
	char	*p;

	read(0, buff, BUF_SIZE);
	if ((p = ft_strstr(buff, "\n")) != NULL)
		*p = 0;
	else
		buff[BUF_SIZE] = 0;
}
