/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:35:08 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/17 17:46:12 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// rgb = 0R 1G 2B
// Modifie les bits de chaque int pour encoder la couleur sur chaque "colonne"
int	split_colors(int start, int end, double coef)
{
	int	rgb_s[3];
	int	rgb_e[3];

	rgb_s[0] = ((start >> 16) & 0xFF);
	rgb_s[1] = ((start >> 8) & 0xFF);
	rgb_s[2] = ((start >> 0) & 0xFF);
	rgb_e[0] = ((end >> 16) & 0xFF);
	rgb_e[1] = ((end >> 8) & 0xFF);
	rgb_e[2] = ((end >> 0) & 0xFF);
	rgb_s[0] = (rgb_e[0] - rgb_s[0]) * coef + rgb_s[0];
	rgb_s[1] = (rgb_e[1] - rgb_s[1]) * coef + rgb_s[1];
	rgb_s[2] = (rgb_e[2] - rgb_s[2]) * coef + rgb_s[2];
	return (0xFF << 24 | rgb_s[0] << 16 | rgb_s[1] << 8 | rgb_s[2]);
}

void	fade_to_white(t_fractol *data, int color, int neutral)
{
	int		i;
	int		j;
	double	fraction;
	int		color1;
	int		color2;

	color1 = neutral;
	color2 = color;
	i = 0;
	while (i < PRECISION)
	{
		j = 0;
		while (j < PRECISION / 2)
		{
			fraction = (double)j / (PRECISION / ft_powerofi(2,
						data->color_smooth));
			data->color_buff[i + j] = split_colors(color1, color2, fraction);
			j++;
		}
		color1 = color2;
		color2 = 0xFFFFFF;
		i += j;
	}
	data->color_buff[PRECISION - 1] = 0;
}

void	set_colors(t_fractol *data, int background, int front)
{
	new_image(data);
	fade_to_white(data, front, background);
}
