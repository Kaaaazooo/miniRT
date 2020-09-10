/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:39:13 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:54:03 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	*alloc_vec(float x, float y, float z)
{
	t_vec	*vec;

	if (!(vec = malloc(sizeof(vec))))
		ft_handle_error(ALLOC_FAIL);
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vec	*new_vec(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

int	v_rgb(t_vec *color)
{
	int	rgb;

	rgb = 0;
	if (color->x > 1 || color->x < 0)
		color->x = color->x > 1 ? 1 : -1;
	if (color->y > 1 || color->y < 0)
		color->y = color->y > 1 ? 1 : -1;
	if (color->z > 1 || color->z < 0)
		color->z = color->z > 1 ? 1 : -1;
	rgb |= (int)(255.99 * color->x) << 16;
	rgb |= (int)(255.99 * color->y) << 8;
	rgb |= (int)(255.99 * color->z);
	return(rgb);
}
