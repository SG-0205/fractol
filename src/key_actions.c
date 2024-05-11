/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:30:36 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 17:05:23 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdio.h>

int	get_x_y_coeff(t_fractol *data)
{
	int		coef;

	coef = 1;
	coef = ft_powerofi(data->zoom_factor, 2);
	if (data->zoom_factor >= 10 && data->zoom_factor < 15)
		coef *= 3;
	if (data->zoom_factor >= 15)
		coef *= 8;
	return (coef);
}

void	update_xy(t_fractol *data, int side, double len)
{
	if (side == UP)
	{
		data->fract_mi += len / (get_x_y_coeff(data));
		data->fract_mxi += len / (get_x_y_coeff(data));
	}
	else if (side == DOWN)
	{
		data->fract_mi -= len / (get_x_y_coeff(data));
		data->fract_mxi -= len / (get_x_y_coeff(data));
	}
	else if (side == RIGHT)
	{
		data->fract_mr += len / (get_x_y_coeff(data));
		data->fract_mxr += len / (get_x_y_coeff(data));
	}
	else if (side == LEFT)
	{
		data->fract_mr -= len / (get_x_y_coeff(data));
		data->fract_mxr -= len / (get_x_y_coeff(data));
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

void	update_z(t_fractol *data, double len, int code)
{
	double	c_r;
	double	c_i;

	if ((code == KEY_W || code == MOUSE_WHEEL_UP))
		data->zoom_factor += 1;
	else if ((code == KEY_S || code == MOUSE_WHEEL_DOWN))
		data->zoom_factor -= 1;
	c_i = data->fract_mxi - data->fract_mi;
	c_r = data->fract_mr - data->fract_mxr;
	data->fract_mxr = data->fract_mxr + (c_r - len * c_r) / 2;
	data->fract_mr = data->fract_mxr + len * c_r;
	data->fract_mi = data->fract_mi + (c_i - len * c_i) / 2;
	data->fract_mxi = data->fract_mi + len * c_i;
}
