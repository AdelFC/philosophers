/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:54:54 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/13 19:00:42 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void *dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while(philo->table->end_simulation == 0)
	{
		if (philo->full)
			break ;
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
		return;
	else
	{
		while (i < table->philo_nbr)
		{
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
			i++;
		}
	}
	table->start_simulation = ft_time(MILLISECOND);
		
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}



	val = pthread_mutex_lock(&table->table_mutex);
	if (val != 0)
		ft_error("Impossible de verrouiller le mutex table_mutex");
	table->all_threads_ready = 1;
	val = pthread_mutex_unlock(&table->table_mutex);
	if (val != 0)
		ft_error("Impossible de déverrouiller le mutex table_mutex");
}
