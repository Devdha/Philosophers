/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:32:27 by dha               #+#    #+#             */
/*   Updated: 2022/04/21 20:21:28 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start(t_root *root)
{
	int			i;
	pthread_t	thread;

	i = 0;
	root->start = get_cur_time();
	while (i < root->num_of_philo)
	{
		root->philos[i].last = root->start;
		if (pthread_create(&(root->philos[i].thread), NULL,
			dining, &(root->philos[i])) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&thread, NULL, scanner, root) != 0)
		return (1);
	pthread_detach(thread);
	return (0);
}

static void	mutex_destory(pthread_mutex_t *mutex)
{
	int	err;

	err = pthread_mutex_destroy(mutex);
	if (err != 0)
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_destroy(mutex);
	}
}

int	end(t_root *root, int is_err)
{
	int	i;

	i = 0;
	if (is_err == 1)
		ft_putstr_fd("Error: Init falied\n", 2);
	while (i < root->num_of_philo)
	{
		if (is_err == 0)
			pthread_join(root->philos[i].thread, NULL);
		mutex_destory(&(root->forks[i]));
		mutex_destory(&(root->philos[i++].mutex));
	}
	mutex_destory(&(root->mutex));
	mutex_destory(&(root->output_mutex));
	free(root->philos);
	free(root->forks);
	return (1);
}

int	main(int argc, char **argv)
{
	t_root	root;

	if (set_args(&root, argc, argv))
		return (1);
	if (init_table(&root))
		return (1);
	if (start(&root))
		return (end(&root, 1));
	end(&root, 0);
	return (0);
}
