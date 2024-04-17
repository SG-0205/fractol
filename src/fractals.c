/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:32:33 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/16 19:18:54 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mandelbrot(double c_real, double c_imaginary)
{
	double	z_im;
	double	z_rea;
	double	swap;
	int		i;

	z_rea = 0;
	z_im = 0;
	i = -1;
	while (++i < PRECISION)
	{
		if ((z_rea * z_rea + z_im * z_im) > 4.0)
			break ;
		swap = 2 * z_rea * z_im + c_real;
		z_rea = z_rea * z_rea - z_im * z_im + c_imaginary;
		z_im = swap;
	}
	return (i);
}

int	julia(double z_real, double z_imaginary, t_fractol *data)
{
	double	swap;
	int		i;

	i = 0;
	while (i < (PRECISION))
	{
		if ((z_imaginary * z_imaginary + z_real * z_real) > 4.0)
			break ;
		swap = 2 * z_real * z_imaginary + data->fract_ki;
		z_real = z_real * z_real - z_imaginary * z_imaginary + data->fract_kr;
		z_imaginary = swap;
		i++;
	}
	return (i);
}
