/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orbiay <orbiay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 09:50:51 by otoufah           #+#    #+#             */
/*   Updated: 2022/10/09 15:47:43 by orbiay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_filling(t_mlx	*wind)
{
	int		j;
	int		i;

	i = 0;
	while (wind->map[i])
	{
		j = 0;
		while (wind->map[i][j])
		{
			if (wind->map[i][j] == '1')
			{
				mlx_put_image_to_window(wind->mlx, wind->window, wind->xpm_wall, j * 64, i * 64);
			}
			else if (wind->map[i][j] == '0')
				mlx_put_image_to_window(wind->mlx, wind->window, wind->xpm_empty, j * 64, i * 64);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(wind->mlx, wind->window, wind->xpm_player, wind->x_player, wind->y_player);
	projecting_rays(wind);
}
