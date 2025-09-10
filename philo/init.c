/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:10:59 by meandrad          #+#    #+#             */
/*   Updated: 2025/09/09 22:33:02 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo			*philo;
	unsigned int	right_fork;
	unsigned int	left_fork;

	philo = (t_philo *)arg;
	right_fork = 0;
	left_fork = 0;
	while (6)
	{
		if (should_stop(philo->data)
			|| take_fork(philo, &left_fork, &right_fork))
			break ;
		if (should_stop(philo->data) || eat_time(philo))
			break ;
		if (should_stop(philo->data)
			|| release_fork(philo, &left_fork, &right_fork))
			break ;
		if (should_stop(philo->data) || sleep_time(philo))
			break ;
		if (should_stop(philo->data) || think_time(philo))
			break ;
	}
	clean_fork(philo, &left_fork, &right_fork);
	return (NULL);
}

static void	philo_wait(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			printf("Error: failure in wait the thread [%d]!\n", i + 1);
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		printf("Error: failure in wait the monitor!\n");
}

static void	init_philo(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_time;
		data->philo[i].meal = 0;
		i++;
	}
}

int	check_data(t_data *data, int argc, char **argv)
{
	if (parsing(data, argc, argv))
		return (1);
	if (alloc_data(data))
		return (1);
	data->start_time = get_time();
	data->dead = 0;
	data->check_ate = 0;
	init_philo(data);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("Error: faliure to initialize print_mutex\n");
		free_data(data);
		return (1);
	}
	if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
	{
		printf("Error: faliure to initialize state_mutex\n");
		free_data(data);
		return (1);
	}
	return (0);
}

int	philosophers(t_data *data)
{
	unsigned int	i;

	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
	{
		printf("Error: faliure to create the monitor thread\n");
		return (1);
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->threads[i], NULL,
				philo_routine, &data->philo[i]) != 0)
		{
			printf("Error: faliure to create thread number: [%d]\n", i + 1);
			philo_wait(data);
			return (1);
		}
		i++;
	}
	philo_wait(data);
	return (0);
}
