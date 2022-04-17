/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:56:46 by dha               #+#    #+#             */
/*   Updated: 2022/04/17 18:55:59 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	if (is_dead(philo))
		return ;
	printf("%ld %d has taken a fork\n", get_cur_time() - philo->root->start,
		philo->id);
	pthread_mutex_lock(philo->rfork);
	if (is_dead(philo))
		return ;
	printf("%ld %d has taken a fork\n", get_cur_time() - philo->root->start,
		philo->id);
}

static int	philo_eat(t_philo *philo)
{
	philo_get_forks(philo);
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

static int	philo_sleep(t_philo *philo)
{
	time_t	cur;

	cur = get_cur_time();
	if (!is_dead(philo))
	{
		printf("%ld %d is sleeping\n", cur - philo->root->start,
			philo->id);
	}
	wait_action(cur, philo->root->time_to_sleep);
	usleep(10);
	return (is_dead(philo));
}

static int	philo_think(t_philo *philo)
{
	if (!is_dead(philo))
	{
		printf("%ld %d is thinking\n", get_cur_time() - philo->root->start,
			philo->id);
	}
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
		if (philo_sleep(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}