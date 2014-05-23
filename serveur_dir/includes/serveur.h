/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:08:49 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/23 15:56:44 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdio.h>
# include <netdb.h>

# define INVALID_SOCKET			(-1)
# define SOCKET_ERROR			(-1)
# define CRLF					("\r\n")
# define MAX_CLIENTS			(100)
# define BUF_SIZE				(1024)
# define NAME_LEN				(9)
# define MAX_CHANNEL			(10)

typedef struct sockaddr_in		t_sockaddr_in;
typedef struct sockaddr			t_sockaddr;
typedef struct in_addr			t_in_addr;

typedef struct					s_client
{
	int							sock;
	char						*name;
	int							nb_channel;
	char						*channel[MAX_CHANNEL];
}								t_client;

typedef struct					s_server
{
	int							sock;
	int							max;
	fd_set						rdfs;
	t_client					clients[MAX_CLIENTS];
}								t_server;

typedef struct					s_cmd
{
	char						*name;
	char						*(*f)(char *, t_client *, t_server *);
	int							len;
}								t_cmd;

int								read_client(int sock, char *buffer);
void							write_client(int sock, const char *buffer);
void							send_to_all(t_client *c, t_client cl,
								int act, char *buf);
void							srv_to_all(t_client *c, t_client cl,
								int act, char *buf);
void							clear_clients(t_client *clients, int actual);
int								new_client(t_server *server, int *actual,
											char *buff);
void							client_talking(t_server *server, int *actual,
												char *buff);
int								check_pseudo(char *buff, t_server *server);
char							*cmd(char *buff, t_client *client,
											t_server *server);
int								chk_char_name(char *line);
int								check_channel(t_client sender, t_client dest);
void							if_read(t_server *server, int *actual,
											char *buff, int i);
void							remove_client(t_server *serv, int rm,
												int *actual);
char							*ft_who(char *buff, t_client *client,
											t_server *server);
char							*ft_leave(char *buff, t_client *client,
											t_server *server);

#endif
