/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:04:39 by dha               #+#    #+#             */
/*   Updated: 2022/04/20 20:44:42 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_root *root)
{
	int	is_dead;

	is_dead = 0;
	pthread_mutex_lock(&(root->mutex));
	if (root->dead)
		is_dead = 1;
	pthread_mutex_unlock(&(root->mutex));
	return (is_dead);
}

int	is_all_done(t_root *root)
{
	int	is_done;

	is_done = 0;
	pthread_mutex_lock(&(root->mutex));
	if (root->num_of_philo == root->cnt)
		is_done = 1;
	pthread_mutex_unlock(&(root->mutex));
	return (is_done);
}

void	switch_to_dead(t_root *root, int i, time_t cur, int is_dead)
{
	pthread_mutex_lock(&(root->mutex));
	if (root->dead == 0)
	{
		root->dead = 1;
		if (is_dead)
			print_in_thread(&(root->philos[i]), "died", cur);
	}
	pthread_mutex_unlock(&(root->mutex));
}

void	*scanner(void *ptr)
{
	time_t	cur;
	t_root	*root;
	int		i;

	i = 0;
	root = ptr;
	while (is_dead(root) == 0)
	{
		cur = get_cur_time();
		if (root->limit_to_eat != 0 && is_all_done(root))
			switch_to_dead(root, i, cur, 0);
		pthread_mutex_lock(&(root->philos[i].mutex));
		if (cur - root->philos[i].last >= root->time_to_die)
			switch_to_dead(root, i, cur, 1);
		pthread_mutex_unlock(&(root->philos[i].mutex));
		if (++i == root->num_of_philo)
			i = 0;
	}
	return (NULL);
}
