/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 23:37:03 by adardour          #+#    #+#             */
/*   Updated: 2023/06/16 17:04:53 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	destroy_mutexes(int numbr_of_philo, t_philo_node *node)
{
	int				i;
	t_philo_node	*current;

	i = 0;
	current = node;
	while (i < numbr_of_philo)
	{
		pthread_mutex_destroy(&current->mutex);
		pthread_mutex_destroy(&current->last_meal_mutex);
		pthread_mutex_destroy(&current->print_mutex);
		pthread_mutex_destroy(&current->eat_mutex);
		current = current->next;
		i++;
	}
}

int	parse_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	if (args[i] == NULL)
		return (0);
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][0] == '+')
				j++;
			if (!ft_isdigit(args[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int c, char **argv)
{
	t_data			*data;
	pthread_t		*threads;
	t_philo_node	*head;

	threads = NULL;
	head = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (c <= 4 || c > 6 || !parse_args(argv))
	{
		free(data);
		return (write(2, "Error Parsing\n", 15), 1);
	}
	if (ft_atoi(argv[1]) == 0)
		return (printf("One or more philosophers sit at a round table.\n"), 1);
	init_args(data, argv, c);
	init_philo(&threads, data->number_of_philosophers);
	head = create_structs_for_philo(data->number_of_philosophers, data);
	initialize_mutexes(head, data->number_of_philosophers);
	to_do(head, threads, data->number_of_philosophers);
	free(data);
	free(threads);
	destroy_mutexes(data->number_of_philosophers, head);
}
