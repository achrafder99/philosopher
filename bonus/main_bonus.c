/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:17:43 by adardour          #+#    #+#             */
/*   Updated: 2023/06/16 15:37:22 by adardour         ###   ########.fr       */
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
	static int	flags;

	sem_wait(philo->print_die);
	last_meal = philo->last_meal;
	current = current_time() - philo->start_time;
	if (current - last_meal >= philo->data.time_to_die)
	{
		print_task("died", current - last_meal, philo);
		flags = 1;
		return (1);
	}
	if (!flags)
		sem_post(philo->print_die);
	return (0);
}

void	run_routine(t_philo_node *philo, sem_t *forks)
{
	while (1)
	{
		sem_wait(forks);
		print_task("has taken a fork", current_time()
			- philo->start_time, philo);
		if (philo->data.number_of_philosophers == 1)
			my_own_usleep22(philo->data.time_to_die, philo, 0);
		sem_wait(forks);
		print_task("has taken a fork", current_time()
			- philo->start_time, philo);
		print_task("is eating", current_time() - philo->start_time,
			philo);
		philo->last_meal = current_time() - philo->start_time;
		my_own_usleep22(philo->data.time_to_eat, philo, 1);
		philo->eat = 1;
		sem_post(forks);
		sem_post(forks);
		print_task("is sleeping", current_time() - philo->start_time,
			philo);
		my_own_usleep22(philo->data.time_to_sleep, philo, 0);
		print_task("is thinking", current_time() - philo->start_time, philo);
		if (philo->data.time_to_eat > philo->data.time_to_sleep)
			my_own_usleep22(philo->data.time_to_eat
				- philo->data.time_to_sleep, philo, 0);
	}
}

void	just_run(t_philo_node *philo, sem_t *inital_semaphore)
{
	if (philo->pid == -1)
	{
		printf("Fork error\n");
		exit(EXIT_FAILURE);
	}
	if (philo->pid == 0)
	{
		usleep(100);
		run_routine(philo, inital_semaphore);
	}
}

void	to_do_bonus(t_philo_node *head, int number_of_philo)
{
	sem_t			*forks;
	sem_t			*print;
	sem_t			*print_die;
	sem_t			*eat_sem;
	long long		start_time;

	sem_unlink("/eat_sem");
	init_semaphore(&forks, &print, number_of_philo, &print_die);
	eat_sem = sem_open("/semaphore", O_CREAT | O_EXCL | O_RDWR, 0666,
			1);
	start_time = current_time();
	while (head)
	{
		head->start_time = start_time;
		head->print = print;
		head->print_die = print_die;
		head->eat_sem = eat_sem;
		head->pid = fork();
		just_run(head, forks);
		head = head->next;
	}
	waitpid(-1, NULL, 0);
	close_and_kill(head, forks, print, print_die);
	sem_unlink("/eat_sem");
}
