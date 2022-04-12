/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:48:11 by dha               #+#    #+#             */
/*   Updated: 2022/04/11 16:26:03 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
