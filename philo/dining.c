/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:06:56 by dha               #+#    #+#             */
/*   Updated: 2022/04/17 22:08:48 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_in_thread(philo, "has taken a fork", get_cur_time());
	pthread_mutex_lock(philo->rfork);
	print_in_thread(philo, "has taken a fork", get_cur_time());
	pthread_mutex_lock(&(philo->mutex));
	if (!is_dead(philo->root))
		print_in_thread(philo, "is eating", philo->last);
	philo->total_eat++;
	philo->last = get_cur_time();
	wait_action(philo->last, philo->root->time_to_eat);
	pthread_mutex_unlock(&(philo->mutex));
	// printf("eat: %d %ld\n", philo->id, get_cur_time() - philo->last);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (is_dead(philo->root));
}

int	philo_sleep(t_philo *philo)
{
	time_t	cur;

	cur = get_cur_time();
	if (!is_dead(philo->root))
		print_in_thread(philo, "is sleeping", cur);
	wait_action(cur, philo->root->time_to_sleep);
	usleep(50);
	return (is_dead(philo->root));
}

void	philo_think(t_philo *philo)
{
	time_t	cur;

	cur = get_cur_time();
	if (!is_dead(philo->root))
		print_in_thread(philo, "is thinking", philo->last);
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
		if (philo_sleep(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}