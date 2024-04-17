/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:54:34 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/17 18:09:51 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	update_continuation(t_fractol *data)
{
	if (data->julia_id == FID_J_SYMVERT)
	{
		data->fract_kr = 0.285;
		data->fract_ki = 0;
	}
	else if (data->julia_id == FID_J_CREMER)
	{
		data->fract_kr = -0.12256;
		data->fract_ki = 0.74486;
	}
	else if (data->julia_id == FID_J_LEAF)
	{
		data->fract_kr = -0.39054;
		data->fract_ki = 0.58679;
	}
	else if (data->julia_id == FID_J_BURNING_S)
	{
		data->fract_kr = -0.835;
		data->fract_ki = 0.2321;
	}
	else if (data->julia_id == FID_J_DISC)
	{
		data->fract_kr = -0.3;
		data->fract_ki = 0.61;
	}
}

void	update_starting_point(t_fractol *data)
{
	if (data->julia_id == FID_J_RABBIT)
	{
		data->fract_kr = -0.7;
		data->fract_ki = 0.27015;
	}
	else if (data->julia_id == FID_J_SEAHORSE)
	{
		data->fract_kr = -0.8;
		data->fract_ki = 0.156;
	}
	else if (data->julia_id == FID_J_SPIRALS)
	{
		data->fract_kr = -0.4;
		data->fract_ki = 0.6;
	}
	else if (data->julia_id == FID_J_SYMHOR)
	{
		data->fract_kr = -0.75;
		data->fract_ki = 0.6;
	}
	else
		update_continuation(data);
}

void	update_julia(t_fractol *data)
{
	data->fract_id = FID_JULIA;
	if (data->julia_id < 21 || data->julia_id > 28)
		data->julia_id = FID_J_RABBIT;
	else
		data->julia_id += 1;
	update_starting_point(data);
}

void	print_coordinates(t_fractol *data)
{
	ft_printf("////////// X_Y_Z //////////\n");
	ft_printf("x / y\t %f / %f\n", data->fract_mr, data->fract_mi);
	ft_printf("X / Y\t %f / %f\n", data->fract_mxr, data->fract_mxi);
	ft_printf("LSD = %d\n\n", data->color_smooth);
}
