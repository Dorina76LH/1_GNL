/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:07:32 by doberes           #+#    #+#             */
/*   Updated: 2024/12/02 11:42:52 by doberes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	// Variables
	int bytes_read;
	char *cup_buffer;

	// Memory allocation
	cup_buffer = ft_calloc(3+1, sizeof(char)); // taille + 1 -> '\0'
	if (cup_buffer == NULL)
		return (NULL);
	
	// What doing
	bytes_read = read(fd, cup_buffer, 3);
	
	// When to stop
	if (bytes_read <= 0)
		return (NULL);
	
	// Return value
	return (cup_buffer);
}