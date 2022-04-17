/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:06:56 by dha               #+#    #+#             */
/*   Updated: 2022/04/17 20:25:40 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	if (!is_dead(philo))
		printf("%ld %d has taken a fork\n", get_cur_time() - philo->root->start,
			philo->id);
	pthread_mutex_lock(philo->rfork);
	if (!is_dead(philo))
		printf("%ld %d has taken a fork\n", get_cur_time() - philo->root->start,
			philo->id);
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&(philo->mutex));
		philo->total_eat++;
		philo->last = get_cur_time();
		printf("%ld %d is eating\n", philo->last - philo->root->start,
			philo->id);
		pthread_mutex_unlock(&(philo->mutex));
	}
	wait_action(philo->last, philo->root->time_to_eat);
	printf("eat: %d %ld\n", philo->id, get_cur_time() - philo->last);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (is_dead(philo));
}

void	*dining(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_dead(philo))
	{
		if (philo_eat(philo))
			break ;
		usleep(30);
		// if (philo_sleep(philo))
		// 	break ;
		// philo_think(philo);
	}
	return (NULL);
}