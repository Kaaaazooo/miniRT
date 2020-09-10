/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 13:15:40 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 13:22:58 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mini_rt.h"

typedef struct	s_coordinates
{
	int				x;
	int				y;
}				t_coord;

typedef struct	s_ambient_light
{
	float			amb_rat;
	t_vec			amb_rgb;
}				t_amb_l;

typedef struct	s_configuration
{
	t_coord			*res;
	t_amb_l			*amb_l;
	t_cam			*cam;
	t_light			*lights;
	t_obj			*objs;
	t_xor			seed;
}				t_conf;


#endif
