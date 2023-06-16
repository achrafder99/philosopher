/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:12:01 by adardour          #+#    #+#             */
/*   Updated: 2023/06/16 13:59:49 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_semaphores
{
	
}	t_semaphores;

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
	int					die;
	long long			start_time;
	sem_t				*fork;
	sem_t				*eat_sem;
	sem_t				*print;
	sem_t				*print_die;
	sem_t				*last_meal_sem;
	int					eat;
	int					id;
	pid_t				pid;
	t_data				data;
	long long			last_meal;
	int					alive;
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
long long				current_time(void);
void					my_own_usleep22(long long time_stamps, \
						t_philo_node *current_philo, int eat);
int						check_death(t_philo_node *philo);
void					kill_all(t_philo_node *head);
void					close_and_kill(t_philo_node *head, \
						sem_t *inital_semaphore,
							sem_t *print, sem_t *print_die);
void					init_semaphore(sem_t **inital_semaphore, sem_t **print,
							int number_of_philo, sem_t **print_die);

#endif