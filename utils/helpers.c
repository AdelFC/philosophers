/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:02:01 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/23 14:00:35 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_or_exit(pthread_mutex_t *mtx)
{
	if (pthread_mutex_lock(mtx) != 0)
		ft_error("Error: mutex lock failed");
}

void	unlock_or_exit(pthread_mutex_t *mtx)
{
	if (pthread_mutex_unlock(mtx) != 0)
		ft_error("Error: mutex unlock failed");
}

int	get_end_simulation(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->end_mtx);
	end = table->end_simulation;
	pthread_mutex_unlock(&table->end_mtx);
	return (end);
}

void	set_end_simulation(t_table *table, int val)
{
	pthread_mutex_lock(&table->end_mtx);
	table->end_simulation = val;
	pthread_mutex_unlock(&table->end_mtx);
}
