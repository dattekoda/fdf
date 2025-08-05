/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:18:56 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/05 22:30:52 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jikken.h"

void	move_camera(int keysym, t_data *data)
{
	if (keysym == UP_KEY)
		data->move->ud += DELTA_UD;
	else if (keysym == DOWN_KEY)
		data->move->ud -= DELTA_UD;
	else if (keysym == LEFT_KEY)
		data->move->lr += DELTA_LR;
	else if (keysym == RIGHT_KEY)
		data->move->lr -= DELTA_LR;
	else if (keysym == PLUS_KEY)
		data->move->zoom += DELTA_ZOOM;
	else if (keysym == MINUS_KEY && DELTA_ZOOM + 2 < data->move->zoom)
		data->move->zoom -= DELTA_ZOOM;
}

void	rotate_camera(int keysym, t_data *data)
{
	if (keysym == D_KEY)
		data->move->z_theta -= DELTA_THETA;
	else if (keysym == A_KEY)
		data->move->z_theta += DELTA_THETA;
	else if (keysym == W_KEY)
		data->move->y_theta -= DELTA_THETA;
	else if (keysym == S_KEY)
		data->move->y_theta += DELTA_THETA;
	else if (keysym == Q_KEY)
		data->move->x_theta -= DELTA_THETA;
	else if (keysym == E_KEY)
		data->move->x_theta += DELTA_THETA;
	else if (keysym == I_KEY)
		*(data->move) = set_move(data->map);
	else if (keysym == X_KEY)
		data->move->x_theta =0;
	else if (keysym == Y_KEY)
		data->move->y_theta =0;
	else if (keysym == Z_KEY)
		data->move->z_theta =0;
}

void	change_map(int keysym, t_data *data)
{
	if (keysym == DOT_KEY)
		data->move->altitude += DELTA_ALTITUDE;
	else if (keysym == COMMA_KEY && 0.8 < data->move->altitude)
		data->move->altitude -= DELTA_ALTITUDE;
}
