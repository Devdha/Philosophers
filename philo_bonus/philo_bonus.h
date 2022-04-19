/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:44:53 by dha               #+#    #+#             */
/*   Updated: 2022/04/19 14:53:49 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

# define SUCCESS 0
# define ERROR 1

typedef struct s_philo
{
	int				id;
	int				total_eat;
	time_t			last;
	pid_t			pid;
	sem_t			sem_philo;
	struct s_root	*root;
}				t_philo;

typedef struct	s_root
{
	time_t	start;
	int		num_of_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		limit_to_eat;
	int		dead;
	t_philo	*philos;
	sem_t	*sem_fork;
	sem_t	*sem_root;
	sem_t	*sem_output;
	sem_t	*sem_end;
}				t_root;

// init
int		set_args(t_root *root, int argc, char **argv);
int		init_table(t_root *root);

char    *ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

#endif