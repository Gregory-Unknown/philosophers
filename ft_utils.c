/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esobchak <esobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 14:17:18 by esobchak          #+#    #+#             */
/*   Updated: 2021/08/16 15:02:26 by esobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	ft_init_dekart_utils(t_kant *kant, int i)
{
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
	if (pthread_create(&kant->dekart[i].thread, NULL,
			ft_mood, (void *)&kant->dekart[i]))
	{
		printf("main error: can't create thread\n");
		return (1);
	}
	return (0);
}

int	ft_init_dekart(t_kant *kant)
{
	int	i;

	kant->dekart = (t_dekart *)malloc(sizeof(t_dekart) * (kant->s_number + 1));
	i = 0;
	kant->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* kant->s_number);
	if (!kant->fork)
		return (1);
	kant->s_time = ft_get_time();
	while (i < kant->s_number)
	{
		kant->dekart[i].count_name = i + 1;
		kant->dekart[i].i = i;
		kant->dekart[i].status = 1;
		kant->dekart[i].right = (i + 1) % kant->s_number;
		kant->dekart[i].left = i;
		kant->dekart[i].kant = kant;
		kant->dekart[i].time = ft_get_time();
		if (ft_init_dekart_utils(kant, i))
			return (1);
		i++;
	}
	return (0);
}

unsigned long	ft_get_time(void)
{
	struct timeval			time;
	unsigned long			res;

	gettimeofday(&time, NULL);
	res = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (res);
}

void	ft_usleep(int ms)
{
	unsigned long	time;

	time = ft_get_time() + ms;
	while (((unsigned long)ft_get_time() < time))
		usleep(500);
}

void	ft_print_message(t_dekart *dekart, int status)
{
	unsigned long	time;
	unsigned long	tmp;

	tmp = ft_get_time();
	time = (tmp - dekart->kant->s_time);
	pthread_mutex_lock(&dekart->print);
	if ((status == 1 || status == 2))
		printf("%ld %d has taken a fork\n", time, dekart->count_name);
	else if (status == 3)
		printf("%ld %d is eating\n", time, dekart->count_name);
	else if (status == 4)
		printf("%ld %d is sleeping\n", time, dekart->count_name);
	else if (status == 5)
		printf("%ld %d is thinking\n", time, dekart->count_name);
	else if (status == 6)
		printf("%ld %d is died\n", time, dekart->count_name);
	pthread_mutex_unlock(&dekart->print);
}
