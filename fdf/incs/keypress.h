/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 03:08:46 by khanadat          #+#    #+#             */
/*   Updated: 2025/08/06 17:30:15 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYPRESS_H
# define KEYPRESS_H

# include "utils.h"

// linux
// linux_key
# define ESC_KEY    65307          // XK_Escape
# define UP_KEY     65362          // XK_Up
# define DOWN_KEY   65364          // XK_Down
# define RIGHT_KEY  65363          // XK_Right
# define LEFT_KEY   65361          // XK_Left
# define Q_KEY      113            // 'q'
# define E_KEY      101            // 'e'
# define W_KEY      119            // 'w'
# define A_KEY      97             // 'a'
# define S_KEY      115            // 's'
# define D_KEY      100            // 'd'
# define I_KEY      105            // 'i'
# define X_KEY      120            // 'x'
# define Y_KEY      121            // 'y'
# define Z_KEY      122            // 'z'
# define PLUS_KEY   61             // '=' key   (Shift → '+')
# define MINUS_KEY  45             // '-' key   (Shift → '−')
# define COMMA_KEY  44             // ',' key   (Shift → '<')
# define DOT_KEY    46             // '.' key   (Shift → '>')

// macos_key
// # define ESC_KEY 53
// # define UP_KEY 126
// # define DOWN_KEY 125
// # define RIGHT_KEY 124
// # define LEFT_KEY 123
// # define Q_KEY 12
// # define E_KEY 14
// # define W_KEY 13
// # define A_KEY 0
// # define S_KEY 1
// # define D_KEY 2
// # define I_KEY 34
// # define X_KEY 7
// # define Y_KEY 16
// # define Z_KEY 6
// # define PLUS_KEY 24
// # define MINUS_KEY 27
// # define COMMA_KEY 43 // <
// # define DOT_KEY 47 // >

// keypress.c
void	move_camera(int keysym, t_data *data);
void	rotate_camera(int keysym, t_data *data);
void	change_map(int keysym, t_data *data);

#endif