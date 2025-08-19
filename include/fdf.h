/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:56:35 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 17:58:51 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_coord
{
	int			x;
	int			y;
	int			z;
	int			u;
	int			v;
	uint32_t	rgba;
}				t_coord;

typedef struct s_projection
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_coord		**matrix;
	int			x_max;
	int			y_max;
	int			gap;
	int			alpha;
	int			x_offset;
	int			y_offset;
	int			redraw;
	int			height;
	int			width;
}				t_projection;

double			rad(int deg);
int				iso_u(int alpha, double x, double y, double z);
int				iso_v(int alpha, double x, double y, double z);
void			isometric(t_projection *p);

uint32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t rgba);
void			clear_image(mlx_image_t *img);

void			ft_hook(void *param);
void			on_scroll(double dx, double dy, void *param);

void			line_low(mlx_image_t *img, t_coord start, t_coord end, int dy);
void			line_high(mlx_image_t *img, t_coord start, t_coord end, int dx);
void			bresenham(mlx_image_t *img, t_coord start, t_coord end);
void			ft_draw_line(t_projection *p);
void			render(t_projection *p);

int				init_coord(t_coord *coord, char **points, int x, int y);
int				assign_coord_z(t_coord *coord, char *z_data);
int				set_points(t_projection *p, char **points, int y);
int				inc_matrix(t_projection *p, int *cap, int fd, int y);
int				parse(t_projection *p, char *line, int y, int x);

int				free_return_parse(char **points);
int				free_split_return(char **points);
int				free_projection_return(t_projection *p);
int				free_coords_points_return(char **points, t_coord *coords);
int				close_fd_return(int fd);
int				free_points_return(char **points);

void			free_matrix(t_projection *p);
void			free_split(char **array);
int				load_matrix_return(t_projection *p, int y, int fd);
int				free_matrix_return(t_projection *p, int y, int fd, char *line);
int				free_matrix_fd_return(t_projection *p, int fd);

int				load_matrix(t_projection *p, char *file, int y, int cap);
int				check_file(const char *filename, const char *ext);
void			init_projection(t_projection *p);
int				init_mlx(t_projection *p);
void			set_matrix(t_projection *p);

int				return_file_error(void);
int				return_args_error(void);

#endif