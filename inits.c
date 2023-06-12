/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:47:23 by adardour          #+#    #+#             */
/*   Updated: 2023/06/10 15:13:54 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	initialize_mutexes(t_philo_node *philosophers, int number_of_philo)
{
	int				i;
	t_philo_node	*philosopher;

	philosopher = philosophers;
	i = 0;
	while (i < number_of_philo)
	{
		pthread_mutex_init(&philosopher->mutex, NULL);
		pthread_mutex_init(&philosopher->last_meal_mutex, NULL);
		pthread_mutex_init(&philosopher->print_mutex, NULL);
		pthread_mutex_init(&philosopher->eat_mutex, NULL);
		philosopher = philosopher->next;
		i++;
	}
}

void	init_philo(pthread_t **threads, int number_of_philo)
{
	*threads = malloc(sizeof(pthread_t) * number_of_philo);
	if (!(*threads))
	{
		write(2, "error threads\n", 15);
		return ;
	}
}

void	init_args(t_data *data, char **args, int c)
{
	data->number_of_philosophers = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (c == 6)
		data->number_of_eat = ft_atoi(args[5]);
	else
		data->number_of_eat = -1;
}
