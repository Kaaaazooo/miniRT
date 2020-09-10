/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:56:23 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:37:35 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vectors.h"
# include "mini_rt.h"
# include "objects.h"

typedef struct	s_ray
{
	t_vec	pos;
	t_vec	dir;
}				t_ray;

typedef struct	s_camera
{
	t_vec					llc;
	t_vec					ho;
	t_vec					ve;
	t_vec					pos;
	t_vec					vec;
	t_vec					vup;
	float					fov;
	struct s_camera			*next;
}				t_cam;

t_ray			*new_ray(t_ray *r, t_vec org, t_vec dir);
t_ray			*get_ray(t_ray *r, t_cam *cam, float u, float v);
t_vec			*pt_at_param(t_vec *dest, t_ray *r, float t);
t_cam			*init_cam(t_cam *cam, float aspect);

#endif
