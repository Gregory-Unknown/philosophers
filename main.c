# include "philos.h"

int	ft_arguments(int argc, char **argv, t_kant *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	data->s_number = ft_atoi(argv[1]);
	if (data->s_number < 1 || data->s_number > 200)
			return(1);
	data->s_time_dead = ft_atoi(argv[2]);
	if (data->s_time_dead < 60)
		return (1);
	data->s_time_eat = ft_atoi(argv[3]);
	if (data->s_time_eat < 60)
			return (1);
	data->s_time_sleep = ft_atoi(argv[4]);
	if (data->s_time_sleep < 60)
		return (1);
	if (argc == 6)
	{
		data->s_eat_number = ft_atoi(argv[5]);
		if (data->s_eat_number < 1)
			return (1);
	}
	data->s_dead_is_come = 1;
	return (0);
}

int	ft_thinking(t_dekart	*dekart)
{
	ft_print_message(dekart, 5);
	return (0);
}

int	ft_sleep(t_dekart	*dekart)
{
	ft_print_message(dekart, 4);
	dekart->time = ft_get_time();
	while (((long)ft_get_time() - dekart->time <= dekart->kant->s_time_sleep) && dekart->kant->s_dead_is_come)
		usleep(1000);
	// dekart->time = ft_get_time();
	// ft_usleep(dekart->kant->s_time_sleep);
	return (0);
}

void	ft_eat(t_dekart	*dekart)
{

	pthread_mutex_lock(&dekart->kant->fork[dekart->right]);
	pthread_mutex_lock(&dekart->kant->fork[dekart->left]);
	pthread_mutex_lock(&dekart->eating);
	ft_print_message(dekart, 1);
	ft_print_message(dekart, 2);
	ft_print_message(dekart, 3);
	dekart->time = ft_get_time();
	while (((long)ft_get_time() - dekart->time <= dekart->kant->s_time_eat) && dekart->kant->s_dead_is_come)
		usleep(1000);
	pthread_mutex_unlock(&dekart->eating);
	pthread_mutex_unlock(&dekart->kant->fork[dekart->left]);
	pthread_mutex_unlock(&dekart->kant->fork[dekart->right]);
}

void	*ft_mood(void *e_dekart)
{
	t_dekart	*dekart;


	dekart = (t_dekart *)e_dekart;
	if (dekart->count_name % 2 == 0)
		ft_usleep(1000 * dekart->kant->s_time_eat);
	while (dekart->kant->s_dead_is_come)
	{
		if (!dekart->kant->s_dead_is_come)
			break ;
		ft_eat(dekart);
		if (!dekart->kant->s_dead_is_come)
			break ;
		ft_sleep(dekart);
		if (!dekart->kant->s_dead_is_come)
			break ;
		ft_thinking(dekart);
		if (!dekart->kant->s_dead_is_come)
			break ;
	}
	return (0);
}

void	*ft_blood(void *e_dekart)
{
	t_dekart	*dekart;

	dekart = e_dekart;
	while (dekart->kant->s_dead_is_come)
	{
		pthread_mutex_lock(&dekart->eating);
		if (ft_get_time() - dekart->time >= dekart->kant->s_time_dead)
		{
			ft_print_message(dekart, 6);
			dekart->kant->s_dead_is_come = 0;
			dekart->status = 0;
			pthread_mutex_unlock(&dekart->eating);
			return (0);
		}
		pthread_mutex_unlock(&dekart->eating);
		usleep(100);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_kant		*kant;
	pthread_t	death;
	int			i;

	kant = (t_kant *)malloc(sizeof(t_kant));
	memset(kant, 0, sizeof(t_kant));
	if (!kant || ft_arguments(argc, argv, kant))
	{
		printf("Error parametr\n");
		return (1);
	}
	kant->dekart = (t_dekart *)malloc(sizeof(t_dekart) * (kant->s_number + 1));
	memset(kant->dekart, 0, sizeof(t_dekart));
	i = 0;
	kant->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * kant->s_number);
	if (!kant->fork)
		return (1);
	memset(kant->fork, 0, sizeof(pthread_mutex_t));
	while (i < kant->s_number)
	{
		kant->dekart[i].count_name = i + 1;
		kant->dekart[i].i = i;
		kant->dekart[i].status = 1;
		kant->dekart[i].right = (i + 1) % kant->s_number;
		kant->dekart[i].left = i;
		kant->dekart[i].kant = kant;

		if (pthread_mutex_init(&(kant->dekart[i].eating), NULL))
		{
			printf("main error: can't init mutex\n");
			return (1);
		}
		if (pthread_mutex_init(&(kant->fork[i]), NULL))
		{
			printf("main error: can't init mutex\n");
			return (1);
		}
		if (pthread_mutex_init(&(kant->dekart[i].print), NULL))
		{
			printf("main error: can't init mutex\n");
			return (1);
		}
		i++;
	}

	i = 0;
	kant->s_time = ft_get_time();
	while (i < kant->s_number)
	{
		kant->dekart[i].time = ft_get_time();
		//printf("AAAAA\n");
		if (pthread_create(&death, NULL, ft_mood, (void *)&kant->dekart[i]))
		{
			printf("main error: can't create thread\n");
			return (1);
		}
		pthread_detach(death);
		if (pthread_create(&kant->dekart[i].thread, NULL, ft_blood, (void *)&kant->dekart[i]))
		{
			printf("main error: can't create thread\n");
			return (1);
		}
		//pthread_detach(kant->dekart[i].thread);
		i++;
	}
	i = 0;
	while (i < kant->s_number)
	{
		if (pthread_join(kant->dekart[i].thread, NULL))
		{
			printf("main error: can't stop thread\n");
			return (1);
		}
		i++;
	}
	printf("GOOD!\n");

	return(0);
}
