/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:13:10 by esergeev          #+#    #+#             */
/*   Updated: 2025/09/11 14:13:12 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/get_next_line.h"

int	count_map_elements(char **map, int *player_count, int *exit_count,
		int *collectible_count)
{
	int	i;
	int	j;

	i = -1;
	*player_count = 0;
	*exit_count = 0;
	*collectible_count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'P')
				(*player_count)++;
			else if (map[i][j] == 'E')
				(*exit_count)++;
			else if (map[i][j] == 'C')
				(*collectible_count)++;
			else if (map[i][j] != '1' && map[i][j] != '0')
				return (ft_printf("Error: unknown key found in map\n"), 0);

		}
	}
	return (1);
}

int	is_valid(char **map)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	if (!map)
		return (0);
	if (!is_rectangular(map))
		return (ft_printf("Error: map is not rectangular\n"), 0);
	if (!is_enclosed_by_walls(map))
		return (ft_printf("Error: map is not enclosed by walls\n"), 0);
	if (!count_map_elements(map, &player_count, &exit_count,
			&collectible_count))
		return (0);
	if (player_count != 1 || exit_count != 1 || collectible_count < 1)
		return (ft_printf("Error: map must have exactly 1 player, 1 exit, \
			at least 1 collectible\n"), 0);
	return (1);
}

char	**load_and_validate_map(char *filename, t_data *all)
{
	all->map = parse_map(filename, all);
	if (!all->map)
	{
		ft_printf("Error: cannot read map\n");
		return (NULL);
	}
	if (!is_valid(all->map))
	{
		ft_printf("Error: invalid map\n");
		return (NULL);
	}
	return (all->map);
}

char	**map_read(t_data *all, char *s)
{
	int		i;

	i = 0;
	all->map = load_and_validate_map(s, all);
	if (!all->map)
		return (NULL);
	printf("map is here:\n");
	while (all->map[i])
	{
		printf("%s\n", all->map[i]);
		i++;
	}
	return (all->map);
}

int	main(int ac, char **av)
{
	t_data	all;

	if (!check_args(ac, av))
		return (1);
	all.map = map_read(&all, av[1]);
	if (!all.map)
		return (1);
	init_window_sizes(all.map, &all.game.width, &all.game.height);
	position(&all);
	collectible(&all.game, all.map);
	copy_grid(&all);
	all.mlx_ptr = work_window(all.game.width, all.game.height, &all);
	if (!all.mlx_ptr)
		return (1);
	gaming(&all);
	mlx_loop(all.mlx_ptr);
	return (0);
}
