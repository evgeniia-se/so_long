/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:08:08 by esergeev          #+#    #+#             */
/*   Updated: 2025/09/23 20:08:10 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 65307)
		window_close(data);
	if (keycode == 119)
		data->game.key_w = 1;
	if (keycode == 97)
		data->game.key_a = 1;
	if (keycode == 115)
		data->game.key_s = 1;
	if (keycode == 100)
		data->game.key_d = 1;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 119)
		data->game.key_w = 0;
	if (keycode == 97)
		data->game.key_a = 0;
	if (keycode == 115)
		data->game.key_s = 0;
	if (keycode == 100)
		data->game.key_d = 0;
	return (0);
}

int	game_loop(void *param)
{
	t_data		*all;
	static int	frame_count;

	all = (t_data *)param;
	frame_count++;
	if (frame_count >= 17660)
	{
		if (all->game.key_w)
			mouve_player(all, -1, 0);
		else if (all->game.key_a)
			mouve_player(all, 0, -1);
		else if (all->game.key_s)
			mouve_player(all, 1, 0);
		else if (all->game.key_d)
			mouve_player(all, 0, 1);
		frame_count = 0;
	}
	return (0);
}

int	expose_hook(void *param)
{
	t_data	*all;

	all = (t_data *)param;
	render_map(all->map, all);
	return (0);
}

void	*work_window(int width, int height, t_data *all)
{
	all->mlx_ptr = mlx_init();
	if (!all->mlx_ptr)
		return (NULL);
	all->win_ptr = mlx_new_window(all->mlx_ptr, width * 32,
			height * 32, "so_long");
	if (!all->win_ptr)
		return (NULL);
	load_textures(all->mlx_ptr, &all->texture);
	render_map(all->map, all);
	mlx_hook(all->win_ptr, 17, 0L, close_win, all);
	mlx_hook(all->win_ptr, 2, 1L, key_press, all);
	mlx_hook(all->win_ptr, 3, 2L, key_release, all);
	mlx_loop_hook(all->mlx_ptr, game_loop, all);
	mlx_expose_hook(all->win_ptr, expose_hook, all);
	return (all->mlx_ptr);
}
