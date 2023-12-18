/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:39:08 by smelicha          #+#    #+#             */
/*   Updated: 2023/12/18 16:37:50 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/// @brief Prints change of state of a given philosopher
/// @param print Mutex to protect printf
/// @param p_number Number of philosopher changing state
/// @param action What is the new state
void	print_status(pthread_mutex_t print, int p_number, int state)
{
	pthread_mutex_lock(&print);
	if (state == 1)
		printf("eating\n");
	if (state == 2)
		printf("sleaping\n");
	if (state == 3)
		printf("thonking\n");
	printf("p_number: %i\n", p_number);
	pthread_mutex_unlock(&print);
}

/// @brief Routine of a single philosopher
/// @param data Main struct where philosopher finds own data
/// @param p_num Number of philosopher, used to acces OWN data from array
void	philosopher(t_data *data, int p_num)
{
	data = data + 1 - 1;
	p_num = p_num + 1 - 1;
}
