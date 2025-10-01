/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 21:57:20 by esergeev          #+#    #+#             */
/*   Updated: 2025/10/01 21:57:23 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_type_extension(char *s)
{
	int		len;
	char	*ext;

	len = ft_strlen(s);
	if (len < 5)
	{
		ft_printf("Invalid file name\n");
		return (0);
	}
	ext = s + len - 4;
	if (!ft_strncmp(ext, ".ber", 4))
		return (1);
	return (0);
}

int	is_rectangular(char **map)
{
	int	row_len;
	int	i;
	int	j;

	row_len = 0;
	i = 0;
	while (map[0][row_len])
		row_len++;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j != row_len)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf("Usage: %s map.ber\n", av[0]);
		return (0);
	}
	if (!valid_type_extension(av[1]))
	{
		ft_printf("Valid extension only .ber\n");
		return (0);
	}
	return (1);
}
