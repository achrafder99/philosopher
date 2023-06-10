/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:12:01 by adardour          #+#    #+#             */
/*   Updated: 2023/06/10 13:49:30 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long long			start_time;
	int					number_of_eat;
}						t_data;

typedef struct t_philo_node
{
	int					eat;
	long long			start_time;
	int					id;
	int					last_meal;
	pthread_mutex_t		mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		eat_mutex;
	t_data				data;
	struct t_philo_node	*next;
}						t_philo_node;

int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						main(int c, char **argv);
void					init_args(t_data *data, char **args, int c);
int						check_args(char **args);
t_philo_node			*create_structs_for_philo(int number_philo,
							t_data *data);
void					start_simulation(t_philo_node *head, pthread_t *threads,
							int numbr_of_philo);
void					init_philo(pthread_t **threads, int number_of_philo);
long long				current_time(void);
void					my_own_usleep22(long long time_stamps);
void					track_conditions(t_philo_node *head,
							int number_of_philo);
void					print_task(char *message, long long time_stamps,
							t_philo_node *philo);
void					init_args(t_data *data, char **args, int c);
void					init_args(t_data *data, char **args, int c);
void					initialize_mutexes(t_philo_node *philosophers,
							int number_of_philo);

#endif