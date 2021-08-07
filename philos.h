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

typedef struct s_data
{
	int				count_name;
	int				time;
	int				status;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}t_data;

typedef struct s_kant
{
	int				s_number;
	int				s_time_dead;
	int				s_time_eat;
	int				s_time_sleep;
	int				s_eat_number;
	int				s_dead_is_come;
	int				s_count_eat;
	int				time;
	int				i;
	t_data			*data;
}t_kant;

int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
long	ft_get_time(void);
void	ft_usleep(int ms);

#endif
