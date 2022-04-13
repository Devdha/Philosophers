/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:04:39 by dha               #+#    #+#             */
/*   Updated: 2022/04/13 16:06:38 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*scanner(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (philo->root->dead == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&philo->root->mutex);
		if (get_cur_time() - philo->last > philo->root->time_to_die && \
			philo->root->dead == 0)
		{
			printf("%lu %d died\n", get_cur_time() - philo->root->start,
				philo->id);
			philo->root->dead = 1;
		}
		pthread_mutex_unlock(&philo->root->mutex);
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}
