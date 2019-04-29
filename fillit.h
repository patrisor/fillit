/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:14:54 by patrisor          #+#    #+#             */
/*   Updated: 2019/04/28 20:15:36 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define MAX_TETRI 26
# include <string.h>
# include <stdint.h>

typedef struct s_etris	t_etris;

struct				s_etris
{
	uint64_t			value;
	t_etris				*last;
	unsigned char		id;
	unsigned char		x;
	unsigned char		y;
	unsigned char		width;
	unsigned char		height;
};

int					read_tetri(const int fd, t_etris *tetris);
int					solve(t_etris *tetris, const int count, uint16_t *map);
int					check_piece(const t_etris *tetris, uint16_t *map);
void				toggle_piece(const t_etris *tetris, uint16_t *map);

#endif
