/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:40:33 by timurray          #+#    #+#             */
/*   Updated: 2025/08/03 17:14:44 by timurray         ###   ########.fr       */
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

/* void ft_randomize(void* param)
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
} */

void ft_put_grid()
{
	for (uint32_t x = 0; x < image->width; ++x)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
			if((x % 20 == 0) && (y % 20 == 0) )
				color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
			else
				color = ft_pixel(0x00, 0x00, 0x00, 0x00);

			mlx_put_pixel(image, x, y, color);
		}
	}
}

/* int iso_x(int i, int j)
{
	return (int)round((i - j) * (sqrt(3.0) / 2.0));
}

int iso_y(int i, int j)
{
	return ((int)(round((i+j) * 0.5)));
}

int iso_xz(int x, int y, int z)
{
	(void)y;
	return ((int)(round((x - z)/sqrt(2.0))));
}

int iso_yz(int x, int y, int z)
{
	return ((int)(round((x + 2*y + z)/sqrt(6.0))));
} */

double rad(int deg)
{
	return (deg * 0.017453292519943295);
}

int iso_u(int alpha, double x, double y, double z)
{
	x = x * cos(rad(alpha));
	y = y * cos(rad(alpha + 120));
	z = z * cos(rad(alpha - 120));

	return ((int)round(x + y + z));
}

int iso_v(int alpha, double x, double y, double z)
{
	x = x * sin(rad(alpha));
	y = y * sin(rad(alpha + 120));
	z = z * sin(rad(alpha - 120));

	return ((int)round(x + y + z));
}


void ft_put_dots()
{
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);

	int rows = 30;
	int cols = 15;
	int i;
	int j;
	int x = 0;
	int y = 0;
	int z = 0;
	int spacing = 15;
	int x_offset = (int)((rows * (spacing) ));
	int y_offset = (int)((rows * (spacing)/2 ));
	
	i = 0;
	while(i < rows)
	{
		j = 0;
		while(j < cols)
		{
			// x = iso_x(i * spacing, j * spacing) + x_offset;
			// y = iso_y(i * spacing, j * spacing) + y_offset;
			if (j == 0 && i == 0)
				z = 50;
			else if (j == 14 && i == 29)
				z = -20;
			else 
				z = 0;
				
			// y = iso_xz(i * spacing, j * spacing, z) + x_offset;
			// x = iso_yz(i * spacing, j * spacing, z) + y_offset;

			int alpha = 45;
			x =  iso_u(alpha, i*spacing, j*spacing, z) + x_offset;
			y = iso_v(alpha, i*spacing, j*spacing, z) + y_offset;

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

int check_file(const char *filename, const char *extension)
{
	const char *dot;
	int ext_length;

	dot = ft_strrchr(filename, '.');
	ext_length = ft_strlen(extension);
	if (!dot || dot == filename)
		return (0);
	else
		return (ft_strncmp(dot, extension, ext_length) == 0);
}

int32_t main(int ac,char **av)
{
	// mlx_t* mlx;
	int fd;

	if (ac != 2)
		return (EXIT_FAILURE);
	else
	{		
		char	*line;
		if (check_file(av[1], ".fdf"))
		{
			fd = open(av[1], O_RDONLY);
			while ((line = get_next_line(fd)))
			{
				ft_printf("%s", line);
				free(line);
			}	
		}
		else
			return (EXIT_FAILURE);
	}

	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
	// {
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (!(image = mlx_new_image(mlx, 1000, 1000)))
	// {
	// 	mlx_close_window(mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (mlx_image_to_window(mlx, image, 10, 10) == -1)
	// {
	// 	mlx_close_window(mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	// mlx_loop_hook(mlx, ft_put_grid, mlx);

	// mlx_loop_hook(mlx, ft_put_dots, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

/* 
TODO: Array resizing?
	
TODO: Get 2D array of 3D colour points
	- Read lines
	- Split on spaces
	- Split z and colour
	
TODO: Transform array in isometric points.
TODO: Draw lines to connect dots.
TODO: colour?
TODO: Orbit rotation?
 */