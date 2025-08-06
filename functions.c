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

			int alpha = 30;
			x =  iso_u(alpha, i*spacing, j*spacing, z) + x_offset;
			y = iso_v(alpha, i*spacing, j*spacing, z) + y_offset;

			printf("x: %i y: %i, i: %i, j: %i \n", x, y, i, j);
			mlx_put_pixel(image, x, y, color);
			j++;
		}
		i++;
	}
}