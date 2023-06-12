/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_conditions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:04:27 by adardour          #+#    #+#             */
/*   Updated: 2023/06/10 15:22:32 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	count_number_of_eat(t_philo_node
*current, int *count, int *number_of_eat)
{
	int	i;

	i = 0;
	while (i < current->data.number_of_philosophers)
	{
		if (number_of_eat[i] >= current->data.number_of_eat)
			(*count)++;
		i++;
	}
}

int	check_stat_eating(t_philo_node *current, int number_of_philo)
{
	static int	count;
	static int	init;
	static int	*number_of_eat;

	if (init == 0)
	{
		number_of_eat = malloc(sizeof(int) * number_of_philo);
		memset(number_of_eat, 0, sizeof(int) * number_of_philo);
		init = 1;
	}
	pthread_mutex_lock(&current->eat_mutex);
	if (current->eat == 1)
	{
		number_of_eat[current->id - 1] += 1;
		count_number_of_eat(current, &count, number_of_eat);
		if (count >= number_of_philo)
			return (1);
		current->eat = 0;
	}
	pthread_mutex_unlock(&current->eat_mutex);
	return (0);
}

int	check_death(t_philo_node *philo)
{
	long long	last_meal;
	long long	current;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	current = current_time() - philo->start_time;
	if (current - last_meal >= philo->data.time_to_die)
	{
		print_task("died", current - last_meal, philo);
		return (1);
	}
	return (0);
}

void	track_conditions(t_philo_node *head, int number_of_philo)
{
	t_philo_node	*current;

	current = head;
	while (1)
	{
		if (check_death(current) || \
				(check_stat_eating(current, number_of_philo) \
				&& current->data.number_of_eat \
				!= -1))
			break ;
		current = current->next;
		usleep(100);
	}
}
