/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:27:17 by dha               #+#    #+#             */
/*   Updated: 2022/04/21 22:29:54 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start(t_root *root)
{
	int	i;

	i = 0;
	root->start = get_cur_time();
	while (i < root->num_of_philo)
	{
		root->philos[i].pid = fork();
		if (root->philos[i].pid == 0)
		{
			root->philos[i].last = root->start;
			dining(&(root->philos[i]));
			break ;
		}
		else if (root->philos[i].pid < 0)
		{
			root->num_of_philo = i;
			end(root, 1);
		}
		++i;
	}
}

void	end(t_root *root, int is_err)
{
	int	i;

	i = 0;
	kill_until(root->num_of_philo, root);
	free(root->philos);
	while (i < root->num_of_philo)
		sem_close(root->philos[i++].sem_philo);
	sem_close(root->sem_fork);
	sem_close(root->sem_done);
	sem_close(root->sem_output);
	sem_close(root->sem_end);
	exit(is_err);
}

int	main(int argc, char **argv)
{
	t_root		root;
	pthread_t	thread;

	if (set_args(&root, argc, argv))
		exit(1);
	if (init_table(&root))
		exit(1);
	start(&root);
	if (argc == 6)
	{
		if (pthread_create(&thread, NULL, done_scanner, &root) != 0)
			end(&root, 1);
		pthread_detach(thread);
	}
	sem_wait(root.sem_end);
	end(&root, 0);
}
