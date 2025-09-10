/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:10:51 by meandrad          #+#    #+#             */
/*   Updated: 2025/09/09 22:24:28 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_status(t_data *data, unsigned int i,
		unsigned int *enough_meals)
{
	long			last_meal;
	unsigned long	timestamp;

	pthread_mutex_lock(&data->state_mutex);
	if (data->dead || data->check_ate)
	{
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	last_meal = data->philo[i].last_meal;
	if (get_time() - last_meal >= data->time_to_die + 6)
	{
		data->dead = 1;
		timestamp = get_time() - data->start_time;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lu %u died\n", timestamp, data->philo[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	if (*enough_meals && data->philo[i].meal < data->nbr_of_meals)
		*enough_meals = 0;
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

int	should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->state_mutex);
	stop = data->dead;
	if (!stop)
		stop = data->check_ate;
	pthread_mutex_unlock(&data->state_mutex);
	return (stop);
}

void	*monitor_routine(void *arg)
{
	t_data			*data;
	unsigned int	i;
	unsigned int	meals_done;

	data = (t_data *)arg;
	while (6)
	{
		i = 0;
		meals_done = data->nbr_of_meals > 0;
		while (i < data->n_philo)
		{
			if (philo_status(data, i++, &meals_done))
				return (NULL);
		}
		if (meals_done && !data->dead)
		{
			pthread_mutex_lock(&data->state_mutex);
			data->check_ate = 1;
			philo_behavior(&data->philo[0], "ate_enough");
			pthread_mutex_unlock(&data->state_mutex);
			return (NULL);
		}
		usleep(5);
	}
	return (NULL);
}
