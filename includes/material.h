/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:26:54 by sabrugie          #+#    #+#             */
/*   Updated: 2020/09/30 18:23:10 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "mini_rt.h"
# include "objects.h"
# include "ray.h"
# include "vectors.h"

# define LA 1
# define ME 2

struct s_hit_rec;
struct s_xor;

typedef struct	s_mat
{
	t_ray				r;
	t_ray				scattered;
	t_vec				attenuation;
	float				fuzz;
	char				type;
}				t_mat;

typedef struct	s_phong
{
	t_vec				ambient;
	t_vec				diffuse;
	t_vec				specular;
}				t_phong;

t_vec			*reflect(t_vec *dest, t_vec *v1, t_vec *v2);
t_bool			scatter_metal(t_ray *ray_in, struct s_hit_rec *rec,
												struct s_xor *seed);
t_bool			scatter_lambert(struct s_hit_rec *rec, struct s_xor *seed);
t_bool			scatter(struct s_hit_rec *rec, struct s_xor *seed,
														t_ray *ray_in);

#endif
