/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:34:25 by doberes           #+#    #+#             */
/*   Updated: 2024/12/06 15:34:22 by doberes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // read()
#include <fcntl.h> // open()

int	main(void)
{
	// Variables
	int	  fd;
	char  buffer [256];
	int   chars_read;

	fd = open("fichier.txt", O_RDONLY);

	while ((chars_read = read(fd, buffer, 50)))
	{
		buffer[chars_read] = '\0';
		printf("Buffer : %s\n", buffer);
	}

	//close(fd);
	//return (0);
}