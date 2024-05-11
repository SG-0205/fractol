/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:30:27 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 15:41:54 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "colors.h"
# include "keycodes.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/keysymdef.h>
# include <math.h>

# define FID_MANDELBROT 1
# define FID_JULIA 2
# define FID_J_RABBIT 21
# define FID_J_SEAHORSE 22
# define FID_J_SPIRALS 23
# define FID_J_SYMHOR 24
# define FID_J_SYMVERT 25
# define FID_J_CREMER 26
# define FID_J_LEAF 27
# define FID_J_BURNING_S 28
# define FID_J_DISC 29

# define WIN_W 1000
# define WIN_H 1000

# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4
# define IN 5
# define OUT 6

# define PRECISION 300

typedef struct s_fractol
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		win_w;
	int		win_h;
	int		zoom_factor;
	int		color_front;
	int		color_back;
	int		*color_bank;
	int		*color_buff;
	int		color_smooth;
	int		fract_id;
	int		julia_id;
	double	fract_mxr;
	double	fract_mr;
	double	fract_mxi;
	double	fract_mi;
	double	fract_fx;
	double	fract_sx;
	double	fract_rx;
	double	fract_kr;
	double	fract_ki;
}			t_fractol;

int			print_error(char *source, int error);
int			name_to_id(char *name);
t_bool		name_check(char *input);
t_bool		init_data(t_fractol *data);
void		clear_data(t_fractol *data, char *err_src, int error);
void		draw(t_fractol *data);
void		config_by_id(t_fractol *data);
int			close_by_btn(t_fractol *data);
void		print_coordinates(t_fractol *data);
int			clear_data_wrap(t_fractol *data);
int			key_hooks(int code, t_fractol *data);
void		update_julia(t_fractol *data);
int			mandelbrot(double real, double imaginary);
int			julia(double z_real, double z_imaginary, t_fractol *data);
void		update_xy(t_fractol *data, int side, double len);
void		update_z(t_fractol *data, double len, int code);
void		set_colors(t_fractol *data, int background, int front);
void		write_colors(int *container, int nb_colors, t_fractol *data);
int			split_colors(int start, int end, double coef);
void		start_mlx(t_fractol *data);
void		new_image(t_fractol *data);
int			*create_color_bank(void);
double		get_absval(double number);
void		reset_view(t_fractol *data);
void		update_starting_point(t_fractol *data);
void		update_colors(t_fractol *data, int key);
void		update_julia(t_fractol *data);
int			mouse_hooks(int code, int x, int y, t_fractol *data);

#endif