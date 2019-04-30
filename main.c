/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:12:43 by patrisor          #+#    #+#             */
/*   Updated: 2019/04/30 03:31:13 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>

// TODO: DELETE
#include <stdio.h>

/*
 * Returns the 16-bit tetromino if it is valid, else returns 0 if invalid.
 */ 
uint16_t	validate(uint16_t mino)
{
	// if the result of the bitwise AND operation is zero, then it will shift the bits to the left
	while(!(mino & 0xF000)) // 0xF000 = 1111 0000 0000 0000
		mino = mino << 4;
	// the code runs under this condition if the result of the bitwise AND operation is Zero
	while(!(mino & 0x8888)) // 0x8888 = 1000 1000 1000 1000
		mino = mino << 1;
	// if a tetromino like 1110 0000 0000 0000 shows up, the the code will run under the ondition.
	if((mino & 0xE000) == 0xE000) // 0xE000 = 1110 0000 0000 0000
		return((mino & 0x1E00) ? mino : 0); // 0x1E00 = 0001 1110 0000 0000
	
	return mino;
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
		// TODO: DELETE
		printf("%" PRIu16 "\n", mino);
	
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
		buf[MINO_SIZE - 1] = (buf[20] == '\n' ? '\0' : 0);
		// Pass the contents of the buffer into get_mino
		bits = get_mino(buf);
		
		// DELETE
		ft_putstr(buf);

		++count;

	}
	return head;
}

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


}
