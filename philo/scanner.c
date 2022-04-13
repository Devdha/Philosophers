/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:04:39 by dha               #+#    #+#             */
/*   Updated: 2022/04/13 21:50:10 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*scanner(void *ptr)
{
	time_t	cur;
	t_philo	*philo;

	philo = ptr;
	while (philo->root->dead == 0)
	{
		pthread_mutex_lock(&philo->root->mutex);
		pthread_mutex_lock(&philo->mutex);
		cur = get_cur_time();
		if (cur - philo->last >= philo->root->time_to_die && \
			philo->root->dead == 0)
		{
			philo->root->dead = 1;
			printf("%ld %d died\n", cur - philo->root->start,
				philo->id);
		}
		pthread_mutex_unlock(&philo->root->mutex);
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}
