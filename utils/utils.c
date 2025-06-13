/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:47:36 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/13 19:02:20 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t  ft_strlen(const char *str)
{
    size_t len;
    
    len = 0;
    while (str && str[len])
        len++;
    return (len);
}

void    ft_error(const char *error)
{
    write(2, error, ft_strlen(error));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}

long ft_time(t_time time)
{
    struct timeval  tv;
    if (gettimeofday(&tv, NULL))
        ft_error("Gettimeofday failed");
    if (SECOND == time)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (MILLISECOND == time)
        return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
    else if (MICROSECOND == time)
        return (tv.tv_sec * 1e6 + (tv.tv_usec));
    else
        ft_error("ft_time failed");
    return (ERROR);
}

void    ft_usleep(long usec, t_table *table)
{
    long    start;
    long    time;

    start = ft_time(MICROSECOND);
    while (ft_time(MICROSECOND) - start < usec)
    {
        time = ft_time(MICROSECOND) - start;
        if (table->end_simulation == 1)
            break ;
        if ((usec - time) > 1e3)
            usleep(usec / 2);
        else
        {
            while (ft_time(MICROSECOND) - start < usec)
                continue ;
        }
    }
}
