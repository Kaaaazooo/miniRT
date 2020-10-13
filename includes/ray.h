/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:56:23 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 19:13:04 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vectors.h"
# include "mini_rt.h"
# include "objects.h"

struct s_mlx;
struct s_coordinates;
struct s_configuration;

typedef struct	s_ray
{
	t_vec	pos;
	t_vec	dir;
}				t_ray;

typedef struct	s_hit
{
	struct s_ray			ray;
	float					t_min;
	float					t_max;
}				t_hit;

typedef struct	s_hit_rec
{
	float					t;
	t_vec					p;
	t_vec					normal;
	struct s_mat			*mat_ptr;
}				t_hit_rec;

typedef struct	s_camera
{
	t_vec					llc;
	t_vec					ho;
	t_vec					ve;
	t_vec					pos;
	t_vec					vec;
	t_vec					vup;
	float					fov;
	void					*img_ptr;
	void					*mlx_ptr;
	void					*win_ptr;
	int						bpp;
	int						line;
	int						endian;
	char					*data;
	struct s_camera			*next;
}				t_cam;

t_ray			*new_ray(t_ray *r, t_vec org, t_vec dir);
t_ray			*get_ray(t_ray *r, t_cam *cam, float u, float v);
t_vec			*pt_at_param(t_vec *dest, t_ray *r, float t);
t_cam			*init_cam(struct s_configuration *conf, struct s_mlx *mlx,
									struct s_coordinates *res, float aspect);

#endif
