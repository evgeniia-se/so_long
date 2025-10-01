/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaming.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:10:52 by esergeev          #+#    #+#             */
/*   Updated: 2025/09/23 20:10:55 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	check_collect_and_exit(t_data *all)
{
	if (all->game.last_tile == 'C')
	{
		all->game.collect++;
		if (all->game.collect == all->game.collect_total)
		{
			all->game.exit_flag = 1;
		}
		all->game.last_tile = '0';
	}
	if (all->game.last_tile == 'E' && all->game.exit_flag == 1)
	{
		ft_printf("You are win! you ate all mouses :)\n");
		ft_printf("Total mouves: %d\n", all->game.mouves);
		cleanup_game(all);
		exit(0);
	}
}

void	mouve_player(t_data *all, int dy, int dx)
{
	int	old_x;
	int	old_y;
	int	new_x;
	int	new_y;

	old_x = all->game.player_pos.x;
	old_y = all->game.player_pos.y;
	new_x = old_x + dx;
	new_y = old_y + dy;
	if (new_y < 0 || new_y >= all->game.height || new_x < 0
		|| new_x >= all->game.width)
		return ;
	if (all->map[new_y][new_x] != '1')
	{
		all->map[old_y][old_x] = all->game.last_tile;
		all->game.last_tile = all->map[new_y][new_x];
		all->game.player_pos.x = new_x;
		all->game.player_pos.y = new_y;
		all->map[new_y][new_x] = 'P';
		all->game.mouves++;
		ft_printf("Moves: %d\n", all->game.mouves);
		check_collect_and_exit(all);
		render_map(all->map, all);
	}
}

void	collectible(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	game->collect_total = 0;
	game->collect = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
			{
				game->collect_total++;
			}
			j++;
		}
		i++;
	}
}

void	position(t_data *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'P')
			{
				all->game.player_pos.x = j;
				all->game.player_pos.y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	gaming(t_data *all)
{
	all->game.mouves = 0;
	all->game.dy = 0;
	all->game.dx = 0;
	all->game.exit_flag = 0;
	all->game.last_tile = '0';
	all->game.key_w = 0;
	all->game.key_a = 0;
	all->game.key_s = 0;
	all->game.key_d = 0;
}
