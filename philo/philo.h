/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:12:01 by dha               #+#    #+#             */
/*   Updated: 2022/04/17 18:32:12 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define SUCCESS 0
# define ERROR 1

typedef struct s_philo
{
	int				id;
	int				state;
	int				total_eat;
	time_t			last;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct s_root	*root;
}				t_philo;

typedef struct s_root
{
	time_t			start;
	int				num_of_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				limit_to_eat;
	int				dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
}				t_root;

int		set_args(t_root *root, int argc, char **argv);
int		init_table(t_root *root);
// dining
void	*dining(void *ptr);
// scanner
void	*scanner(void *ptr);
int		is_dead(t_philo *philo);
// util
void	ft_putstr_fd(char *s, int fd);
int		ft_isnum(const char *s);
int		ft_atoi(const char *str);
int		ft_malloc(void **ptr, size_t size);
time_t	get_cur_time(void);
void	print_ms(long ms, int id, char *msg);
void	wait_action(time_t begin, time_t limit);
// error
int		err_argnum(void);
int		err_invalid_input(void);
int		err_malloc(void);

#endif
