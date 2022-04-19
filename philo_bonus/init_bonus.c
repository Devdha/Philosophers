/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:30:18 by dha               #+#    #+#             */
/*   Updated: 2022/04/18 21:28:25 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (err_argnum());
	while (argv[i])
	{
		if (!ft_isnum(argv[i]) || ft_atoi(argv[i]) < 1)
			return (err_invalid_input());
		i++;
	}
	return (1);
}

int	set_args(t_root *root, int argc, char **argv)
{
	if (is_valid_args(argc, argv) == 0)
		return (1);
	memset(root, 0, sizeof(t_root));
	root->num_of_philo = ft_atoi(argv[1]);
	root->time_to_die = (time_t) ft_atoi(argv[2]);
	root->time_to_eat = (time_t) ft_atoi(argv[3]);
	root->time_to_sleep = (time_t) ft_atoi(argv[4]);
	if (argc == 6)
		root->limit_to_eat = ft_atoi(argv[5]);
	return (0);
}

int	init_table(t_root *root)
{
	int	i;

	if (ft_malloc((void **) &(root->philos), root->num_of_philo * sizeof(t_philo)))
		return (1);
	if (ft_malloc((void **) &(root->forks), root->num_of_philo * sizeof(sem_t)))
		return (1);
	i = 0;
	while (i < root->num_of_philo)
	{
		root->philos[i].id = i + 1;
		root->philos[i].root = root;
	}
}