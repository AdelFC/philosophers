/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:03:31 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/24 11:04:20 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_for_start(t_table *table)
{
	pthread_mutex_lock(&table->start_mtx);
	while (!table->start_simulation)
	{
		pthread_mutex_unlock(&table->start_mtx);
		usleep(100);
		pthread_mutex_lock(&table->start_mtx);
	}
	pthread_mutex_unlock(&table->start_mtx);
}
