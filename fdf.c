/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:40:33 by timurray          #+#    #+#             */
/*   Updated: 2025/08/12 13:45:46 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIDTH 1920
#define HEIGHT 1920

static mlx_image_t* image; //Global?

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t projection)
{
    return (r << 24 | g << 16 | b << 8 | projection);
}

void put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t rgba)
{
    if ((uint32_t)x < img->width && (uint32_t)y < img->height)
        mlx_put_pixel(img, x, y, rgba);
}

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

void ft_hook(void *param)
{
    t_projection	*projection;
    mlx_t			*mlx;

	projection = param;
	mlx = projection->mlx;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	else
	{	
		if (mlx_is_key_down(mlx, MLX_KEY_UP))
			projection->y_offset -= 5;
		if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
			projection->y_offset += 5;
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			projection->x_offset -= 5;
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
			projection->x_offset += 5;
		projection->redraw = 1;
	}
	if (projection->redraw)
	{
		render(projection);
		projection->redraw = 0;
	}
}

int check_file(const char *filename, const char *ext)
{
	const char	*dot;
	int			ext_len;

	dot = ft_strrchr(filename, '.');
	ext_len = ft_strlen(ext);
	if ((!dot || dot == filename))
		return (0);
	else
		return ((ft_strncmp(dot, ext, ext_len) == 0) && dot[ext_len] == '\0');
}

t_coord *parse(char *line, int y, int *x_count)
{
	int		x;
	char	**points;
	char	**colour_data;
	t_coord	*coords;

	points = ft_split(line, ' ');
	if (!points)
		return (NULL);
	x = 0;
	*x_count = 0;
	while (points[x++])
		(*x_count)++;
	coords = (t_coord *)malloc(sizeof(t_coord) * x);
	x = 0;
	while (x < *x_count)
	{
		if(ft_strchr(points[x], ','))
		{
			colour_data = ft_split(points[x], ',');
			coords[x].z = ft_atoi(colour_data[0]);
		}
		else
			coords[x].z = ft_atoi(points[x]);
		coords[x].x = x;
		coords[x].y = y;
		coords[x].rgba = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
		x++;
	}
	return (coords);
}

void line_low(t_coord start, t_coord end, int dy, int dx)
{
	int yi;
	int d;
	uint32_t color;
	
	color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	while (start.u <= end.u)
	{
		put_pixel_safe(image, start.u, start.v, color);
		if (d > 0)
		{
			start.v = start.v + yi;
			d = d + (2 *(dy - dx));
		}
		else
			d = d + (2*dy);
		(start.u)++;
	}
}

void line_high(t_coord start, t_coord end, int dy, int dx)
{
	int			xi;
	int			d;
	uint32_t	color;
	
	color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	xi = 1;
	if(dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	while (start.v <= end.v)
	{
		put_pixel_safe(image, start.u, start.v, color);
		if (d > 0)
		{
			start.u = start.u + xi;
			d = d + (2 *(dx - dy));
		}
		else
			d = d + (2*dx);
		(start.v)++;
	}
}

void bresenham(t_coord start, t_coord end)
{
	int dy;
	int dx;

	dy = abs(end.v - start.v);
	dx = abs(end.u - start.u);
	if (dy < dx)
	{
		if (start.u > end.u)
			line_low(end, start, (start.v - end.v), (start.u - end.u));
		else
			line_low(start, end, (end.v - start.v), (end.u - start.u));
	}
	else
	{
		if (start.v > end.v)
			line_high(end, start, (start.v - end.v), (start.u - end.u));
		else
			line_high(start, end, (end.v - start.v), (end.u - start.u));
	}
}

void on_scroll(double dx, double dy, void *param) {
    t_projection *projection; 
    int new_gap;
	
	(void)dx;
	projection = param;
	new_gap = projection->gap + (int)dy;
    if (new_gap < 1)
		new_gap = 1;
    if (new_gap > 100)
		new_gap = 100;
    if (new_gap != projection->gap)
	{
		projection->gap = new_gap;
		projection->redraw = 1;
	}
}

void clear_image(mlx_image_t *img) {
    ft_memset(img->pixels, 0, img->width * img->height * 4);
}

void ft_draw_line(t_coord **m, int max_x, int max_y)
{
	int x;
	int y;

	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			if ((y + 1) < max_y)
				bresenham(m[y][x], m[y + 1][x]);
			if ((x + 1) < max_x)
				bresenham(m[y][x], m[y][x + 1]);
			x++;
		}
		y++;
	}
}

void render(t_projection *p)
{
	int		x;
	int		y;
	t_coord	*c;

    clear_image(p->image);
	y = 0;
	while (y < p->y_max)
	{
		x = 0;
		while (x < p->x_max)
		{
            c = &p->matrix[y][x];
            c->u = iso_u(p->alpha, c->x * p->gap, c->y * p->gap, \
				c->z * p->gap) + p->x_offset;
            c->v = iso_v(p->alpha, c->x * p->gap, c->y * p->gap, \
				c->z * p->gap) + p->y_offset;
			x++;
        }
		y++;
    }
	ft_draw_line(p->matrix, p->x_max, p->y_max);
}

int32_t main(int ac, char **av)
{
	mlx_t* mlx;
	char	*line;
	int 	fd;
	t_coord **matrix;
	t_coord **temp;

	int	x_max;
	int y_max;
	int x;
	int y;
	int i;
	int cap;

	t_projection projection;

	x_max = 0;
	y_max = 0;
	x = 0;
	y = 0;
	if (ac != 2)
		return (EXIT_FAILURE);
	else
	{
		if (check_file(av[1], ".fdf"))
		{
			fd = open(av[1], O_RDONLY);
			if(fd == -1)
			{
				ft_printf("File: %s not found.", av[1]);
				return (EXIT_FAILURE);
			}
			matrix = (t_coord **)malloc(sizeof(t_coord *));
			cap = 1;
			while ((line = get_next_line(fd)))
			{
				x = 0;
				matrix[y] = parse(line, y, &x);
				if(matrix[y] == NULL)
					return (EXIT_FAILURE);
				y++;
				if(x > x_max)
					x_max = x;
				if (y >= cap)
				{
					temp = (t_coord **)malloc(sizeof(t_coord *) * ++cap);
					if(!temp)
						return (EXIT_FAILURE);
					i = 0;
					while (i < y)
					{
						temp[i] = matrix[i];
						i++;
					}
					free(matrix);
					matrix = temp;
				}
				// ft_printf("%s", line); //TODO: Remove
				free(line);
			}
			y_max = y;
		}
		else
			return (EXIT_FAILURE);
	}

	projection.mlx = NULL;
	projection.image = NULL;
	projection.matrix = matrix;
	projection.x_max = x_max;
	projection.y_max = y_max;
	projection.gap = 10;
	projection.alpha = 30;
	projection.x_offset = WIDTH/2;
	projection.y_offset = HEIGHT/2;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	projection.mlx = mlx;
	projection.image = image;
	mlx_scroll_hook(mlx, on_scroll, &projection);
	mlx_loop_hook(mlx, ft_hook, &projection);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

/* 
TODO: Clip functions.

TODO: Leaks, leaks, leaks. Correctly free.

TODO: initial zoom level(gap), offsets.
TODO: puts?
TODO: Norminette.
 */