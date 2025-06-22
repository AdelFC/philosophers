/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:54:54 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/22 23:40:21 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* is_all_eat
* Objectif :
*   - Vérifier si tous les philosophes ont atteint leur quota de repas (full).
*   - Protéger l’accès à l’indicateur full de chaque philosophe par mutex.
* Sortie :
*   - Retourne true si tous sont full, false sinon.
*/
bool	is_all_eat(t_table *table)
{
	int	i;
	int	full_count;

	if (table->nbr_max_meals < 0)
		return (false);
	full_count = 0;
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philos[i].philo_mtx);
		if (table->philos[i].full)
			full_count++;
		pthread_mutex_unlock(&table->philos[i].philo_mtx);
		i++;
	}
	return (full_count == table->philo_nbr);
}

/* start_simulation
* Objectif :
*   - Initialiser le timestamp de départ pour la simulation.
*   - Initialiser last_meal_time pour chaque philosophe.
*   - Lancer le thread de monitoring et les threads philosophes.
*   - Gérer le cas particulier d’un seul philosophe.
*   - Détacher les threads à la fin.
* Sortie :
*   - Lance et gère toute la vie du programme.
*/
static void	launch_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL,
				philo_routine, &table->philos[i]) != 0)
			ft_error("Error: philosopher thread creation failed");
		i++;
	}
}

void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor;

	table->start_simulation = ft_time(MILLISECOND);
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].last_meal_time = table->start_simulation;
		i++;
	}
	if (table->philo_nbr == 1)
	{
		ft_print_status(TAKE_FIRST_FORK, &table->philos[0]);
		ft_usleep(table->time_to_die * 1000, table);
		ft_print_status(DIE, &table->philos[0]);
		return ;
	}
	if (pthread_create(&monitor, NULL, &monitor_loop, table) != 0)
		ft_error("Error: monitor thread creation failed");
	launch_threads(table);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->philo_nbr)
		pthread_detach(table->philos[i++].thread_id);
}
