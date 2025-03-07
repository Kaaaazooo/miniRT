/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:06:09 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 19:24:46 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	skip_spaces(char **str)
{
	while (**str && (**str == ' ' || (**str >= 9 && **str <= 13)))
		(*str) += 1;
}

t_vec	skip_atov(char **str, t_conf *conf, char *type)
{
	t_vec	vec;

	vec.x = skip_atof(str, conf, type);
	if (**str != ',')
	{
		write(1, type, ft_strlen(type));
		ft_handle_error(" : wrong input\n", conf);
	}
	++(*str);
	vec.y = skip_atof(str, conf, type);
	if (**str != ',')
	{
		write(1, type, ft_strlen(type));
		ft_handle_error(" : wrong input\n", conf);
	}
	++(*str);
	vec.z = skip_atof(str, conf, type);
	if (**str && **str != ' ' && (**str < 9 || **str > 13))
	{
		write(1, type, ft_strlen(type));
		ft_handle_error(" : wrong input\n", conf);
	}
	return (vec);
}

int		skip_atoi(char **str, t_conf *conf, char *type)
{
	int		nb;
	int		sign;

	nb = 0;
	sign = 1;
	skip_spaces(str);
	while (**str == '-' || **str == '+')
	{
		sign *= -1;
		(*str) += 1;
	}
	if (!ft_isdigit(**str))
	{
		write(1, type, ft_strlen(type));
		ft_handle_error(" : wrong input\n", conf);
	}
	while (ft_isdigit(**str))
		nb = nb * 10 + *((*str)++) - '0';
	return (nb * sign);
}

float	skip_atof(char **str, t_conf *conf, char *type)
{
	float	nb;
	float	dec;
	int		sign;

	nb = 0;
	sign = 1;
	skip_spaces(str);
	while (**str == '-' || **str == '+')
	{
		sign *= -1;
		(*str) += 1;
	}
	if (!ft_isdigit(**str) && write(1, type, ft_strlen(type)))
		ft_handle_error(" : wrong input\n", conf);
	while (ft_isdigit(**str))
		nb = nb * 10 + (float)(*((*str)++) - '0');
	if (**str == '.')
		(*str) += 1;
	dec = 0.1;
	while (ft_isdigit(**str))
	{
		nb += dec * (float)(*((*str)++) - '0');
		dec *= 0.1;
	}
	return (nb * sign);
}
