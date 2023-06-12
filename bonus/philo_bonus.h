/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:12:01 by adardour          #+#    #+#             */
/*   Updated: 2023/06/12 17:00:09 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_count
{
	int					countdigitis;
	int					index;
	int					strlenbuffer;
	char				*str;
}						t_c;

typedef struct t_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_eat;
}						t_data;

typedef struct t_philo_node
{
	long long			start_time;
	sem_t				*fork;
	int					eat;
	int					id;
	pid_t				pid;
	t_data				data;
	long	long		last_meal;
	struct t_philo_node	*next;
}						t_philo_node;

int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						parse(char **args);
int						main(int c, char **argv);
void					init_args(t_data *data, char **args, int c);
t_philo_node			*init_nodes(int number_philo, t_data *data);
void					to_do_bonus(t_philo_node *head, int number_of_philo);
int						main(int c, char **argv);

#endif