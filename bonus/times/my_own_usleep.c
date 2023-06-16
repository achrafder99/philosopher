/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_own_usleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:43:55 by adardour          #+#    #+#             */
/*   Updated: 2023/06/16 13:52:07 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	count_number_of_eat(t_philo_node *current,
							int *count,
							int *number_of_eat)
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
	sem_wait(current->eat_sem);
	if (current->eat == 1)
	{
		number_of_eat[current->id - 1] += 1;
		count_number_of_eat(current, &count, number_of_eat);
		if (count >= number_of_philo)
			return (1);
		current->eat = 0;
	}
	sem_post(current->eat_sem);
	return (0);
}

void	my_own_usleep22(long long time_stamps, t_philo_node *current_philo,
		int eat)
{
	long long	start_time;
	long long	until;

	start_time = current_time();
	until = time_stamps;
	if (current_philo->data.number_of_eat != -1)
	{
		if (eat == 1 && check_stat_eating(current_philo,
				current_philo->data.number_of_philosophers))
			exit(1);
	}
	while ((current_time() - start_time) < until)
	{
		if (check_death(current_philo))
			exit(1);
		usleep(50);
	}
}
