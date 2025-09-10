/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:49:41 by meandrad          #+#    #+#             */
/*   Updated: 2025/09/09 22:22:55 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc == 5 || argc == 6)
	{
		if (check_data(&data, argc, argv) != 0)
		{
			free_data(&data);
			return (1);
		}
		if (philosophers(&data) != 0)
		{
			free_data(&data);
			return (1);
		}
	}
	else
		printf(ERROR_MESSAGE);
	free_data(&data);
	return (0);
}
