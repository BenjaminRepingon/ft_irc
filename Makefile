# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/26 13:13:47 by rbenjami          #+#    #+#              #
#    Updated: 2014/05/23 14:49:24 by mgarcin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include		libft/Makefile.sources

export	CC		=	clang

export	INC		=	-I $(PWD)/libft

SERVEUR		=	serveur
CLIENT		=	client

CFLAGS		=	-Wall -Wextra -Werror -g

INC			+=	-I $(SERVEUR)/includes -I $(CLIENT_INC_SRC)/includes

INC_DIR		=	includes/
SRC_DIR		=	srcs/

#SERVEUR
SERVEUR_INC_FILES	=	$(SERVEUR).h

SERVEUR_INC_SRC		=	$(addprefix $(SERVEUR)_dir/$(INC_DIR), $(SERVEUR_INC_FILES))

SERVEUR_FILES		=	$(SERVEUR).c \
						read_write.c \
						client_ctrl.c \
						verif.c \
						cmd.c \
						cmd2.c

SERVEUR_SRC			=	$(addprefix $(SERVEUR)_dir/$(SRC_DIR), $(SERVEUR_FILES))

SERVEUR_OBJ			=	$(SERVEUR_SRC:.c=.o)

#CLIENT
CLIENT_INC_FILES	=	$(CLIENT).h

CLIENT_INC_SRC		=	$(addprefix $(CLIENT)_dir/$(INC_DIR), $(CLIENT_INC_FILES))

CLIENT_FILES		=	$(CLIENT).c \
						read_write.c \
						name.c

CLIENT_SRC			=	$(addprefix $(CLIENT)_dir/$(SRC_DIR), $(CLIENT_FILES))

CLIENT_OBJ			=	$(CLIENT_SRC:.c=.o)

#LIBFT
OBJ_LIB		=	$(libft/SRC_LIB:.c=.o)

HEAD_LIB	=	libft/libft.h

LIB			=	-L./ -lft

all:			libft.a $(SERVEUR) $(CLIENT)

libft.a:		libft/$(OBJ_LIB) $(HEAD_LIB)
	@make -C libft

$(SERVEUR):		$(SERVEUR_OBJ)
	@$(CC) $(CFLAGS) -o $(SERVEUR) $(SERVEUR_OBJ) $(LIB)
	@echo ""
	@echo "\033[33m"Compilation of $(SERVEUR) : "\033[32m"Success"\033[0m"

$(CLIENT):		$(CLIENT_OBJ)
	@$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) $(LIB)
	@echo ""
	@echo "\033[33m"Compilation of $(CLIENT) : "\033[32m"Success"\033[0m"

%.o:			%.c
	@echo -n .
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean-serveur:
	@/bin/rm -f $(SERVEUR_OBJ)
	@echo "\033[31m"Objects of $(SERVEUR) : deleted"\033[0m"

clean-client:
	@/bin/rm -f $(CLIENT_OBJ)
	@echo "\033[31m"Objects of $(CLIENT) : deleted"\033[0m"

clean: clean-serveur clean-client

fclean:			clean
	@/bin/rm -f $(CLIENT) $(SERVEUR)
	@echo "\033[31m"$(CLIENT) and $(SERVEUR) : deleted"\033[0m"
	@make fclean -C libft

re:				fclean all

norm:			$(SERVEUR_SRC) $(CLIENT_SRC) $(CLIENT_INC_SRC) $(SERVEUR_INC_SRC)
	@echo "\033[31mNORME server and client\033[0m":
	@norminette $^
	@make norm -C libft

.PHONY:			all clean fclean re clean-serveur clean-client
