/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esobchak <esobchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 14:24:11 by esobchak          #+#    #+#             */
/*   Updated: 2021/08/17 09:33:07 by esobchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static const char	*ft_is_pass(const char *str)
{
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == 32)
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long		res;

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

static void	ft_arguments_utils(t_kant *data)
{
	data->s_flag = 0;
	if (data->s_number < 2 || (((int)data->s_time_dead - 10)
			<= (data->s_time_eat * 2)))
		data->s_flag = 1;
	data->s_time = 0;
	data->s_dead_is_come = 1;
}

int	ft_arguments(int argc, char **argv, t_kant *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	data->s_number = ft_atoi(argv[1]);
	if (data->s_number < 1 || data->s_number > 200)
		return (1);
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
		if (data->s_eat_number < 0)
			return (1);
		data->s_count = data->s_number * data->s_eat_number;
	}
	else
		data->s_count = -1;
	ft_arguments_utils(data);
	return (0);
}
