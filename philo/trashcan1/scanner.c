/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:04:39 by dha               #+#    #+#             */
/*   Updated: 2022/04/17 19:41:13 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_dead(t_philo *philo)
{
	int	is_dead;

	is_dead = 0;
	pthread_mutex_lock(&(philo->root->mutex));
	if (philo->root->dead)
		is_dead = 1;
	pthread_mutex_unlock(&(philo->root->mutex));
	return (is_dead);
}

void	*scanner(void *ptr)
{
	time_t	cur;
	t_philo	*philo;

	philo = ptr;
	while (!is_dead(philo))
	{
		cur = get_cur_time();
		pthread_mutex_lock(&(philo->mutex));
		if (cur - philo->last >= philo->root->time_to_die)
		{
			if (!is_dead(philo))
			{
				philo->root->dead = 1;
				printf("%ld %d died\n", cur - philo->root->start,
					philo->id);
			}
		}
		pthread_mutex_unlock(&(philo->mutex));
	}
	return (NULL);
}
