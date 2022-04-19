/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:32:27 by dha               #+#    #+#             */
/*   Updated: 2022/04/19 15:27:14 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start(t_root *root)
{
	int			i;
	pthread_t	thread;

	i = 0;
	root->start = get_cur_time();
	while (i < root->num_of_philo)
	{
		root->philos[i].last = root->start;
		pthread_create(&(root->philos[i].thread), NULL,
			dining, &(root->philos[i]));
		i++;
	}
	pthread_create(&thread, NULL, scanner, root);
	pthread_detach(thread);
}

static void	mutex_destory(pthread_mutex_t *mutex)
{
	int	err;

	err = pthread_mutex_destroy(mutex);
	if (err == EBUSY)
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_destroy(mutex);
	}
}

static void	end(t_root *root)
{
	int	i;

	i = 0;
	while (i < root->num_of_philo)
	{
		pthread_join(root->philos[i].thread, NULL);
		mutex_destory(&(root->forks[i]));
		mutex_destory(&(root->philos[i++].mutex));
	}
	mutex_destory(&(root->mutex));
	mutex_destory(&(root->output_mutex));
	free(root->philos);
	free(root->forks);
}

int	main(int argc, char **argv)
{
	t_root	root;

	if (set_args(&root, argc, argv))
		return (1);
	if (init_table(&root))
		return (1);
	start(&root);
	end(&root);
}
