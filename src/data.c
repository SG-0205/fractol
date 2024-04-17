/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:57:19 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/17 18:16:21 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	clear_data(t_fractol *data, char *err_src, int error)
{
	if (data->color_bank)
		free(data->color_bank);
	if (data->color_buff)
		free(data->color_buff);
	if (!data)
		exit(error);
	if (data->img_ptr && data->mlx_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr && data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_loop_end(data->mlx_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (err_src)
		(ft_printf("%s : %s\n", err_src, strerror(error)), exit(error));
	else
		ft_printf("%s\n", strerror(error));
	free(data);
	exit(error);
}

void	config_by_id(t_fractol *data)
{
	if (data->fract_id == FID_MANDELBROT)
	{
		data->fract_mxr = 4.0;
		data->fract_mr = -4.0;
		data->fract_mi = -4.0;
		data->fract_mxi = ((data->fract_mxr - data->fract_mr) + data->fract_mi)
			* (data->win_h / data->win_w);
	}
	if (data->fract_id == FID_JULIA)
	{
		data->julia_id = FID_J_RABBIT;
		update_starting_point(data);
		data->fract_mxr = 4.0;
		data->fract_mr = -4.0;
		data->fract_mi = -4.0;
		data->fract_mxi = ((data->fract_mxr - data->fract_mr) + data->fract_mi)
			* (data->win_h / data->win_w);
	}
}

t_bool	init_data(t_fractol *data)
{
	data->color_bank = NULL;
	data->color_buff = NULL;
	data->color_front = 1;
	data->julia_id = 21;
	data->color_back = 10;
	data->fract_mxi = 0;
	data->fract_mi = 0;
	data->fract_mxr = 0;
	data->fract_mr = 0;
	data->fract_fx = 0;
	data->fract_rx = 0;
	data->fract_sx = 0;
	data->fract_ki = 0;
	data->fract_kr = 0;
	data->img_ptr = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->win_w = WIN_W;
	data->win_h = WIN_H;
	return (TRUE);
}

void	new_image(t_fractol *data)
{
	int		endian;
	char	*data_address;
	int		p_b;
	int		l_b;

	data->img_ptr = mlx_new_image(data->mlx_ptr, data->win_w, data->win_h);
	data_address = mlx_get_data_addr(data->img_ptr, &p_b, &l_b, &endian);
	if (!data_address)
		clear_data(data, "new_image", errno);
	data->img_data = data_address;
	if (!data->color_buff)
		data->color_buff = (int *)malloc(sizeof(int) * (PRECISION + 1));
	if (!data->color_buff)
		clear_data(data, "new_image", errno);
	else
		ft_bzero(data->color_buff, PRECISION + 1);
}

void	start_mlx(t_fractol *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		clear_data(data, "start_mlx", errno);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H,
			"FRACTOL");
	if (!data->win_ptr)
		clear_data(data, "start mlx", errno);
	data->fract_fx = 1.0;
	data->fract_rx = 0.5;
	data->fract_sx = 2.0;
	data->color_bank = create_color_bank();
	if (!data->color_bank)
		clear_data(data, "start_mlx", errno);
	config_by_id(data);
	set_colors(data, data->color_bank[data->color_back],
		data->color_bank[data->color_front]);
}
