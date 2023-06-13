/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:17:43 by adardour          #+#    #+#             */
/*   Updated: 2023/06/13 18:33:35 by adardour         ###   ########.fr       */
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

void	print_task(char *message, long long time_stamps, t_philo_node *philo)
{
	sem_unlink("/print");
	philo->print = sem_open("/print", O_CREAT | O_EXCL | O_RDWR, 0666, 1);
	sem_wait(philo->print);
	printf("%lld %d %s\n", time_stamps, philo->id, message);
	sem_post(philo->print);
	sem_close(philo->print);
	sem_unlink("/print");
}

void	my_own_usleep22(long long time_stamps, t_philo_node *philo)
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
		print_task("has taken a fork", current_time() - time, current_philo);
		sem_wait(current_philo->fork);
		print_task("has taken a fork", current_time() - time, current_philo);
		print_task("is eating", current_time() - time, current_philo);
		my_own_usleep22(current_philo->data.time_to_eat, current_philo);
		sem_post(current_philo->fork);
		sem_post(current_philo->fork);
		print_task("is sleeping", current_time() - time, current_philo);
		my_own_usleep22(current_philo->data.time_to_sleep, current_philo);
		print_task("is thinking", current_time() - time, current_philo);
	}
}

void	to_do_bonus(t_philo_node *head, int number_of_philo)
{
	sem_t			*inital_semaphore;
	t_philo_node	*philo;
	long long		start_time;
	int				i;

	sem_unlink("/semaphore");
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
		if (philo->pid == -1)
		{
			printf("Fork error\n");
			exit(EXIT_FAILURE);
		}
		if (philo->pid == 0)
		{
			usleep(100);
			run_routine(philo);
		}
		i++;
		philo = philo->next;
	}
	wait(NULL);
	sem_close(inital_semaphore);
	sem_unlink("/semaphore");
}
