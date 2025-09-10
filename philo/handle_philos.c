/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:10:59 by meandrad          #+#    #+#             */
/*   Updated: 2025/09/09 22:21:44 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_behavior(t_philo *philo, char *action)
{
	unsigned long	timestamp;

	if (!ft_strcmp(action, "ate_enough"))
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("Philosophers ate %u times!\n", philo->data->nbr_of_meals);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (0);
	}
	pthread_mutex_lock(&philo->data->state_mutex);
	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lu %u %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (philo->data->dead || philo->data->check_ate)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	return (0);
}

int	eat_time(t_philo *philo)
{
	if (philo_behavior(philo, "is eating"))
		return (1);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->last_meal = get_time();
	philo->meal++;
	pthread_mutex_unlock(&philo->data->state_mutex);
	if (should_stop(philo->data))
		return (1);
	safe_usleep(philo->data->time_to_eat, philo);
	return (0);
}

int	sleep_time(t_philo *philo)
{
	if (philo_behavior(philo, "is sleeping"))
		return (1);
	if (should_stop(philo->data))
		return (1);
	safe_usleep(philo->data->time_to_sleep, philo);
	return (0);
}

int	think_time(t_philo *philo)
{
	return (philo_behavior(philo, "is thinking"));
}
