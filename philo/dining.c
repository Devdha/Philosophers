/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:06:56 by dha               #+#    #+#             */
/*   Updated: 2022/04/21 09:17:57 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_eat(t_philo *philo)
{
	time_t	cur;

	pthread_mutex_lock(philo->lfork);
	if (!is_dead(philo->root))
		print_in_thread(philo, "has taken a fork", get_cur_time());
	if (philo->root->num_of_philo == 1)
	{
		wait_action(get_cur_time(), philo->root->time_to_die + 100);
		return (1);
	}
	pthread_mutex_lock(philo->rfork);
	if (!is_dead(philo->root))
		print_in_thread(philo, "has taken a fork", get_cur_time());
	pthread_mutex_lock(&(philo->mutex));
	philo->total_eat++;
	philo->last = get_cur_time();
	if (!is_dead(philo->root))
		print_in_thread(philo, "is eating", philo->last);
	cur = philo->last;
	pthread_mutex_unlock(&(philo->mutex));
	wait_action(cur, philo->root->time_to_eat);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (is_dead(philo->root));
}

static int	philo_sleep(t_philo *philo)
{
	time_t	cur;

	cur = get_cur_time();
	if (!is_dead(philo->root))
		print_in_thread(philo, "is sleeping", cur);
	wait_action(cur, philo->root->time_to_sleep);
	usleep(50);
	return (is_dead(philo->root));
}

static void	philo_think(t_philo *philo)
{
	time_t	cur;

	cur = get_cur_time();
	if (!is_dead(philo->root))
		print_in_thread(philo, "is thinking", cur);
}

int	is_done(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex));
	if (philo->total_eat == philo->root->limit_to_eat)
	{
		pthread_mutex_unlock(&(philo->mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->mutex));
	return (0);
}

void	*dining(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_dead(philo->root))
	{
		if (philo_eat(philo))
			break ;
		if (philo->root->limit_to_eat != 0 && is_done(philo))
		{
			pthread_mutex_lock(&(philo->root->mutex));
			philo->root->cnt++;
			pthread_mutex_unlock(&(philo->root->mutex));
		}
		if (philo_sleep(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
