/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:40:33 by timurray          #+#    #+#             */
/*   Updated: 2025/07/16 15:18:42 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIDTH 1080
#define HEIGHT 1920

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				0x00, // R
				0xBB, // G
				0x00, // B
				0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

// void ft_put_grid()
// {
// 	for (uint32_t x = 0; x < image->width; ++x)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
// 			if((x % 20 == 0) && (y % 20 == 0) )
// 				color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
// 			else
// 				color = ft_pixel(0x00, 0x00, 0x00, 0x00);

// 			mlx_put_pixel(image, x, y, color);
// 		}
// 	}
// }

int iso_x(int i, int j)
{
	return (int)round((i - j) * (sqrt(3.0) / 2.0));
}

int iso_y(int i, int j)
{
	return ((int)(round((i+j) * 0.5)));
}

void ft_put_dots()
{
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);

	int rows = 30;
	int cols = 20;
	int i;
	int j;
	int x = 0;
	int y = 0;
	int spacing = 15;
	int x_offset = (int)((rows * (spacing) ));
	int y_offset = (int)((rows * (spacing) ));
	
	i = 0;
	while(i < rows)
	{
		j = 0;
		while(j < cols)
		{
			x = iso_x(i * spacing, j * spacing) + x_offset;
			y = iso_y(i * spacing, j * spacing) + y_offset;

			if (i % 7 == 0 && j % 13 == 0)
			{
				y -= 50;
			}

			if (i % 11 == 0 && j % 7 == 0)
			{
				y += 50;
			}

			printf("x: %i y: %i, i: %i, j: %i \n", x, y, i, j);
			mlx_put_pixel(image, x, y, color);
			j++;
		}
		i++;
	}
}


void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

int32_t main(void)
{
	mlx_t* mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 1000, 1000)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 10, 10) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	// mlx_loop_hook(mlx, ft_put_grid, mlx);

	mlx_loop_hook(mlx, ft_put_dots, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
