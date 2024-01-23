/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsas <dsas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:03:32 by dsas              #+#    #+#             */
/*   Updated: 2024/01/23 18:45:24 by dsas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	floor_ceiling(t_game *game)
{
	int		y;
	int		x;
	int		w;

	y = -1;
	while (++y < game->screen_width)
	{
		x = -1;
		while (++x < game->screen_height / 2)
			my_mlx_pixel_put(game, y, game->screen_height \
									- x - 1, game->floor_color);
		w = -1;
		while (++w < game->screen_height / 2)
			my_mlx_pixel_put(game, y, w, game->ceiling_color);
	}
}

static void	calc_draw(t_game *game)
{
	t_raycast	*r;

	r = game->rays;
	r->line_height = (int)(game->screen_height / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + game->screen_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + game->screen_height / 2;
	if (r->draw_end >= game->screen_height)
		r->draw_end = game->screen_height - 1;
	r->texnum = game->map[r->map_y][r->map_x] - 48;
	if (r->side % 2 == 0)
		r->wallx = r->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wallx = r->pos_x + r->perp_wall_dist * r->ray_dir_x;
	r->wallx -= floor((r->wallx));
	r->texx = (int)(r->wallx * (double)game->tex_width);
}

static void	draw_walls(t_game *game, int i)
{
	int			j;
	t_raycast	*rays;

	rays = game->rays;
	if (rays->side % 2 == 0 && rays->ray_dir_x > 0)
		rays->texx = game->tex_width - rays->texx - 1;
	if (rays->side % 2 == 1 && rays->ray_dir_y < 0)
		rays->texx = game->tex_width - rays->texx - 1;
	rays->step = 1.0 * game->tex_height / rays->line_height;
	rays->texpos = (rays->draw_start - game->screen_height / 2 + \
								rays->line_height / 2) * rays->step;
	j = rays->draw_start;
	while (j < rays->draw_end)
	{
		rays->texy = (int)rays->texpos & (game->tex_height - 1);
		rays->texpos += rays->step;
		rays->colr = game->texture[rays->texnum + rays->side - 1] \
		[game->tex_height * rays->texy + rays->texx];
		my_mlx_pixel_put(game, i, j, rays->colr);
		j++;
	}
}

void	wall_casting(t_game *game)
{
	int			i;
	t_raycast	*rays;

	rays = game->rays;
	i = 0;
	while (i < game->screen_width)
	{
		init_wall_casting(game, i);
		calc_side_dist(game);
		calc_hit(game);
		calc_draw(game);
		draw_walls(game, i);
		i++;
	}
}

int	draw(t_game *game)
{
	t_raycast	*rays;

	game->rays->time = ft_get_ticks();
	rays = game->rays;
	if (rays->img)
		mlx_destroy_image(game->mlx, rays->img);
	rays->img = mlx_new_image(game->mlx, game->screen_width, \
													game->screen_height);
	rays->img_addr = mlx_get_data_addr(rays->img, &rays->bits_per_pixel, \
		&rays->line_length, &rays->endian);
	floor_ceiling(game);
	wall_casting(game);
	mlx_put_image_to_window(game->mlx, game->win, rays->img, 0, 0);
	key_hook(game);
	return (0);
}
