/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:55:13 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/23 14:04:01 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* monitor
* Objectif :
*   - Surveiller en continu l’état de chaque philosophe :
*       - Détecter la mort (dépassement du time_to_die sans repas).
*       - Détecter si tous les philosophes ont 
* atteint leur quota de repas (is_all_eat).
*   - Mettre fin à la simulation et afficher le message adéquat.
* Sortie :
*   - Retourne NULL lorsque la simulation doit s’arrêter.
*/
static int	monitor_check_philos(t_table *table, long now)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		lock_or_exit(&table->philos[i].philo_mtx);
		if (now - table->philos[i].last_meal_time > table->time_to_die)
		{
			ft_print_status(DIE, &table->philos[i]);
			set_end_simulation(table, 1);
			unlock_or_exit(&table->philos[i].philo_mtx);
			return (ERROR);
		}
		unlock_or_exit(&table->philos[i].philo_mtx);
		i++;
	}
	return (SUCCESS);
}

void	*monitor_loop(void *arg)
{
	t_table	*table;
	long	now;

	table = (t_table *)arg;
	while (!get_end_simulation(table))
	{
		now = ft_time(MILLISECOND);
		if (monitor_check_philos(table, now) == ERROR)
			return (NULL);
		if (is_all_eat(table))
		{
			set_end_simulation(table, 1);
			return (NULL);
		}
		ft_usleep(1000, table);
	}
	return (NULL);
}
