/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 09:07:06 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/10 12:41:18 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "mini_rt.h"
# include "utils.h"
# include "material.h"
# include "ray.h"

# define SP 1
# define PL 2
# define SQ 4
# define CY 8
# define TR 16
# define R 32
# define A 64
# define C 128
# define L 256

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

typedef struct	s_ambient_light
{
	float			amb_rat;
	t_vec			amb_rgb;
}				t_amb_l;

typedef struct	s_sphere
{
	t_vec					pos;
	float					radius;
	struct s_mat			*mat_ptr;
}				t_sp;

typedef struct	s_light
{
	t_vec					pos;
	float					ratio;
	t_vec					rgb;
	struct s_light			*next;
}				t_light;

typedef struct	s_plane
{
	t_vec					pos;
	t_vec					dir;
	t_vec					rgb;
	struct s_mat			*mat_ptr;
}				t_pl;

typedef struct	s_configuration
{
	t_coord			*res;
	t_amb_l			*amb_l;
	struct s_camera	*cam;
	struct s_light	*lights;
	struct s_obj_ls	*objs;
	t_xor			seed;
}				t_conf;

typedef t_bool	(*t_func)(struct s_sphere *sp, t_hit *hit);

typedef struct	s_obj_ls
{
	char					type;
	void					*obj;
	struct s_obj_ls			*next;
	t_func					f;
}				t_obj;

t_bool			hit_any(t_obj *objs, t_hit *hit, t_hit_rec *rec);
t_bool			hit_sphere(t_sp *sp, t_hit *hit, t_hit_rec *rec);
t_obj			*new_obj(char type, void *obj, t_obj *next, t_func f);
t_sp			*new_sphere(t_sp *dest, t_vec *v1, float radius);
t_vec			*rand_unit_sp(t_vec *dest, t_xor *seed);
#endif
