/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 20:12:43 by patrisor          #+#    #+#             */
/*   Updated: 2019/04/30 00:01:03 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>



t_list		*create_list(int fd, char *buf, int *prev_read)
{
	t_list		*head;
	t_list		*cur;
	int			count;
	t_uint16	bits;
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
