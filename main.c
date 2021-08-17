/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esobchak <esobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 14:17:13 by esobchak          #+#    #+#             */
/*   Updated: 2021/08/16 14:32:12 by esobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	ft_destroy(t_kant *kant)
{
	int	i;

	i = 0;
	if (!(kant->s_flag))
		pthread_mutex_lock(&kant->dekart[i].print);
	while (i < kant->s_number)
	{
		pthread_mutex_destroy(&kant->fork[i]);
		i++;
	}
}

static void	ft_detach(t_kant *kant)
{
	int	i;

	i = 0;
	while (i < kant->s_number)
	{
		pthread_detach(kant->dekart[i].thread);
		i++;
	}
}

void	ft_over(t_kant *kant)
{
	ft_destroy(kant);
	ft_detach(kant);
	printf("That's enough. Everyone has eaten!\n");
}

void	ft_dead(t_dekart *dekart, t_kant *kant)
{
	ft_destroy(kant);
	ft_detach(kant);
	ft_print_message(dekart, 6);
}

int	main(int argc, char **argv)
{
	t_kant		*kant;

	kant = (t_kant *)malloc(sizeof(t_kant));
	memset(kant, 0, sizeof(t_kant));
	if (!kant || ft_arguments(argc, argv, kant))
	{
		printf("Error parametr\n");
		return (1);
	}
	if (ft_init_dekart(kant))
	{
		printf("Error, bad init\n");
		return (1);
	}
	ft_loop(kant);
	free(kant);
	return (0);
}
