/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:12:43 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/01 03:54:16 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>

// TODO: DELETE
#include <stdio.h>
#include <inttypes.h>

/*
 * Generates a new tetromino piece by filling parameters such as char and the mapping of bits,
 * and stores it into node->content.
 */
t_mino		*new_mino(char ch, uint16_t bits)
{
	t_mino	*newmino;

	// Allocate enough memory to store a tetromino in heap
	newmino = (t_mino *)ft_memalloc(sizeof(t_mino));
	// Error check
	if (!newmino)
		return (0);
	// Sets the data for the newmino
	newmino->c = ch;
	newmino->mino = bits;
	newmino->x = 0;
	newmino->y = 0;
	newmino->last = -1;
	return newmino;
}

/*
 * Compares the octet using every valid possibility, then returns it 
 * if it is valid, else returns 0 if input is invalid.
 */ 
uint16_t	validate(uint16_t mino)
{
	// if the result of the bitwise AND operation is zero, then it will shift the bits to the left
	while(!(mino & 0xF000)) // 0xF000 = 1111 0000 0000 0000
		mino = mino << 4;
	// the code runs under this condition if the result of the bitwise AND operation is Zero
	// If a tetromino is not in top left corner, it will move it;
	// FOR EXAMPLE, 0110 0110 0000 0000 turns into 1100 1100 0000 0000
	while(!(mino & 0x8888)) // 0x8888 = 1000 1000 1000 1000
		mino = mino << 1;
	// if a tetromino like 1110 0000 0000 0000 shows up, the the code will run under the ondition.
	if((mino & 0xE000) == 0xE000) // 0xE000 = 1110 0000 0000 0000
		return((mino & 0x1E00) ? mino : 0); // 0x1E00 = 0001 1110 0000 0000
	if ((mino & 0x8880) == 0x8880) // 0x8880 = 1000 1000 1000 0000 
		return ((mino & 0x4448) ? mino : 0); // 0x4448 = 0100 0100 0100 1000
	if ((mino & 0x4C00) == 0x4C00) // 0x4C00 = 0100 1100 0000 0000
		return ((mino & 0xA2C0) ? mino : 0); // 0xA2C0 = 1010 0010 1100 0000
	if (((mino & 0x8400) == 0x8400) && (mino != 0x8640)) // 0x8400 = 1000 0100 0000 0000;
	// 0x8640 = 1000 0110 0100 0000
		return ((mino & 0x31BF) ? 0 : mino); // 0x31BF = 0011 0001 1011 1111
	// This returns the 'L' shaped pieces if that is what they are
	return ((mino == 0x44C0 || mino == 0x2E00) ? mino : 0); // 0x44C0 = 0100 0100 1100 0000
	// 0x2E00 = 0010 1110 0000 0000
}

/*
 * Returns single tetromino converted from String into unsigned 16 bit int
 */
uint16_t	get_mino(char *buf)
{
	uint16_t    mino;
	int			i;
	int			count;

	mino = 0;
	i = 0;
	count = 0;
	// Iterate through the string buffer to check for '\n', '#', '.'
	while(buf[i] != '\0')
	{	
		// if you stumble upon a tetrimino piece piece, '#', the counter goes up.
		if(buf[i] == '#' && ++count)
			// MOST IMPORTANT: where you manipulate a 16 bit unsigned int, based on how the buffer looks like
			mino = mino | (1 << (15 - (i - (i / 5))));
		// the only available option is '\0'. You have reached end of the file
		else if (buf[i] != '.' && buf[i] != '\n')
			return (0);
		// If you are on a newline characterand the next position is not divisible by 5. meaning you are not at end of tetromino.
		else if (buf[i] == '\n' && ((i + 1) % 5 != 0))
			return (0);
		++i; 
	}
	// if the count != 4 or i != 20 (the piece is invalid), return 0. Else pass it into the validate function. 
	return((count != 4 || i != 20) ? 0 : validate(mino));
}

/*
 * create a linked list of the mino from the file, allocate memory for the prev_read characters.
 */
t_list		*create_list(int fd, char *buf, int *prev_read)
{
	t_list		*head;
	t_list		*cur;
	int			count;
	uint16_t	bits;
	int			bytes;

	head = ft_lstnew(0, 0);
	if(!head)
		return 0;
	cur = head;
	count = 0;
	while(count < 26 && (bytes = read(fd, buf, MINO_SIZE)) != 0)
	{
		*prev_read = bytes;
		// Depending on what the state of the buffer is at index 20, assign either a null character or a zero
		// if the buf is equal to '\n' than the line adds a '\0' at the end of the string; if it's not equal to '\n', then we terminate the string
		buf[MINO_SIZE - 1] = (buf[20] == '\n' ? '\0' : 0);
		// Pass the contents of the buffer into get_mino in order to convert from buf into 16-bit representation
		bits = get_mino(buf);
		
		// TODO: DELETE
		// printf("Pre Conversion:\n%s\nPost Conversion: %" PRIu16 "\n", buf, bits);

		// sets the content of address of the list head pointer to a valid 'A-Z' mino based on placement of mino bits.
		cur->content = new_mino('A' + count, bits);
		// Error check: if linked list content or bits are equal to NULL , then return 0.
		if (!cur->content || !bits)
			return (0);
		++count;
		// Set the rest of the parameters for the node, like size and next node within list; iterate list.
		cur->content_size = sizeof(cur->content);
		cur->next = ft_lstnew(0, 0);
		cur = cur->next;
	}
	return head;
}

// TODO: DELETE
/*
void	ft_putlst(t_list *node)
{
	t_list *temp = node;
	while(temp != NULL)
	{
		printf("%" PRIu16 "\n", (uint16_t)node->content->mino);
		temp = temp->next;
	}
}
*/

int		main(int argc, char **argv)
{
	char	*buf;
	int		fd;
	t_list	*head;
	int		prev_read;

	if(argc != 2)
	{
		ft_putendl(USAGE);
		return -1;
	}
	// Creates new empty string in memory of size 22
	buf = ft_strnew(MINO_SIZE + 1); 
	prev_read = 0;
	// Opens a file passed in as argument and assigns new file descriptor.
	fd = open(argv[1], O_RDONLY);
	// Create a new LinkedList
	head = create_list(fd, buf, &prev_read);
	close(fd);
	// Error check for results of linked list function and it the previous tetromino was incorrect
	if (!head || !head->content || prev_read != 20)
	{
		ft_putendl(ERROR);
		return -1;
	}

	// TODO: DELETE
	// ft_putlst(head);

	// create a map of the linked list of the minos; map[16]; from the smallest map to the biggesst one == 16
	// also map_main check if there is no solution - returns an error
	// map_main(head);
	return 0;
}
