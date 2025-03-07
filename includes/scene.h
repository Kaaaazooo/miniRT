/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 13:15:40 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/07 15:28:30 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mini_rt.h"

typedef	struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct	s_coordinates
{
	int				x;
	int				y;
}				t_coord;

typedef struct	s_ambient_light
{
	float			ratio;
	t_vec			rgb;
}				t_amb_l;

typedef struct	s_configuration
{
	t_coord			*res;
	t_amb_l			*amb_l;
	t_cam			*cams;
	t_cam			*cam;
	int				i;
	t_light			*lights;
	t_obj			*objs;
	t_mlx			*mlx;
	t_xor			seed;
}				t_conf;

void			render(t_conf *conf);

#endif
