/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:27 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 17:01:51 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mouse_hooks(int code, int x, int y, t_fractol *data)
{
	if (code == MOUSE_WHEEL_DOWN)
		update_z(data, 2, code);
	else if (code == MOUSE_WHEEL_UP)
	{
		update_z(data, 0.5, code);
		x -= WIN_W / 2;
		y -= WIN_H / 2;
		if (x < 0)
			update_xy(data, (double)x * -1 / WIN_W, LEFT);
		else if (x > 0)
			update_xy(data, (double)x / WIN_W, RIGHT);
		if (y < 0)
			update_xy(data, (double)y * -1 / WIN_H, DOWN);
		else if (y > 0)
			update_xy (data, (double)y / WIN_H, UP);
	}
	draw(data);
	return (0);
}
