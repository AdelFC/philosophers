/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:47:41 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/23 14:13:26 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc < 5 || argc > 6)
		ft_error("Error: Incorrect input");
	parse_input(&table, argv);
	init_table(&table);
	start_simulation(&table);
	i = 0;
	while (i < table.philo_nbr)
		pthread_mutex_destroy(&table.forks[i++].fork);
	i = 0;
	while (i < table.philo_nbr)
		pthread_mutex_destroy(&table.philos[i++].philo_mtx);
	pthread_mutex_destroy(&table.print_lock);
	pthread_mutex_destroy(&table.end_mtx);
	free(table.forks);
	free(table.philos);
	return (SUCCESS);
}
