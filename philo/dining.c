/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:19:50 by dha               #+#    #+#             */
/*   Updated: 2022/04/13 16:59:34 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	printf("%ld %d has taken a fork\n", get_cur_time() - philo->root->start,
		philo->id);
	pthread_mutex_lock(philo->rfork);
	printf("%ld %d has taken a fork\n", get_cur_time() - philo->root->start,
		philo->id);
}

static void	philo_eat(t_philo *philo)
{
	philo_get_forks(philo);
	pthread_mutex_lock(&philo->root->mutex);
	pthread_mutex_lock(&philo->mutex);
	(philo->total_eat)++;
	philo->last = get_cur_time();
	if (philo->root->dead == 0)
		printf("%ld %d is eating\n", philo->last - philo->root->start,
			philo->id);
	usleep(philo->root->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->root->mutex);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

static void	philo_sleep(t_philo *philo)
{
	if (philo->root->dead == 0)
		printf("%ld %d is sleeping\n", get_cur_time() - philo->root->start,
			philo->id);
	usleep(philo->root->time_to_sleep * 1000);
	// usleep(50);
}

static void	philo_think(t_philo *philo)
{
	if (philo->root->dead == 0)
		printf("%ld %d is thinking\n", get_cur_time() - philo->root->start,
			philo->id);
}

void	*dining(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		usleep(philo->root->time_to_eat * 1000);
	while (philo->root->dead == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}