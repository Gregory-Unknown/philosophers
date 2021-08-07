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
	data->time = 0;
	return (0);
}

// void	ft_eat(t_kant	*kant)
// {
// 	int	i;

// 	i = 0;
// 	if (kant->s_dead_is_come)
// 	{
// 		i = kant->i;
// 		if (i + 1 == kant->s_number)
// 			i = 0;
// 		else if (i == 0)
// 			i = kant->s_number - 1;
// 		else
// 			i = kant->i - 1;
// 		pthread_mutex_lock(&kant->data->fork[kant->i]);
// 		if (i > 0)
// 			pthread_mutex_lock(&kant->data->fork[i]);
// 	}
// 	printf("AAAAAA\n");
// 	pthread_mutex_unlock(&kant->data->fork[kant->i]);
// 	if (i > 0)
// 			pthread_mutex_unlock(&kant->data->fork[i]);
// }

void	*ft_mood(void *e_kant)
{
	t_kant	*kant;

	kant = (t_kant *)e_kant;
	// while (kant->s_dead_is_come)
	// {
	// 	//printf("AAAAAA\n");
	// 	//ft_eat(kant);
	// 	// ft_sleep(kant);
	// 	// ft_think(kant);
	// }
	return (0);
}

int	main(int argc, char **argv)
{
	t_kant	*kant;
	int		i;

	kant = (t_kant *)malloc(sizeof(t_kant));
	memset(kant, 0, sizeof(t_kant));
	if (!kant || ft_arguments(argc, argv, kant))
	{
		printf("Error parametr\n");
		return (1);
	}
	kant->data = (t_data *)malloc(sizeof(t_data) * kant->s_number);
	if (!kant->data)
		return (1);
	kant->data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * kant->s_number);
	if (!kant->data->fork)
		return (1);
	kant->i = 0;
	i = 0;
	while (i < kant->s_number)
	{
		if (pthread_mutex_init(&(kant->data->fork[i]), NULL))
		{
			printf("main error: can'tinit mutex\n");
			return (1);
		}
		printf("BBBBBBB %d\n", i);
		printf("CCCCCCC %d\n", kant->s_number);
		i++;
	}
	i = 0;
	while (i < kant->s_number)
	{
		kant->i = i;
		kant->data->count_name = i + 1;
		if (pthread_create(&(kant->data[kant->i].thread), NULL, ft_mood, (void *)kant))
		{
			printf("main error: can't create thread\n");
			return (1);
		}
		printf("AAAAAA\n");
		i++;
	}
	i = 0;
	while (i < kant->s_number)
	{
		if (pthread_join((kant->data[i].thread), NULL))
		{
			printf("main error: can't stop thread\n");
			return (1);
		}
		i++;
	}
	printf("GOOD\n");
	return(0);
}
