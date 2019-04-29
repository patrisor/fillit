/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:14:54 by patrisor          #+#    #+#             */
/*   Updated: 2019/04/28 23:12:10 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define MAX_TETRI 26
# include <string.h>
# include <stdint.h>

#define MINO_SIZE 21
#define R(i, cur) ((BITS(cur) & (0xF000 >> (i * 4))) << (i * 4))
#define BITS(cur) (((t_mino *)(cur->content))->mino)
#define CHAR(cur) (((t_mino *)(cur->content))->c)
#define X(cur) (((t_mino *)(cur->content))->x)
#define Y(cur) (((t_mino *)(cur->content))->y)
#define LAST(cur) (((t_mino *)(cur->content))->last)
#define CORD(cur, size) ((Y(cur) * size) + X(cur))
#define XOROR(a,b) ((a ^ b) == (a | b))

typedef struct	s_mino
{
	char			c;
	t_uint64		value;
	t_uint16		tetrimino;
	t_uint8			x;
	t_uint8			y;
	int				last	;
} 						t_mino;

void				print_map(t_list *list, int size);
void				place_mino(t_uint16 map[], t_list *mino);
int					find_spot(t_uint16 map[], int size, t_list * mino, int row);
void				map_main(t_list *head);

#endif
