/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:17:04 by meandrad          #+#    #+#             */
/*   Updated: 2025/09/09 22:28:48 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pair_philo(t_philo *philo, unsigned int *left_fork,
	unsigned int *right_fork)
{
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	*left_fork = 1;
	if (should_stop(philo->data))
		return (1);
	if (philo_behavior(philo, "has taken a fork"))
		return (1);
	if (philo->data->n_philo == 1)
		return (1);
	pthread_mutex_lock(&philo->data->forks[philo->id
		% philo->data->n_philo]);
	*right_fork = 1;
	if (should_stop(philo->data))
		return (1);
	if (philo_behavior(philo, "has taken a fork"))
	{
		return (1);
	}
	return (0);
}

static int	odd_philo(t_philo *philo, unsigned int *left_fork,
		unsigned int *right_fork)
{
	pthread_mutex_lock(&philo->data->forks[philo->id
		% philo->data->n_philo]);
	*right_fork = 1;
	if (should_stop(philo->data))
		return (1);
	if (philo_behavior(philo, "has taken a fork"))
		return (1);
	if (philo->data->n_philo == 1)
		return (1);
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	*left_fork = 1;
	if (should_stop(philo->data))
		return (1);
	if (philo_behavior(philo, "has taken a fork"))
	{
		return (1);
	}
	return (0);
}

int	take_fork(t_philo *philo, unsigned int *left_fork,
	unsigned int *right_fork)
{
	if (philo->id % 2 == 0)
		return (pair_philo(philo, left_fork, right_fork));
	else
	{
		safe_usleep(5, philo);
		return (odd_philo(philo, left_fork, right_fork));
	}
}

int	release_fork(t_philo *philo, unsigned int *left_fork,
		unsigned int *right_fork)
{
	if (*left_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		*left_fork = 0;
	}
	if (*right_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id
			% philo->data->n_philo]);
		*right_fork = 0;
	}
	return (0);
}

void	clean_fork(t_philo *philo, unsigned int *left_fork,
	unsigned int *right_fork)
{
	if (*left_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		*left_fork = 0;
	}
	if (*right_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id
			% philo->data->n_philo]);
		*right_fork = 0;
	}
}
