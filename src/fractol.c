/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:43:53 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 17:24:46 by sgoldenb         ###   ########.fr       */
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
	ft_printf(YELLOW BOLD"Fractales: mandelbrot, julia\n" RESET);
	(ft_arrfree((void **)known_fractals), free(known_fractals));
	return (FALSE);
}

void	print_controls(void)
{
	ft_printf(GREEN BOLD"////FRACTOL////\n"RESET);
	ft_printf(BOLD"\tX / Y moves :\t\t\t ARROWS\n");
	ft_printf("\tZ moves :\t\t\t W / S / MOUSE WHEEL\n");
	ft_printf("\tSwitch Mandelbrot/Julia :\t M / J\n");
	ft_printf("\tSwitch colors front/back :\t F / B\n");
	ft_printf("\tReset view :\t\t\t R\n");
	ft_printf("Clean exit :\t\t\t\t ESC / Window button\n");
}

int	main(int argc, char **argv)
{
	t_fractol	*data;

	if (argc != 2)
		(ft_printf(ITALIC RED "./fractol [nom_de_la_fractale]\n"
				RESET), exit(EINVAL));
	data = (t_fractol *)malloc(sizeof(t_fractol));
	if (!data)
		return (print_error("fractol", errno));
	if (init_data(data) == FALSE)
		return (print_error("fractol", errno));
	if (name_check(argv[1]) == FALSE)
		(ft_printf(ITALIC RED "./fractol [nom_de_la_fractale]\n"
				RESET), free(data), exit(EINVAL));
	data->fract_id = name_to_id(argv[1]);
	data->color_smooth = 4;
	print_controls();
	start_mlx(data);
	draw(data);
	mlx_hook(data->win_ptr, EVENT_CLOSE_BTN, 0, close_by_btn, data);
	mlx_mouse_hook(data->win_ptr, mouse_hooks, data);
	mlx_key_hook(data->win_ptr, key_hooks, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
