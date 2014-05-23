/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:51:49 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/23 14:39:15 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>

# define INVALID_SOCKET		(-1)
# define SOCKET_ERROR		(-1)
# define CRLF				("\r\n")
# define BUF_SIZE			(1024)
# define NAME_LEN			(9)

typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;
typedef struct in_addr		t_in_addr;

int							read_server(int sock, char *buffer);
void						write_server(int sock, const char *buffer);
void						read_msg(char *buff);
char						*pseudo(void);

#endif
