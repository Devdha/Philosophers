/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:12:01 by dha               #+#    #+#             */
/*   Updated: 2022/04/05 22:24:52 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philo
{
	int				pos;
	int				eat;
	int				is_eating;
	time_t			last;
	time_t			next;
	pthread_mutex_t	mutex;
	pthread_mutex_t	m_eat;
}				t_philo;

typedef	struct	s_root
{
	time_t	start;
	int		num_of_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		limit_to_eat;
	t_philo	*philos;
};


// util
void	ft_putstr_fd(char *s, int fd);
// error
int		err_argnum(void);

#endif