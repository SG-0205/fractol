/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:06:51 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 16:56:16 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	print_error(char *source, int error)
{
	if (source)
	{
		ft_printf("%s : %s\n", source, strerror(error));
		return (error);
	}
	else
		ft_printf("%s\n", strerror(error));
	return (error);
}

double	get_absval(double number)
{
	if (number < 0)
		return (number * -1);
	return (number);
}

void	reset_view(t_fractol *data)
{
	data->fract_mi = -4;
	data->fract_mxi = 4;
	data->fract_mxr = 4;
	data->fract_mr = -4;
	data->zoom_factor = 0;
}

int	name_to_id(char *name)
{
	char	*fract_ok;
	char	**fract_names;
	int		index;

	fract_ok = "mandelbrot,julia";
	fract_names = ft_split(fract_ok, ',');
	if (!fract_names)
		return (-1);
	index = ft_arrloc(fract_names, name) + 1;
	ft_arrfree((void **)fract_names);
	free(fract_names);
	return (index);
}

int	*create_color_bank(void)
{
	int	*bank;

	bank = (int *)malloc(sizeof(int) * 13);
	if (!bank)
		return (NULL);
	bank[0] = X_COLOR_BLACK;
	bank[1] = X_COLOR_BLUE;
	bank[2] = X_COLOR_CYAN;
	bank[3] = X_COLOR_GOLD;
	bank[4] = X_COLOR_SILVER;
	bank[5] = X_COLOR_LIME;
	bank[6] = X_COLOR_PINK;
	bank[7] = X_COLOR_PURPLE;
	bank[8] = X_COLOR_RED;
	bank[9] = X_COLOR_YELLOW;
	bank[10] = X_COLOR_LIGHT_GRAY;
	bank[11] = X_COLOR_GRAY;
	bank[12] = X_COLOR_DARK_GRAY;
	return (bank);
}
