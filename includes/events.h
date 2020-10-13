/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 11:18:45 by sabrugie          #+#    #+#             */
/*   Updated: 2020/10/13 18:10:19 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "mini_rt.h"

void	handle_events(t_conf *conf);
void	free_objs(t_obj *obj);
void	free_all(t_conf *conf);

#endif
