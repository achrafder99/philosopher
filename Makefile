# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adardour <adardour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 19:09:59 by adardour          #+#    #+#              #
#    Updated: 2023/06/10 13:48:44 by adardour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
EXECUTABLE= philo

SRCS = philo.c ./utils/ft_atoi.c ./utils/ft_isdigit.c ./init_struct.c ./main.c \
./times/currenttime.c ./times/my_own_usleep.c \
./track_conditions.c ./inits.c

CC		= cc -g -fsanitize=thread
RM		= rm -rf
CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:%.c=%.o}

all:	${NAME}

%.o:%.c philo.h
		${CC} ${CFLAGS} -c  $< -o ${<:%.c=%.o}
		
$(NAME): ${OBJS} philo.h
		${CC}  ${CFLAGS} ${OBJS} -o ${EXECUTABLE}
clean:
		${RM}  ${OBJS} 

fclean:	clean
		${RM} ${NAME} 
		
re:		fclean all
