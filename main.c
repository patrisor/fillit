/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:12:43 by patrisor          #+#    #+#             */
/*   Updated: 2019/04/29 04:13:24 by ajulanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"
#include <fcntl.h>

// 

t_mino		*new_mino(char ch, t_uint16 bits)
{
	t_mino	*newmino;

	newmino = (t_mino *)ft_memalloc(sizeof(t_mino));
	if (!newmino)
		return (0);
	newmino->c = ch;
	newmino->mino = bits;
	newmino->x = 0;
	newmino->y = 0;
	newmino ->last = -1;
	return (newmino);
}

t_uint16		validate(t_uint16 mino)
{
	while (!(mino & 0xF000))
		mino = mino << 4;
	while (!(mino & 0x8888))
		mino = mino << 1;
	if ((mino & 0xE000) == 0xE000)
		return ((mino & 0x1E00) ? mino : 0);
	if ((mino & 0x8880) == 0x8880)
		return ((mino & 0x4448) ? mino : 0);
	if ((mino & 0x4C00) == 0x4C00)
		return ((mino & 0xA2C0) ? mino :0);
	if (((mino & 0x8400) == 0x8400) && (mino != 0x8640))
		return ((mino & 0x31BF) ? 0 : mino);
	return ((mino == 0x44C0 || mino == 0x2E00) ? mino : 0);
}

t_uint16		get_mino(char *buf)
{
	t_uint16	mino;
	int			i;
	int			count;

	mino = 0;
	i = 0;
	count = 0;
	while (buf[i])
	{
		if (buf[i] == '#' && ++count)
			mino |= (1 << (15 - (i - (i/5))));
		else if (buf[i] != '.' && buf[i] != '\n')
			return (0);
		else if (buf[i] == '\n' && ((i + 1) % 5 != 0))
			return (0);
		++i;
	}
	return ((count != 4 || i != 20) ? 0 : validate(mino));
}

//create a linked list of the mino from the file, allocate memory for the prev_read characters.
t_list			*create_list(int fd, char *buf, int *prev_read)
{
	t_list		*head; //read list
	t_list		*cur; //current list
	int			count; //???to mark the minos with the letters A-Z, 26 letters
	t_uint16	bits;
	int 		bytes;

	head = ft_lstnew(0, 0); 
	if (!head) // 
		return (0);
	cur = head; // cope head to the current list
	count = 0;
	// check that the file does not contain > 26 or less that 1 mino;
	while (count < 26 && (bytes = read(fd, buf, MINO_SIZE)) != 0)
	{
		*prev_read = bytes; // how many bytes we have read??? 20?
		// if 21 char from the buf is equal '\n' than the line ads '\0' at the end of the string, not an '\n'; we terminate the string
		buf[MINO_SIZE - 1] = (buf[20] == '\n' ? '\0' : 0);
		// convert minos in bits
		bits = get_mino(buf);
		//link current list to the content struct; 
		cur->content = new_mino('A' + count, bits);
		// error check
		if (!cur->content || !bits)
			return (0);
		// 
		++count;
		cur->content_size = sizeof(cur->content);
		//create new current list
		cur->next = ft_lstnew( 0, 0);
		// current list that contain copy of the head list and marked minos
		cur = cur->next;
	}
	return (head);
}

int				main(int ac, char **av)
{
	char	*buf; // new string
	int		fd;   // file with the minos
	t_list *head; // linked list with the minos
	int prev_read; // prev_read == (bytes = read(fd, buf, MINO_SIZE)), 20

	// print "usage" message for user, if there is no right command
	if (ac != 2) 
	{
		ft_putendl("usage: ./fillit <file>");
		return (0);
	}
	
	// create a string take a file, open, read, gets the mino and returns them in a linked list 
	buf = ft_strnew(MINO_SIZE + 1); 
	// MINO_SIZE = 21 =  4 rows * 5 character (4 char + \n + 1 char for \0)
	// allocate memory for the string = MINO_SIZE + 1
	prev_read = 0;
	// start reading minos from the 0 in order char??? 
	fd = open(av[1], O_RDONLY);
	// open and read the file
	head = create_list(fd, buf, &prev_read);
	// create a linked list of the mino
	close(fd);
	//close file
	if (!head || !head->content || prev_read != 20)
		// if there is no linked list OR the list is empty OR ??? we didnt read 20 char from the file
	{
		ft_putendl("error"); // print an error
		return (0);
	}
	// create a map of the linked list of the minos; map[16]; from the smallest map to the biggesst one == 16 
	// also map_main check if there is no solution - returns an error
	map_main(head); 
	return (0);
}
