# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adardour <adardour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 19:09:59 by adardour          #+#    #+#              #
#    Updated: 2023/06/16 16:42:20 by adardour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
EXECUTABLE = philo
BONUS_EXECUTABLE = ./bonus/philo_bonus

SRCS = philo.c ./utils/ft_atoi.c ./utils/ft_isdigit.c ./init_struct.c ./main.c \
	./times/currenttime.c ./times/my_own_usleep.c \
	./track_conditions.c ./inits.c

BONUS = ./bonus/main.c ./bonus/philo_bonus.c ./bonus/utils/ft_atoi.c ./bonus/utils/ft_isdigit.c \
./bonus/parse.c ./bonus/main_bonus.c ./bonus/times/currenttime.c ./bonus/times/my_own_usleep.c \
./bonus/kill_all.c ./bonus/close_and_kill.c ./bonus/init_semaphores.c

CC = cc 
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:%.c=%.o}
OBJSBONUS = ${BONUS:%.c=%.o}

all: ${NAME}

%.o:%.c philo.h
	${CC} -c $< -o ${<:%.c=%.o}

$(NAME): ${OBJS} philo.h
	${CC} ${OBJS} -o ${EXECUTABLE}

bonus: ${OBJS} ${OBJSBONUS} philo.h
	${CC} ${OBJSBONUS} -o ${BONUS_EXECUTABLE}

clean:
	${RM} ${OBJS} ${OBJSBONUS}

fclean: clean
	${RM} ${NAME}
	${RM} ${BONUS_EXECUTABLE}

re: fclean all