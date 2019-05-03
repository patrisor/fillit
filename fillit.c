/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 03:18:36 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/03 07:16:41 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Apply a character to a placement of a bitwise tetrominoi by first counting the bits
 */
void	print_map(t_list *list, int size)
{
	char	*s;
	int		row;
	int		i;

	// initialize a string with a given character, '.', to a given length, size, 
	// enough to build your graph
	s = ft_strinit(sizeof(char) * size * (size + 1), '.');
	row = size;
	// Stringbuilding -> the last character of the string is a null pointer
	s[((size + 1) * row) - 1] = '\0';
	while(--row)
		// Traverse down the list in order to place a new line character on the graph
		s[((size + 1) * row) - 1] = '\n';
	while(list->content) // While the tetrominoes exist within each node withn linked list
	{
		row = 0;
		i = 16;
		while(i--)
		{
			// if the tetromino after the shift and mask is equal to 0000 0000 0000 0001,
			if((BITS(list) >> i) & 0x0001)
				// then go through the rows and columns of the graph to place a character there.
				s[(Y(list) + row) * (size + 1) + X(list) + ((15 - i) % 4)] = CHAR(list);
			// If you are at the end of the row, go to the next one
			if((16 - i) % 4 == 0)
				++row;
		}
		list = list->next; // Traverses linked list 
	}
	// Put end line at the end of string
	 ft_putendl(s);
}

/*
 *
 */
void	place_mino(uint16_t *map, t_list *mino)
{
	int		i;

	i = -1;
	// Go down to correct row
	map += Y(mino);
	// Mask the address of the empty map
	// Choose column for which to place a mino?
	while(++i < 4)
		// TODO: 
		*map++ ^= R(i, mino) >> X(mino);
}

/*
 * Backtracking?
 */
int		find_spot(uint16_t *map, int size, t_list *mino, int row)
{
	// Return error code if map was empty OR the y coordinate of mino is greater than size
	// AND check if the bits of the mino are in the top left corner
	// R will never even get to that point because we are applying an AND mask to 0xF000
	if(!map || (((Y(mino) + row) >= size) && (R(row, mino) > 0)))
		return -1;
	// If you are on the current mino, iterate forward one column; iterate to change the
	// x-position of mino
	if(LAST(mino) == CORD(mino, size))
		++X(mino);
	// The condition is saying: once you apply a mask on the top row and it comes you positive, 
	// you will apply a shift from top right position to next row, first column.
	if(X(mino) >= (size - 3) && (BITS(mino) & (0x1111 << ((X(mino) - (size - 3))))))
	{
		++Y(mino); // Iterate row down
		X(mino) = 0; // Go to first column
		return(find_spot(map, size, mino, 0)); // Use recursion to backtrack and go through the same cycle
	}
	if(row == 0) // If you are on first row
	{
		// TODO: If the tetromino does not fit
		if(XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))))
			if(find_spot(map + 1, size, mino, row + 1)) // if this returns positive, 
				return(find_spot(map + 1, size, mino, row + 1)); // then keep going that way
		++X(mino); // Iterate to the next row and try again
		return (find_spot(map, size, mino, row)); 
	}
	// TODO: 
	if (row < 3 && XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))))
		return (find_spot(map + 1, size, mino, row + 1));
	else
		return (XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))));
	// If all else fails, tetrominoes do not fit?
}

/*
 * Based on how many tetrominoes thre are, create a map of a partivular size which will fit all of them in
 */
int		fill_map(uint16_t *map, int size, t_list *head)
{
	int		fit;

	// if the content is empty, it will return 1
	if(!head->content)
		return 1;
	// Points to last in the structure
	LAST(head) = -1;
	// Points to the Y coordinate of structure (uint8_t)
	Y(head) = 0;
	// Points to the X coordinate of structure (uint8_t)
	X(head) = 0;
	// TODO: Returns a number 1 if it fits, if not, it returns something else
	fit = find_spot(map, size, head, 0);
	while(fit == 1)
	{
		// TODO: set the last number as the current
		LAST(head) = CORD(head, size);
		// TODO: 
		place_mino(map, head);
		// Uses recursion to keep on filling the pieces to the map??
		if(fill_map(map, size, head->next))
			return 1;
		place_mino(map, head);
		fit = find_spot(map, size, head, 0);
	}
	return 0;
}

// DELETE: Function used for testing contents of the list
void	ft_putlst(t_list *head)
{
	while(head != NULL && head->content != NULL)
	{
		printf("%hu\n", ((t_mino *)(head->content))->mino);
		head = head->next;
	}
}

void	map_main(t_list *head)
{
	uint16_t		map[16]; // Create a bit map of size 16 (size of tetromino piece)
	int			count;
	int			size;

	ft_bzero(map, sizeof(uint16_t) * 16); // allocate big enough chunk of memory for bitmap
	count = ft_lstlen(head); // Every tetromino piece equates to one node in linked list of memory
	size = 2;
	// build a graph big enough to fit all tetrominoes
	// size * size is the area of our graph (2x2, 4x4, etc.)
	while(size * size < count * 4)
		++size;
	while(size <= 16)
	{
		// if the function returns zero, it will keep iterating size of the graph
		if(!fill_map(map, size, head))
			++size;
		else
			break ;
	}
	if(size > 16)
		ft_putendl(ERROR);
	print_map(head, size);
}
