/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:17:43 by adardour          #+#    #+#             */
/*   Updated: 2023/06/15 02:47:23 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	print_task(char *message, long long time_stamps, t_philo_node *philo)
{
	sem_wait(philo->print);
	printf("%lld %d %s\n", time_stamps, philo->id, message);
	sem_post(philo->print);
}

int	check_death(t_philo_node *philo)
{
	long long	last_meal;
	long long	current;

	last_meal = philo->last_meal;
	current = current_time() - philo->start_time;
	if (current - last_meal >= philo->data.time_to_die)
	{
		print_task("died", current - last_meal, philo);
		return (1);
	}
	return (0);
}

void	run_routine(t_philo_node *current_philo)
{
	while (1)
	{
		sem_wait(current_philo->fork);
		print_task("has taken a fork", current_time()
			- current_philo->start_time, current_philo);
		if (current_philo->data.number_of_philosophers == 1)
			my_own_usleep22(current_philo->data.time_to_die, current_philo);
		sem_wait(current_philo->fork);
		print_task("has taken a fork", current_time()
			- current_philo->start_time, current_philo);
		print_task("is eating", current_time() - current_philo->start_time,
			current_philo);
		current_philo->last_meal = current_time() - current_philo->start_time;
		my_own_usleep22(current_philo->data.time_to_eat, current_philo);
		sem_post(current_philo->fork);
		sem_post(current_philo->fork);
		print_task("is sleeping", current_time() - current_philo->start_time,
			current_philo);
		my_own_usleep22(current_philo->data.time_to_sleep, current_philo);
		print_task("is thinking", current_time() - current_philo->start_time,
			current_philo);
	}
}

void	just_run(t_philo_node *philo)
{
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
}

void	to_do_bonus(t_philo_node *head, int number_of_philo)
{
	sem_t			*inital_semaphore;
	sem_t			*print;
	t_philo_node	*philo;
	long long		start_time;
	int				i;

	int_semaphores(inital_semaphore, print, number_of_philo);
	philo = head;
	i = 0;
	start_time = current_time();
	while (i++ < number_of_philo)
	{
		philo->fork = inital_semaphore;
		philo->start_time = start_time;
		philo->print = print;
		philo->pid = fork();
		just_run(philo);
		philo = philo->next;
	}
	wait(NULL);
	close_and_kill(head, inital_semaphore, print);
}
