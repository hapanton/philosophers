# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsergean <qsergean@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/30 20:11:30 by qsergean          #+#    #+#              #
#    Updated: 2022/07/08 13:58:47 by qsergean         ###   ########.fr        #
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

NAME			=	philo_bonus

SRCS			=	sources/philo_bonus.c		sources/ft_ll_atoi.c\
					sources/lifestyle_bonus.c	sources/creators_bonus.c	sources/ft_atoi.c\
					sources/ft_isdigit.c		sources/utils_bonus.c

OBJS			=	$(SRCS:.c=.o)
HEADER			=	includes/philo_bonus.h
MAKE			= 	Makefile

LIBC			=	ar rc
LIBR			=	ranlib

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
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
