/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:40:33 by timurray          #+#    #+#             */
/*   Updated: 2025/08/13 17:07:15 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static mlx_image_t* image; //TODO: Global?

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
		return (EXIT_FAILURE);
	else
		return (!((ft_strncmp(dot, ext, ext_len) == 0) && dot[ext_len] == '\0'));
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

void on_scroll(double dx, double dy, void *param)
{
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

void clear_image(mlx_image_t *img)
{
    ft_memset(img->pixels, 0, (img->width * img->height * 4));
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

void isometric(t_projection *p)
{
	int		x;
	int		y;
	t_coord	*c;

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
}

void render(t_projection *p)
{
    clear_image(p->image);
	isometric(p);
	ft_draw_line(p->matrix, p->x_max, p->y_max);
}

void init_projection(t_projection *p)
{
	p->x_max = 0;
	p->y_max = 0;
	p->mlx = NULL;
	p->image = NULL;
	p->alpha = 30;
	p->height = 1920;
	p->width = 1920;
}

int count_points(char **points)
{
	int i;

	i = 0;
	while(points[i])
		i++;
	return (i);
}

void free_split(char **array)
{
	int i;

	i = 0;
	if(!array)
		return ;
	while(array[i])
		free(array[i++]);
	free(array);
}

void init_coord(t_coord *coord, char **points, int x, int y)
{
	char	**colour_data;

	if(ft_strchr(points[x], ','))
	{
		colour_data = ft_split(points[x], ',');
		coord->z = ft_atoi(colour_data[0]);
		free_split(colour_data);
	}
	else
		coord->z = ft_atoi(points[x]);
	coord->x = x;
	coord->y = y;
	coord->rgba = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
}

t_coord *parse(char *line, int y, int *x_count)
{
	int		x;
	char	**points;
	t_coord	*coords;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \n\t\v\r\f");
	if(!trimmed_line)
		return (NULL);
	points = ft_split(trimmed_line, ' ');
	if (!points)
	{
		free(trimmed_line);
		return (NULL);
	}
	*x_count = count_points(points);
	coords = (t_coord *)malloc(sizeof(t_coord) * (*x_count));
	if (!coords)
		return (NULL);
	x = 0;
	while (x < *x_count)
	{
		init_coord(&coords[x], points, x, y);
		x++;
	}
	free(trimmed_line);
	free_split(points);
	return (coords);
}

int load_matrix(t_projection *projection, char *file)
{
	int		fd;
	
	t_coord **temp;
	int x;
	int y;
	int i;
	int cap;
	char	*line;

	x = 0;
	y = 0;
	fd = open(file, O_RDONLY);
	if(fd == -1)
	{
		ft_printf("File: %s not found.", file);
		return (EXIT_FAILURE);
	}
	projection->matrix = (t_coord **)malloc(sizeof(t_coord *));
	cap = 1;
	while ((line = get_next_line(fd)))
	{
		x = 0;
		projection->matrix[y] = parse(line, y, &x);
		if(projection->matrix[y] == NULL)
		{
			free(line);
			close(fd);
			return (EXIT_FAILURE);
		}
		y++;
		if(x > projection->x_max)
			projection->x_max = x;
		if (y >= cap)
		{
			temp = (t_coord **)malloc(sizeof(t_coord *) * ++cap);
			if(!temp)
			{
				free(line);
				close(fd);
				return (0);
			}
			i = 0;
			while (i < y)
			{
				temp[i] = projection->matrix[i];
				i++;
			}
			free(projection->matrix); //TODO: improve this.
			projection->matrix = temp;
		}
		// ft_printf("%s", line); //TODO: Remove
		free(line);
	}
	close(fd);
	projection->y_max = y;
	return (EXIT_SUCCESS);
}

int init_mlx(t_projection *p)
{
	if (!(p->mlx = mlx_init(p->width, p->height, "FDF", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(p->mlx, p->width, p->height)))
	{
		mlx_close_window(p->mlx);
		// puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(p->mlx, image, 0, 0) == -1)
	{
		mlx_close_window(p->mlx);
		// puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int32_t main(int ac, char **av)
{
	t_projection	projection;
	
	init_projection(&projection);
	if (ac != 2)
		return (EXIT_FAILURE);
	else
	{
		if (((check_file(av[1], ".fdf")) || (load_matrix(&projection, av[1]))))
			return (EXIT_FAILURE);
	}
	projection.gap = (int)round(projection.height/projection.x_max/2) ;
	projection.y_offset = projection.height/2;
	projection.x_offset = projection.width/2;
	if(init_mlx(&projection))
		return (EXIT_FAILURE);
	projection.image = image; //TODO: use instead of global.
	mlx_scroll_hook(projection.mlx, on_scroll, &projection);
	mlx_loop_hook(projection.mlx, ft_hook, &projection);
	mlx_loop(projection.mlx);

	ft_printf("this ran\n");
	mlx_terminate(projection.mlx);
	return (EXIT_SUCCESS);
}

/* 
TODO: Clip functions.

TODO: Leaks, leaks, leaks. Correctly free.

TODO: process the u,v's intitially.

TODO: line low+high, passed image.

TODO:get min of the max x's or reject map.

TODO: max & min int? 
TODO: empty map?

TODO: initial zoom level(gap), offsets.
TODO: puts?

TODO: libft fixes

TODO: Check return values
TODO: Norminette.
 */