/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:34:25 by doberes           #+#    #+#             */
/*   Updated: 2024/12/02 11:44:59 by doberes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
  // Variables
  int	fd;
  char	*next_line;
  int	count;

  count = 0;
  fd = open("example.txt", O_RDONLY);
  next_line = get_next_line(fd);
  count++;
  printf("[%d]:%s\n", count, next_line); //count is to show you the line numbers
  next_line = NULL;

  close(fd);
  return (0);
}