/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:39:34 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/17 18:06:44 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdio.h>

int	close_by_btn(t_fractol *data)
{
	clear_data(data, NULL, 0);
	return (0);
}

int	clear_data_wrap(t_fractol *data)
{
	clear_data(data, NULL, 0);
	return (0);
}

double	filter_len(t_fractol *data, double len)
{
	if (data->fract_id == FID_JULIA)
		return (len * 5);
	else
		return (len);
}

int	key_hooks(int code, t_fractol *data)
{
	if (code == KEY_ESC)
		return (clear_data_wrap(data));
	else if (code == KEY_DOWN)
		update_xy(data, DOWN, filter_len(data, 0.1));
	else if (code == KEY_UP)
		update_xy(data, UP, filter_len(data, 0.1));
	else if (code == KEY_LEFT)
		update_xy(data, LEFT, filter_len(data, 0.1));
	else if (code == KEY_RIGHT)
		update_xy(data, RIGHT, filter_len(data, 0.1));
	else if (code == KEY_S)
		update_z(data, 2);
	else if (code == KEY_W)
		update_z(data, 0.5);
	else if (code == KEY_R)
		reset_view(data);
	else if (code == KEY_J)
		(update_julia(data), reset_view(data));
	else if (code == KEY_M)
		data->fract_id = FID_MANDELBROT;
	else if (code == KEY_F || code == KEY_B)
		update_colors(data, code);
	print_coordinates(data);
	draw(data);
	return (0);
}
