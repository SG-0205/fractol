/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:27:44 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/11 14:58:54 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	fract_parse(t_fractol *data, double real, double imaginary)
{
	int	iterations;

	iterations = 0;
	if (data->fract_id == FID_MANDELBROT)
		iterations = mandelbrot(real, imaginary);
	if (data->fract_id == FID_JULIA)
		iterations = julia(real, imaginary, data);
	return (iterations);
}

//B = 0 G = 8 R = 16 T = 24
void	print_color(int x, int y, t_fractol *data, int iter)
{
	int	color;

	color = data->color_buff[iter];
	data->img_data[x * 4 + y * WIN_W * 4] = color;
	data->img_data[x * 4 + y * WIN_W * 4 + 1] = color >> 8;
	data->img_data[x * 4 + y * WIN_W * 4 + 2] = color >> 16;
	data->img_data[x * 4 + y * WIN_W * 4 + 3] = color >> 24;
}

void	draw(t_fractol *data)
{
	int		hor;
	int		vert;
	int		iterations;
	double	real;
	double	imaginary;

	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	vert = -1;
	while (++vert < WIN_H)
	{
		hor = -1;
		while (++hor < WIN_W)
		{
			real = data->fract_mr + (double)hor * (data->fract_mxr
					- data->fract_mr) / WIN_W;
			imaginary = data->fract_mxi + (double)vert * (data->fract_mi
					- data->fract_mxi) / WIN_H;
			iterations = fract_parse(data, real, imaginary);
			print_color(hor, vert, data, iterations);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
