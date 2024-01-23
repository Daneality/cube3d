/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsas <dsas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:10 by dsas              #+#    #+#             */
/*   Updated: 2024/01/23 18:44:58 by dsas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	key_up(t_game *game)
{
	t_raycast	*rays;

	rays = game->rays;
	if (game->map[(int)rays->pos_y][(int)(rays->pos_x + \
								rays->dir_x * game->movespeed)] == '0')
		rays->pos_x += rays->dir_x * game->movespeed;
	if (game->map[(int)(rays->pos_y + rays->dir_y * \
							game->movespeed)][(int)rays->pos_x] == '0')
		rays->pos_y += rays->dir_y * game->movespeed;
}

void	key_down(t_game *game)
{
	t_raycast	*rays;

	rays = game->rays;
	if (game->map[(int)rays->pos_y][(int)(rays->pos_x - \
								rays->dir_x * game->movespeed)] == '0')
		rays->pos_x -= rays->dir_x * game->movespeed;
	if (game->map[(int)(rays->pos_y - rays->dir_y * \
							game->movespeed)][(int)rays->pos_x] == '0')
		rays->pos_y -= rays->dir_y * game->movespeed;
}

void	key_a(t_game *game)
{
	t_raycast	*rays;

	rays = game->rays;
	if (game->map[(int)rays->pos_y][(int)(rays->pos_x - \
						rays->dir_y * game->movespeed)] == '0')
		rays->pos_x -= rays->dir_y * game->movespeed;
	if (game->map[(int)(rays->pos_y + rays->dir_x * \
				game->movespeed)][(int)rays->pos_x] == '0')
		rays->pos_y += rays->dir_x * game->movespeed;
}

void	key_d(t_game *game)
{
	t_raycast	*rays;

	rays = game->rays;
	if (game->map[(int)rays->pos_y][(int)(rays->pos_x + \
					rays->dir_y * game->movespeed)] == '0')
		rays->pos_x += rays->dir_y * game->movespeed;
	if (game->map[(int)(rays->pos_y - rays->dir_x * \
				game->movespeed)][(int)rays->pos_x] == '0')
		rays->pos_y -= rays->dir_x * game->movespeed;
}
