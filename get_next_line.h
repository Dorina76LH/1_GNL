/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:18:30 by doberes           #+#    #+#             */
/*   Updated: 2024/12/02 10:41:20 by doberes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* *************************** */
/*    Create static library    */
/* *************************** */

#ifndef GNLFT_H
# define GNLFT_H

/* ************************** */
/*         Buffer size        */
/* ************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE
# endif

/* ************************** */
/* List of included libraries */
/* ************************** */

# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <bsd/string.h>

/* *************************** */
/*  List of included .c files  */
/* *************************** */

char    *get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);


#endif
