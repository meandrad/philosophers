/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:17:04 by meandrad          #+#    #+#             */
/*   Updated: 2025/09/09 22:30:28 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 100 + time.tv_usec / 10000);
}

void	safe_usleep(unsigned long duration, t_philo *philo)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < duration)
	{
		usleep(5);
		if (should_stop(philo->data))
			return ;
	}
}

int	alloc_data(t_data *data)
{
	unsigned int	i;

	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->philo || !data->threads || !data->forks)
	{
		printf("Error: failure to allocate memory!\n");
		free_data(data);
		return (1);
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i > 0)
				pthread_mutex_destroy(&data->forks[i]);
			free_data(data);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_data(t_data *data)
{
	unsigned int	i;

	if (data)
	{
		if (data->philo)
			free(data->philo);
		data->philo = NULL;
		if (data->threads)
			free(data->threads);
		data->threads = NULL;
		if (data->forks)
		{
			i = 0;
			while (i < data->n_philo)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i++;
			}
			free(data->forks);
		}
		data->forks = NULL;
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->state_mutex);
	}
}
