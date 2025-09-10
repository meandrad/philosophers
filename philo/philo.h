/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:33:59 by meandrad          #+#    #+#             */
/*   Updated: 2025/09/09 22:30:35 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
	unsigned int	dead;
	unsigned int	nbr_of_meals;
	unsigned int	check_ate;
	unsigned long	start_time;
	t_philo			*philo;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
}					t_data;

//data
long	get_time(void);
void	safe_usleep(unsigned long duration, t_philo *philo);
void	free_data(t_data *data);
int		alloc_data(t_data *data);

//handle_forks
int		take_fork(t_philo *philo, unsigned int *left_fork,
			unsigned int *right_fork);
int		release_fork(t_philo *philo, unsigned int *left_fork,
			unsigned int *right_fork);
void	clean_fork(t_philo *philo, unsigned int *left_fork,
			unsigned int *right_fork);

//handle_philos
int		philo_behavior(t_philo *philo, char *action);
int		eat_time(t_philo *philo);
int		sleep_time(t_philo *philo);
int		think_time(t_philo *philo);

//init
int		check_data(t_data *data, int argc, char **argv);
int		philosophers(t_data *data);

//monitor
void	*monitor_routine(void *arg);
int		should_stop(t_data *data);

//utils
int		parsing(t_data *data, int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);

#endif