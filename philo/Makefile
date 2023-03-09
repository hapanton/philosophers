# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/12 15:54:24 by qsergean          #+#    #+#              #
#    Updated: 2022/07/08 14:00:49 by qsergean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                               ／ﾌﾌﾌ                ム｀ヽ      #
#												/ ノ)　　 ∧　　∧　　　　）　ヽ     #
#	█▒   █▒  █████▒ >ЧИТАЮ САБЖ					/ ｜　　(´・ω ・`）ノ⌒（ゝ._,ノ   #
#	█▒   █▒  █▒ 	>ПОЛЬЗУЮСЬ МАНОМ			/　ﾉ⌒＿⌒ゝーく　 ＼　　／ 		  #
#	██████▒  ████▒ 	>СПРАШИВАЮ ПИРА СПРАВА		丶＿ ノ 　　 ノ､　　|　/ 		  #
#	█▒   █▒  █▒		>СПРАШИВАЮ ПИРА СЛЕВА		　　 `ヽ `ー-‘人`ーﾉ / 			 #
#	█▒   █▒  █████▒ >ПРАВДА ВСЕ ЭТО				　　　 丶 ￣ _人’  ﾉ			    #
#												　　　／｀ヽ _/\__				 #
# 											 	　　 ／    _/\__				#
#																			   #
# **************************************************************************** #

NAME			=	philo

SRCS			=	sources/philo.c				sources/ft_ll_atoi.c		sources/utils.c\
					sources/lifestyle.c			sources/creators.c			sources/ft_atoi.c\
					sources/ft_isdigit.c		sources/monitoring.c

OBJS			=	$(SRCS:.c=.o)
HEADER			=	includes/philo.h
MAKE			= 	Makefile

LIBC			=	ar rc
LIBR			=	ranlib

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror #-g -fsanitize=thread 
RM				=	rm -rf

%.o: %.c ${HEADER} ${MAKE}
	${CC} ${CFLAGS} -c $< -o $@ 

all: ${NAME} 

${NAME}: ${OBJS}
	$(CC) ${CFLAGS} -pthread -o $(NAME) $(OBJS)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re .c.o
