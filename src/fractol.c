/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:43:53 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/17 17:50:07 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_bool	name_check(char *input)
{
	char	*fract_ok;
	char	**known_fractals;
	int		i;

	i = -1;
	fract_ok = "mandelbrot,julia";
	known_fractals = ft_split(fract_ok, ',');
	if (!known_fractals)
		(ft_printf("name_check : %s\n", strerror(errno)), exit(errno));
	while (known_fractals[++i])
	{
		if (ft_strcmp(known_fractals[i], input) == 0)
		{
			(ft_arrfree((void **)known_fractals), free(known_fractals));
			return (TRUE);
		}
	}
	(ft_arrfree((void **)known_fractals), free(known_fractals));
	return (FALSE);
}

int	ingest_lsd(char *blotter_nb)
{
	int	blotter_count;

	blotter_count = ft_atoi(blotter_nb);
	if (blotter_count < 0 || blotter_count > 4)
		return (4);
	else
		return (blotter_count);
}

int	main(int argc, char **argv)
{
	t_fractol	*data;

	if (argc != 3)
		(ft_printf(ITALIC RED "./fractol [nom_de_la_fractale] [lsd 0-4]\n" 
				RESET), exit(EINVAL));
	data = (t_fractol *)malloc(sizeof(t_fractol));
	if (!data)
		return (print_error("fractol", errno));
	if (init_data(data) == FALSE)
		return (print_error("fractol", errno));
	if (name_check(argv[1]) == FALSE)
		(print_error("fractol", errno), exit(errno));
	data->fract_id = name_to_id(argv[1]);
	data->color_smooth = ingest_lsd(argv[2]);
	start_mlx(data);
	draw(data);
	mlx_hook(data->win_ptr, EVENT_CLOSE_BTN, 0, close_by_btn, data);
	mlx_key_hook(data->win_ptr, key_hooks, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
