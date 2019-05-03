/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:14:54 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/03 08:09:06 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define MINO_SIZE 21
# define USAGE "usage: ./fillit <file>" 
# define ERROR "error"
# define R(i, cur) ((BITS(cur) & (0xF000 >> (i * 4))) << (i * 4))
# define BITS(cur) (((t_mino *)(cur->content))->mino)
# define CHAR(cur) (((t_mino *)(cur->content))->c)
# define X(cur) (((t_mino *)(cur->content))->x)
# define Y(cur) (((t_mino *)(cur->content))->y)
# define LAST(cur) (((t_mino *)(cur->content))->last)
# define CORD(cur, size) ((Y(cur) * size) + X(cur))
# define XOROR(a, b) ((a ^ b) == (a | b))

# include "libft/includes/libft.h"
# include <string.h>
# include <stdint.h>
// TODO: DELETE
#include <inttypes.h>
#include <stdio.h>

typedef struct		s_mino
{
	char			c;
	uint16_t		mino;
	uint8_t			x;
	uint8_t			y;
	int				last;
}					t_mino;

void				print_map(t_list *list, int size);
void				place_mino(uint16_t *map, t_list *mino);
int					find_spot(uint16_t *map, int size, t_list *mino, int row);
int					fill_map(uint16_t *map, int size, t_list *head);
void				map_main(t_list *head);

#endif
