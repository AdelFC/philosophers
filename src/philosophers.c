/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afodil-c <afodil-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:47:41 by afodil-c          #+#    #+#             */
/*   Updated: 2025/06/13 19:04:10 by afodil-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_table table;

    if (argc < 5 || argc > 6)
    {
        ft_error("Error: Incorrect input");
    }
    parse_input(&table, argv);
    init_table(&table);
    dinner_start(&table);
    return (0);
}
