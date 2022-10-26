#include "../cub3d.h"

void	projecting_rays(t_mlx *wind)
{
	int		x;
	double	angle;

	x = -1;
	angle = wind->field_of_view - HALF_WALL;
	wind->my_mlx.img = mlx_new_image(wind->mlx, WIN_WIDTH, WIN_HEIGHT);
	wind->my_mlx.addr = mlx_get_data_addr(wind->my_mlx.img, &wind->my_mlx.bpp, &wind->my_mlx.line_len, &wind->my_mlx.endian);
	while (++x < WIN_WIDTH)
	{
		cast_rays(wind, angle, x);
		angle += WALL_DIM / WIN_WIDTH;
	}
	mlx_put_image_to_window(wind->mlx, wind->window, wind->my_mlx.img, 0, 0);
}

double	calculate_distance(double y_player, double x_player, double y_wall, double x_wall)
{
	return (sqrt(((x_player - x_wall) * (x_player - x_wall)) + ((y_player - y_wall) * (y_player - y_wall))));
}

void	cast_rays(t_mlx *wind, double angle, int x)
{
	double	px;
	double	py;
	char	direction = '\0';
	char	direction_coin = '\0';
	

	px = wind->x_player;
	py = wind->y_player;
	while (TRUE)
	{
		if (wind->map[(int)py / (int)WALL_DIM][(int)px / (int)WALL_DIM] == 'C')
		{
			direction_coin = set_direction_coin(wind->y_player, wind->x_player, wind->y_coin, wind->x_coin, wind);
			wind->distance = calculate_distance(wind->y_player, wind->x_player, wind->y_coin, wind->x_coin);
			wind->where= (int)round(wind->where * (1000.0 / 64.0)) % 1000;
			break;
		}
		if (wind->map[(int)py / (int)WALL_DIM][(int)px / (int)WALL_DIM] == '1')
		{
			wind->x_endray = px;
			wind->y_endray = py;
			wind->distance = calculate_distance(wind->y_player, wind->x_player, py, px);
			direction = set_directions(wind->y_endray, wind->x_endray, wind);
			wind->where= (int)round(wind->where * (1000.0 / 64.0)) % 1000;
			break ;
		}
		px += cos((angle) * (M_PI / 180));
		py += sin((angle) * (M_PI / 180));
	}
	wind->corrected_distance = wind->distance * cos((angle - wind->field_of_view) * (M_PI / 180));
	casting_3d(wind->corrected_distance, x, wind, direction, direction_coin);
}

void	casting_3d(double distance, int height, t_mlx *mlx, char dir, char coin)
{
	int 	i;
	char	*color;
	int		width;

	printf("Coin		=> %c\n", coin);
	printf("Direction	=> %c\n", dir);
	width = 0;
	i = -1;
	mlx->dst_to_projection = ((WIN_WIDTH / 2) / (tan((HALF_WALL) * (M_PI / 180))));
	mlx->projection_3d = (WALL_DIM / distance) * mlx->dst_to_projection;
	mlx->floor_ceiling = (WIN_HEIGHT / 2) - (mlx->projection_3d / 2);
	while (width < WIN_HEIGHT && width < mlx->floor_ceiling)
		my_mlx_pixel_put(&mlx->my_mlx, height, width++, mlx->ceilling);
	while (width < WIN_HEIGHT && width < mlx->floor_ceiling + mlx->projection_3d && ++i < WIN_HEIGHT) 
	{
		if (dir == 'N')
		{
			color = (mlx->my_mlx.addr_w + (((int)(round((i + (mlx->projection_3d - (double)WIN_HEIGHT) * (mlx->projection_3d > WIN_HEIGHT) / 2) * (1000.0 / mlx->projection_3d))) % 1000) * mlx->my_mlx.line_len_w + (int)round(mlx->where) * (mlx->my_mlx.bpp_w / 8)));
			my_mlx_pixel_put(&mlx->my_mlx, height, width++, *(unsigned int *)color);
		}
		else if (dir == 'S')
		{
			color = (mlx->my_mlx.addr_s + (((int)(round((i + (mlx->projection_3d - (double)WIN_HEIGHT) * (mlx->projection_3d > WIN_HEIGHT) / 2) * (1000.0 / mlx->projection_3d))) % 1000) * mlx->my_mlx.line_len_s + (int)mlx->where * (mlx->my_mlx.bpp_s / 8)));
			my_mlx_pixel_put(&mlx->my_mlx, height, width++, *(unsigned int *)color);
		}
		else if (dir == 'W')
		{
			color = (mlx->my_mlx.addr_n + (((int)(round((i + (mlx->projection_3d - (double)WIN_HEIGHT) * (mlx->projection_3d > WIN_HEIGHT) / 2) * (1000.0 / mlx->projection_3d))) % 1000) * mlx->my_mlx.line_len_n + (int)mlx->where * (mlx->my_mlx.bpp_n / 8)));
			my_mlx_pixel_put(&mlx->my_mlx, height, width++, *(unsigned int *)color);
		}
		else if (coin == 'A')
		{
			// color = (mlx->my_mlx.addr_c + (((int)(round((i + (mlx->projection_3d - (double)WIN_HEIGHT) * (mlx->projection_3d > WIN_HEIGHT) / 2) * (1000.0 / mlx->projection_3d))) % 1000) * mlx->my_mlx.line_len_c + (int)mlx->where * (mlx->my_mlx.bpp_c / 8)));
			color = (mlx->my_mlx.addr_n + (((int)(round((i + (mlx->projection_3d - (double)WIN_HEIGHT) * (mlx->projection_3d > WIN_HEIGHT) / 2) * (1000.0 / mlx->projection_3d))) % 1000) * mlx->my_mlx.line_len_n + (int)mlx->where * (mlx->my_mlx.bpp_n / 8)));
			my_mlx_pixel_put(&mlx->my_mlx, height, width++, *(unsigned int *)color);
		}
		else
		{
			color = (mlx->my_mlx.addr_e + (((int)(round((i + (mlx->projection_3d - (double)WIN_HEIGHT) * (mlx->projection_3d > WIN_HEIGHT) / 2) * (1000.0 / mlx->projection_3d))) % 1000) * mlx->my_mlx.line_len_e + (int)mlx->where * (mlx->my_mlx.bpp_e / 8)));
			my_mlx_pixel_put(&mlx->my_mlx, height, width++, *(unsigned int *)color);
		}
	}
	while (width < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&mlx->my_mlx, height, width++, mlx->floor);
	}
}
