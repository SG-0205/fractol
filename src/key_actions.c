/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:30:36 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/17 18:00:26 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	get_x_y_coeff(double c)
{
	double	absval_c;
	int		coef;

	coef = 1;
	absval_c = get_absval(c);
	if (absval_c > 2)
		coef = 2;
	else if (absval_c < 2 && absval_c > 1)
		coef = 4;
	else if (absval_c < 1 && absval_c > 0.9)
		coef = 16;
	else if (absval_c < 0.9 && absval_c > 0.7)
		coef = 32;
	else
		coef = 128;
	if (absval_c < 0.3)
		return (coef * 2);
	else
		return (coef);
}

void	update_xy(t_fractol *data, int side, double len)
{
	double	c_i;
	double	c_r;

	c_i = get_absval(data->fract_mxi);
	c_r = get_absval(data->fract_mxr);
	if (side == UP)
	{
		data->fract_mi += len * c_i / (get_x_y_coeff(c_r));
		data->fract_mxi += len * c_i / (get_x_y_coeff(c_r));
	}
	else if (side == DOWN)
	{
		data->fract_mi -= len * c_i / (get_x_y_coeff(c_r));
		data->fract_mxi -= len * c_i / (get_x_y_coeff(c_r));
	}
	else if (side == RIGHT)
	{
		data->fract_mr += len * c_r / (get_x_y_coeff(c_r));
		data->fract_mxr += len * c_r / (get_x_y_coeff(c_r));
	}
	else if (side == LEFT)
	{
		data->fract_mr -= len * c_r / (get_x_y_coeff(c_r));
		data->fract_mxr -= len * c_r / (get_x_y_coeff(c_r));
	}
}

void	update_colors(t_fractol *data, int key)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (key == KEY_F)
	{
		if (data->color_front >= 12)
			data->color_front = 1;
		data->color_front ++;
	}
	else if (key == KEY_B)
	{
		if (data->color_back >= 12)
			data->color_back = 0;
		data->color_back ++;
	}
	if (data->color_back == data->color_front)
		data->color_front ++;
	set_colors(data, data->color_bank[data->color_back],
		data->color_bank[data->color_front]);
}

void	update_z(t_fractol *data, double len)
{
	double	c_r;
	double	c_i;

	c_i = data->fract_mxi - data->fract_mi;
	c_r = data->fract_mr - data->fract_mxr;
	data->fract_mxr = data->fract_mxr + (c_r - len * c_r) / 2;
	data->fract_mr = data->fract_mxr + len * c_r;
	data->fract_mi = data->fract_mi + (c_i - len * c_i) / 2;
	data->fract_mxi = data->fract_mi + len * c_i;
}
