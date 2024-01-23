/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsas <dsas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:45:30 by dsas              #+#    #+#             */
/*   Updated: 2024/01/23 18:45:02 by dsas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_hook(t_game *d)
{
	if (d->key_w)
		key_up(d);
	if (d->key_s)
		key_down(d);
	if (d->key_right)
		rotate(1, d, d->rotspeed);
	if (d->key_left)
		rotate(-1, d, d->rotspeed);
	if (d->key_a)
		key_a(d);
	if (d->key_d)
		key_d(d);
	if (d->key_esc)
		close_game(d);
	return (0);
}

int	key_release(int key, t_game *d)
{
	if (key == W_KEY)
		d->key_w = 0;
	if (key == S_KEY)
		d->key_s = 0;
	if (key == A_KEY)
		d->key_a = 0;
	if (key == D_KEY)
		d->key_d = 0;
	if (key == KEY_ARR_RIGHT)
		d->key_right = 0;
	if (key == KEY_ARR_LEFT)
		d->key_left = 0;
	if (key == ESC_KEY)
		d->key_esc = 0;
	if (key == KEY_SHIFT_LEFT)
		d->movespeed /= 1.5;
	return (0);
}

int	key_press(int key, t_game *d)
{
	if (key == W_KEY)
		d->key_w = 1;
	if (key == S_KEY)
		d->key_s = 1;
	if (key == A_KEY)
		d->key_a = 1;
	if (key == D_KEY)
		d->key_d = 1;
	if (key == KEY_ARR_RIGHT)
		d->key_right = 1;
	if (key == KEY_ARR_LEFT)
		d->key_left = 1;
	if (key == ESC_KEY)
		d->key_esc = 1;
	if (key == KEY_SHIFT_LEFT)
		d->movespeed *= 1.5;
	return (0);
}
