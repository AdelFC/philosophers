/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:02:01 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/22 23:40:51 by afodil-c         ###   ########.fr       */
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
