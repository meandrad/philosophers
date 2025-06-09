/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:33:59 by meandrad          #+#    #+#             */
/*   Updated: 2025/06/09 19:41:30 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define ERROR_MESSAGE "Error: ./philo <number_of_philosophers> <time_to_die> \
						<time_to_eat> <time_to_sleep> Optional argument: \
						<number_of_times_each_philosopher_must_eat> \n"

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	meal;
	unsigned long	last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat;
	unsigned int	is_dead;

	unsigned long	start_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
}					t_data;

//utils
void	ft_putstr(char *s, int fd);

#endif