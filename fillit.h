/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:14:54 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/01 02:35:25 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define MINO_SIZE 21
# define USAGE "usage: ./fillit <file>" 
# define ERROR "error"
# include "libft/includes/libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdint.h>

typedef struct		s_mino
{
	char			c;
	uint16_t		mino;
	uint8_t			x;
	uint8_t			y;
	int				last;
}					t_mino;

void				print_map(t_list *list, int size);
void				place_mino(uint16_t map[], t_list *mino);
int					find_spot(uint16_t map[], int size, t_list *mino, int row);
int					fill_map(uint16_t map[], int size, t_list *head);
void				map_main(t_list *head);

#endif
