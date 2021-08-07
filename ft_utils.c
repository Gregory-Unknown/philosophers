# include "philos.h"

static const char	*ft_is_pass(const char *str)
{
	while (*str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r' || *str == 32)
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	res = 0;
	sign = 1;
	str = ft_is_pass(str);
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str > 47 && *str < 58)
	{
		res = 10 * res + (*str - 48);
		str++;
	}
	return (res * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000);
}
void	ft_usleep(int ms)
{
	long	time;

	time = ft_get_time() + ms;
	while (((long)ft_get_time() < time))
		usleep(500);
}

void	ft_print(t_kant *kant)
{
	printf("%d", kant->data->count_name);
	if (kant->data->status == 1 || kant->data->status == 2)
		printf(" : has taken a fork\n");
	else if (kant->data->status == 3)
		printf(" : is eating\n");
	else if (kant->data->status == 4)
		printf(" : is sleeping\n");
	else if (kant->data->status == 5)
		printf(" : is thinking\n");
	else if (kant->data->status == 6)
		printf(" : is died\n");
}

void	ft_print_message(t_kant *kant)
{
	int	time;

	time = ft_get_time();
	pthread_mutex_lock(&kant->data->print);
	if (!kant->s_dead_is_come)
	{
		pthread_mutex_unlock(&kant->data->print);
		return ;
	}
	if (kant->s_eat_number && kant->s_eat_number == kant->s_count_eat)
		printf("all philosophers eat at least %d\n", kant->s_count_eat);
	else
		ft_print(kant);
	pthread_mutex_unlock(&kant->data->print);
}
