/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:07:32 by doberes           #+#    #+#             */
/*   Updated: 2024/12/16 14:41:29 by doberes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================
// -------------------------------- headers -----------------------------------
// ============================================================================
#include "get_next_line.h"

// ============================================================================
// ---------------------------- get_next_line ---------------------------------
// ============================================================================

// 1. Validate the inputs and test the file descriptor
// 2. Read from fd and append to 'buffer_static'
// 3. Extract 'line' from 'buffer_static'
// 4. Clean 'buffer_static'
// [FD_MAX] c'est le nb de fd - double tableau

char	*get_next_line(int fd)
{
	static char	*buffer_static;
	char		*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buffer_static = read_and_join(fd, buffer_static);
	if (buffer_static == NULL)
		return (NULL);
	line = find_new_line(buffer_static, line);
	if (line == NULL || *line == '\0')
		return (free(buffer_static), buffer_static = NULL, free(line), NULL);
	buffer_static = clean_buffer_static(buffer_static);
	return (line);
}

// ============================================================================
// ------------------------------ read_and_join -------------------------------
// ============================================================================

//	Read buffer_size from fd and append the characters read in 'buffer_static'
//  1. Allocate memory for 'buffer_read'
//	2. Initialise 'buffer_static'
//	3. Loop : read if the return value of read() > 0
//	   Initialize count_char to 1, to ensure entring the loop at least once
//	   If reading error (-1) =>> free buffers and return NULL
//     buffer_tmp = concatenate buffer_static and buffer_read

char	*read_and_join(int fd, char *buffer_static)
{
	char		*buffer_read;
	char		*buffer_tmp;
	ssize_t		count_char;

	buffer_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer_read == NULL)
		return (free(buffer_static), NULL);
	if (!buffer_static)
		buffer_static = ft_substr("", 0, 0);
	count_char = 1;
	while (ft_strchr(buffer_static, '\n') == 0 && count_char > 0)
	{
		count_char = read(fd, buffer_read, BUFFER_SIZE);
		if (count_char == -1)
			return (free(buffer_static), free(buffer_read), NULL);
		buffer_read[count_char] = '\0';
		buffer_tmp = ft_strjoin(buffer_static, buffer_read);
		if (buffer_tmp == NULL)
			return (free(buffer_static), free(buffer_read), NULL);
		free(buffer_static);
		buffer_static = buffer_tmp;
	}
	return (free(buffer_read), buffer_static);
}

// ============================================================================
// ----------------------------- find_new_line ---------------------------------
// ============================================================================

// Check after read(), if there is a new line im buffer_static
// 1. Check for new line ( '\n' or EOF ) in buffer_static 
// 2. Calculate length of new line
// 3. Copy new line in 'line'
// 4. Return line

char	*find_new_line(char *buffer_static, char *line)
{
	int	len_line;

	len_line = 0;
	while (buffer_static[len_line] != '\n' && buffer_static[len_line] != '\0')
		len_line++;
	if (buffer_static[len_line] == '\n')
		len_line++;
	line = ft_substr(buffer_static, 0, len_line);
	if (line == NULL)
		return (NULL);
	return (line);
}

// ============================================================================
// ----------------------------- clean_buffer ---------------------------------
// ============================================================================

// after extracting the line, remove the characters read
// the static_buffer have to contain only the characters not jet extracted
// 1. Find len_extract 
//    - Check length of 'line' in 'buffer_static' (strlen + 1 =>> include '\n')
//    - Check length if 'buffer_static'
//    - len_extract = length_total - len_line
// 2. Clean buffer_static
//    - Copy the content of 'buffer_static' after 'start' in 'buffer_extract'
//    - Free 'buffer_static'
//    - Return 'buffer_extract'
char	*clean_buffer_static(char *buffer_static)
{
	char	*buffer_extract;
	int		len_line;
	int		start;
	int		len_total;
	int		len_extract;

	len_line = 0;
	while (buffer_static[len_line] != '\n' && buffer_static[len_line] != '\0')
		len_line++;
	start = len_line + 1;
	len_total = 0;
	while (buffer_static[len_total] != '\0')
		len_total++;
	len_extract = len_total - start;
	buffer_extract = ft_substr(buffer_static, start, len_extract);
	if (buffer_extract == NULL)
		return (free(buffer_static), NULL);
	free(buffer_static);
	return (buffer_extract);
}
//============================================================================
//--------------------------------- main -------------------------------------
//============================================================================
// gcc -Wall -Werror -Wextra -g -D BUFFER_SIZE=1
// get_next_line.c get_next_line.h get_next_line_utils.c
// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*new_line;
// 	int		count_line = 0;
// 	// Read : File
// 	if (argc == 2)
// 	{
// 		fd = open(argv[1], O_RDONLY);
// 		printf("Read from : %s\n", argv[1]);
// 	}
// 	// Read : stdin
// 	else if (argc == 1)
// 	{
// 		fd = STDIN_FILENO;
// 		printf("Read from : Terminal \n");
// 		printf("Tape texte => EOF =. Ctrl + D : \n");
// 	}
// 	// Loop => read => call get_next_line
// 	// while return of GNL is > 0 >> there is encore something to read
// 	new_line = get_next_line(fd);
// 	while (new_line != NULL)
// 	{
// 		printf("Line #%d : %s\n", ++count_line, new_line);
// 		free(new_line);
// 		new_line = get_next_line(fd);
// 	}
// 	// if new_line == NULL >> end of file
// 	if (new_line == NULL)
// 	{
// 		printf("Line #%d : %s\n", ++count_line, new_line);
// 		printf("----- End of file -----\n");
// 	}
// 	free(new_line);
// 	close(fd);
// 	return (0);
//}
// fichier1.txt
// 11111111111111111111111111111111111111111111111111111111111111111111111
// 22222222222222222222222222222222222222222222222222222222222222222222222
// 33333333333333333333333333333333333333333333333333333333333333333333333
// 44444444444444444444444444444444444444444444444444444444444444444444444
// 55555555555555555555555555555555555555555555555555555555555555555555555
// 66666666666666666666666666666666666666666666666666666666666666666666666
// 77777777777777777777777777777777777777777777777777777777777777777777777
// 88888888888888888888888888888888888888888888888888888888888888888888888
// 99999999999999999999999999999999999999999999999999999999999999999999999
// 00000000000000000000000000000000000000000000000000000000000000000000000
// fichier2.txt
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
// bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
// cccccccccccccccccccccccccccccccccccccccccccccc
// dddddddddddddddddddddddddddddddddddddddddddddd
// eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
// ffffffffffffffffffffffffffffffffffffffffffffff
// gggggggggggggggggggggggggggggggggggggggggggggg
// hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
// iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
// jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
// kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk