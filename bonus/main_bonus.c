/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:17:43 by adardour          #+#    #+#             */
/*   Updated: 2023/06/12 17:28:52 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

long long	current_time(void)
{
	long long		milliseconds;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	milliseconds = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (milliseconds);
}

void	my_own_usleep22(long long time_stamps)
{
	long long	current;

	current = current_time();
	while (current_time() - current < time_stamps)
		usleep(50);
}

void	run_routine(t_philo_node *current_philo)
{
	long long	time;

	time = current_time();
	while (1)
	{
		sem_wait(current_philo->fork);
		printf("%lld %d has taken a fork\n", current_time() - time,
			current_philo->id);
		sem_wait(current_philo->fork);
		printf("%lld %d has taken a fork\n", current_time() - time,
			current_philo->id);
		printf("%lld %d is eating \n", current_time() - time,
			current_philo->id);
		my_own_usleep22(current_philo->data.number_of_eat);
		current_philo->last_meal = current_time() - current_philo->start_time;
		sem_post(current_philo->fork);
		sem_post(current_philo->fork);
		printf("%lld %d is sleeping \n", current_time() - time,
			current_philo->id);
		my_own_usleep22(current_philo->data.time_to_sleep);
		printf("%lld %d is thinking \n", current_time() - time,
			current_philo->id);
	}
}

void	to_do_bonus(t_philo_node *head, int number_of_philo)
{
	sem_t			*inital_semaphore;
	t_philo_node	*philo;
	long long		start_time;
	int				i;

	inital_semaphore = sem_open("/semaphore", O_CREAT | O_EXCL | O_RDWR, 0666,
			number_of_philo);
	if (!inital_semaphore)
	{
		printf("Semaphore error\n");
		exit(EXIT_FAILURE);
	}
	philo = head;
	i = 0;
	start_time = current_time();
	while (i < number_of_philo)
	{
		philo->fork = inital_semaphore;
		philo->pid = fork();
		philo->start_time = start_time;
		if (philo->pid == -1)
		{
			printf("Fork error\n");
			exit(EXIT_FAILURE);
		}
		if (philo->pid == 0)
		{
			run_routine(philo);
		}
		philo = philo->next;
		i++;
	}
	wait(NULL);
	sem_close(inital_semaphore);
	unlink("/semaphore");
}

