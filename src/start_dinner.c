/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:54:54 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/15 20:40:49 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void *dinner_simulation(void *data)
{
	t_philo *philo;
	int val;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while(philo->table->end_simulation == 0)
	{
		val = pthread_mutex_lock(&philo->philo_mtx);
		if (val != 0)
			ft_error("Impossible de verrouiller le mutex du philosophe");
		if (philo->full)
		{
			val = pthread_mutex_unlock(&philo->philo_mtx);
			if (val != 0)
				ft_error("Impossible de déverrouiller le mutex du philosophe");
			break;
		}
		val = pthread_mutex_unlock(&philo->philo_mtx);
		if (val != 0)
			ft_error("Impossible de déverrouiller le mutex du philosophe");
		ft_eat(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int i;
	int val;

	i = 0;
	if(table->nbr_max_meals == 0)
		return;
	else if(table->philo_nbr == 1)
	{
		table->start_simulation = ft_time(MILLISECOND);
		ft_print_status(TAKE_FIRST_FORK, &table->philos[0]);
		ft_usleep(table->time_to_die * 1e3, table);
		ft_print_status(DIE, &table->philos[0]);
		table->end_simulation = 1;
		return;
	}
	else
	{
		while (i < table->philo_nbr)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
	}
	val = pthread_mutex_lock(&table->table_mutex);
	if (val != 0)
		ft_error("Impossible de verrouiller le mutex table_mutex");
	table->start_simulation = ft_time(MILLISECOND);
	table->all_threads_ready = 1;
	val = pthread_mutex_unlock(&table->table_mutex);
	if (val != 0)
		ft_error("Impossible de déverrouiller le mutex table_mutex");
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
}
