/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajulanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:24:48 by ajulanov          #+#    #+#             */
/*   Updated: 2019/04/28 21:52:58 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "fillit.h"

int check_counts(const char *str, const int count)
{

}


// Read tetrimino from file and put them in one array

int 	read_tetri(const int fd, t_etris *tetris)
{
	// buffer array for 22 = allocate 22 bytes, almost strlen + 1 to ensure '\0' is included
	//
	//it is the better implemetation of the 
	//#define BUFSIZE 22
	//char buffer 
	char	buf[22];
	int		count;
	int		i;
	int		j;
	char 	current;

	i = 0;
	current = 'A';
	while ((count = read(fd, buf, 21)) >= 20)
	{
		if (check_counts(buf, count) != 0)
			return (0);
		tetris[i] = get_piece(buf, current++);
		j = i - 1;
		while (j >= 0)
		{
			if (tetris[j].value == tetris[i].value)
				tetris[i].last = tetris + j;
			j--;
		}
		i++;
	}
	if (count != 0)
		return (0);
	return (current - 'A');
}
