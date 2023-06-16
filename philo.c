/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:11:14 by adardour          #+#    #+#             */
/*   Updated: 2023/06/16 00:13:48 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	protect_eat(t_philo_node *philo)
{
	if (philo->data.number_of_eat != -1)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->eat = 1;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
}

void	print_task(char *message, long long time_stamps, t_philo_node *philo)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("%lld %d %s\n", time_stamps, philo->id, message);
	pthread_mutex_unlock(&philo->print_mutex);
}

void	*tasks(void *data)
{
	t_philo_node	*philo;

	philo = (t_philo_node *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		print_task("has taken a fork", current_time() - philo->start_time,
			philo);
		pthread_mutex_lock(&philo->next->mutex);
		print_task("has taken a fork", current_time() - philo->start_time,
			philo);
		print_task("is eating", current_time() - philo->start_time, philo);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = current_time() - philo->start_time;
		pthread_mutex_unlock(&philo->last_meal_mutex);
		my_own_usleep22(philo->data.time_to_eat);
		protect_eat(philo);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->next->mutex);
		print_task("is sleeping", current_time() - philo->start_time, philo);
		my_own_usleep22(philo->data.time_to_sleep);
		print_task("is thinking", current_time() - philo->start_time, philo);
	}
	return (NULL);
}

void	to_do(t_philo_node *head, pthread_t *threads,
		int numbr_of_philo)
{
	t_philo_node	*current;
	int				i;
	long long		start_time;

	i = -1;
	current = head;
	start_time = current_time();
	while (++i < numbr_of_philo)
	{
		current->start_time = start_time;
		if (pthread_create(&threads[i], NULL, tasks, current) == -1)
		{
			printf("Error threads\n");
			break ;
		}
		if (pthread_detach(threads[i]) == -1)
		{
			printf("Error deatch\n");
			break ;
		}
		current = current->next;
		usleep(100);
	}
	track_conditions(head, numbr_of_philo);
}
