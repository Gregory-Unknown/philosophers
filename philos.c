/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esobchak <esobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 14:21:12 by esobchak          #+#    #+#             */
/*   Updated: 2021/08/16 14:32:56 by esobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	ft_sleep(t_dekart	*dekart)
{
	ft_print_message(dekart, 4);
	ft_usleep(dekart->kant->s_time_sleep);
}

static void	ft_eat(t_dekart	*dekart)
{
	pthread_mutex_lock(&dekart->kant->fork[dekart->right]);
	ft_print_message(dekart, 1);
	pthread_mutex_lock(&dekart->kant->fork[dekart->left]);
	ft_print_message(dekart, 2);
	dekart->time = ft_get_time();
	ft_print_message(dekart, 3);
	if (dekart->kant->s_count != -1)
		dekart->kant->s_count--;
	ft_usleep(dekart->kant->s_time_eat);
	pthread_mutex_unlock(&dekart->kant->fork[dekart->left]);
	pthread_mutex_unlock(&dekart->kant->fork[dekart->right]);
}

void	*ft_mood(void *e_dekart)
{
	t_dekart	*dekart;

	dekart = (t_dekart *)e_dekart;
	if (dekart->count_name % 2 == 0)
		ft_usleep(dekart->kant->s_time_eat / 2);
	dekart->time = ft_get_time();
	while (dekart->kant->s_count)
	{
		ft_eat(dekart);
		ft_sleep(dekart);
		ft_print_message(dekart, 5);
	}
	return (0);
}

int	ft_loop(t_kant *kant)
{
	int				i;
	unsigned long	tmp;

	while (1)
	{
		i = 0;
		while (i < kant->s_number)
		{
			if (!kant->s_count)
			{
				ft_over(kant);
				return (0);
			}
			tmp = ft_get_time() - kant->dekart[i].time;
			if ((int)tmp >= (int)kant->s_time_dead)
			{
				ft_dead(&kant->dekart[i], kant);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void	ft_free(t_kant *kant)
{
	int	i;

	i = 0;
	while (i < kant->s_number)
	{
		free(&kant->fork[i]);
		i++;
	}
}
