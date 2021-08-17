/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esobchak <esobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 14:20:39 by esobchak          #+#    #+#             */
/*   Updated: 2021/08/16 14:33:55 by esobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <ctype.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_kant	t_kant;

typedef struct s_dekart
{
	int				i;
	int				fork_count;
	int				count;
	int				count_name;
	unsigned long	time;
	int				status;
	int				left;
	int				right;
	pthread_mutex_t	eating;
	pthread_mutex_t	print;
	pthread_t		thread;
	t_kant			*kant;
}t_dekart;

typedef struct s_kant
{
	int					s_number;
	unsigned long		s_time_dead;
	int					s_time_eat;
	int					s_time_sleep;
	int					s_eat_number;
	int					s_dead_is_come;
	int					s_count_eat;
	int					s_think;
	unsigned long		s_time;
	int					s_count;
	int					s_flag;
	pthread_mutex_t		*fork;
	t_dekart			*dekart;
}t_kant;

int				ft_strlen(int *s);
int				ft_strcmp(char *s1, char *s2);
int				ft_atoi(const char *str);
unsigned long	ft_get_time(void);
void			ft_usleep(int ms);
void			ft_print_message(t_dekart *dekart, int status);
void			*ft_mood(void *e_dekart);
int				ft_loop(t_kant *kant);
void			ft_dead(t_dekart *dekart, t_kant *kant);
void			ft_over(t_kant *kant);
int				ft_arguments(int argc, char **argv, t_kant *data);
void			ft_free(t_kant *kant);
int				ft_init_dekart(t_kant *kant);

#endif
