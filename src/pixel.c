/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:25:33 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 15:44:39 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | a);
}

void	put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t rgba)
{
	if ((uint32_t)x < img->width && (uint32_t)y < img->height)
		mlx_put_pixel(img, x, y, rgba);
}

void	clear_image(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, (img->width * img->height * 4));
}
