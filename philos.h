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
	int				time;
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
	int				s_number;
	int				s_time_dead;
	int				s_time_eat;
	int				s_time_sleep;
	int				s_eat_number;
	int				s_dead_is_come;
	int				s_count_eat;
	int				s_think;
	long			s_time;
	int				*array_fork;
	pthread_mutex_t	*fork;
	t_dekart		*dekart;
}t_kant;

int		ft_strlen_int(int *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
long	ft_get_time(void);
void	ft_usleep(int ms);
void	ft_print_message(t_dekart *dekart, int status);

#endif
