/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:44:53 by dha               #+#    #+#             */
/*   Updated: 2022/04/20 20:02:50 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define SUCCESS 0
# define ERROR 1

# define DIE_MSG 0
# define FORK_MSG 1
# define EAT_MSG 2
# define SLEEP_MSG 3
# define THINK_MSG 4

typedef struct s_philo
{
	int				id;
	int				total_eat;
	int				dead;
	time_t			last;
	pid_t			pid;
	pthread_t		thread;
	sem_t			*sem_philo;
	struct s_root	*root;
}				t_philo;

typedef struct s_root
{
	time_t	start;
	int		num_of_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		limit_to_eat;
	t_philo	*philos;
	sem_t	*sem_fork;
	sem_t	*sem_output;
	sem_t	*sem_done;
	sem_t	*sem_end;
}				t_root;

// init
int		set_args(t_root *root, int argc, char **argv);
int		init_table(t_root *root);

// dining
void	dining(t_philo *philo);

// scanner
void	*scanner(void *ptr);
int		is_dead(t_philo *philo);
void	*done_scanner(void *ptr);

// util
char	*ft_strjoin(char const *s1, char *s2);
char	*ft_itoa(int n);
time_t	get_cur_time(void);
int		ft_atoi(const char *str);
int		ft_isnum(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_malloc(void **ptr, size_t size);
void	wait_action(time_t begin, time_t limit);
void	print_each(t_philo *philo, int idx, time_t cur);
void	kill_until(int i, t_root *root);

// error
int		err_invalid_input(void);
int		err_argnum(void);
int		err_malloc(void);

#endif