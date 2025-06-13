/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_dinner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:23:11 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/13 17:28:04 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    wait_all_threads(t_table *table)
{
    int val;
    int ready;

    while (1)
    {
        val = pthread_mutex_lock(&table->table_mutex);
        if (val != 0)
            ft_error("Impossible de verrouiller le mutex table_mutex");
        ready = table->all_threads_ready;
        val = pthread_mutex_unlock(&table->table_mutex);
        if (val != 0)
            ft_error("Impossible de déverrouiller le mutex table_mutex");
        if (ready)
            break;
    }
}
