/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:07:32 by doberes           #+#    #+#             */
/*   Updated: 2024/12/12 15:29:16 by doberes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================
// -------------------------------- headers -----------------------------------
// ============================================================================
#include "get_next_line.h"

// ============================================================================
// ---------------------------- get_next_line ---------------------------------
// ============================================================================

// 0. Validate the inputs and test the file descriptor
// 1. Read from fd and append to 'buffer_static'
// 2. Extract 'line' from 'buffer_static'
// 3. Clean 'buffer_static'
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

//	read the fd and add characters to the static buffer and add '\0'
//		count_char : return the number of chars read to get_next_line
//		static_buffer : pour emplier les caracteres lus
//		

char	*read_and_join(int fd, char *buffer_static)
{
	char		*buffer_read;
	char		*buffer_tmp;
	ssize_t		count_char;

	// Allocate memory for the read buffer
	buffer_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer_read == NULL)
		return (free(buffer_static), NULL);
	// Initialise static buffer if it's NULL
	if (!buffer_static)
		buffer_static = ft_substr("", 0, 0);
	// boucle pour lire tant que la valeur de retour est zero (pas '\n' trouve)
	count_char = 1; // rentrer au moins une fois dans le boucle
	while (ft_strchr(buffer_static, '\n') == 0 && count_char > 0)
	{
		count_char = read(fd, buffer_read, BUFFER_SIZE); // buffer rempli avec buffer_size
		if (count_char == -1) // gestion erreur de lecture read()
			return (free(buffer_static), free(buffer_read), NULL);
		buffer_read[count_char] = '\0';
		// concatener buffer static et buffer read
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

// extract all charcaters from the 'static_buffer' and copy them in 'line',
// stopping after the first '\n' found

char	*find_new_line(char *buffer_static, char *line)
{
	int	len_line;

	// find length of new line
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

// after extracting the line, we need to remove the characters read
// the static_buffer have to contain only the characters not jet extracted 

char	*clean_buffer_static(char *buffer_static)
{
	char	*buffer_extract;
	int		len_line;
	int		start;
	int		len_total;
	int		len_extract;

	// find length of line
	len_line = 0;
	while (buffer_static[len_line] != '\n' && buffer_static[len_line] != '\0')
		len_line++;
	// start after '\n'
	start = len_line + 1;
	// find lenght of buffer_static
	len_total = 0;
	while (buffer_static[len_total] != '\0')
		len_total++;
	len_extract = len_total - start;
	// copier chaine apres 'n' dans le varaible temp
	buffer_extract = ft_substr(buffer_static, start, len_extract);
	if (buffer_extract == NULL)
		return (free(buffer_static), NULL);
	// reassigner buffer_tmp a buffer static
	free(buffer_static);
	return (buffer_extract);
}
// ============================================================================
// --------------------------------- main -------------------------------------
// ============================================================================

/*
	fd : descripteur de fichier
	return_value : valeur de retour de la fonction get_next_line
		- si > 0   => une ligne a ete lue avec succes
		- si == 0  => fin du fichier
		- si == -1 => erreur
	count_line : compte le nb de lignes lues
	*buffer : ptr qui contiendra la chaine retournee par get_next_line

	argc == 2 : un seul argument fourni au programme -> nom du fichier a lire

	get_next_line alloue de la memoire dynamique pour buffer et le reutilise
	a chaque appel => il faut liberer buffer apres l'avoir utilise (printf)
	pourquoi apres printf ? car tant qu'on n'a pas encore affiche le contenu,
	nous avons besoin de la memoire pointee par le buffer
*/

// int	main(int argc, char **argv)
// {
// 	// Variable declaration
// 	int		fd;
// 	char	*new_line;
// 	int		count_line;

// 	// Variable initialisation
// 	count_line = 0;

// 	// when argc == 2
// 	if (argc == 2)
// 	{
// 		// open the file >> read only
// 		fd = open(argv[1], O_RDONLY);
// 		// read the file line by line, while return_value of GNL is > 0
// 		// there is encore something to read
// 		new_line = get_next_line(fd);
// 		while (new_line != NULL)
// 		{
// 			printf("Line #%d : %s\n", ++count_line, new_line);
// 			free(new_line);
// 			new_line = get_next_line(fd);
// 		}
// 		if (new_line == NULL)
// 		{
// 			printf("Line #%d : %s\n", ++count_line, new_line);
// 		 	printf("----- End of file -----\n");
// 		}
// 		free(new_line);
// 		close(fd);
// 	}
// 	// when argc == 1
// 	// read from stdin - tape by user
// 	// if (argc == 1)
// 	// {
// 	// 	while ((return_value = get_next_line(fd, &buffer))>0)
// 	// 	{
// 	// 		printf("[Return : %d] Line #%d : %s\n", ++line, buffer);
// 	// 	}
// 	// 	// special cases : last line, reading error, end of file
// 	// 	// print last line after the loop (line = return value of GNL)
// 	// 	printf("[Return : %d] Line #%d : %s\n", return_value, ++line, buffer);
// 	// 	if (return_value == -1)
// 	// 		printf("----- Reading error -----\n");
// 	// 	else if (retu == 0)
// 	// 		printf("----- End of stdin -----\n");
// 	//	close(fd);
// 	//}
// 	return (0);
// }

/* 
------------------------------------------
0) Main
------------------------------------------
	- controle le nb des arguments recus en parametre
	- ouvre le fd
	- appels successifs a get_next_line tant que return_value >0
	  si return_value > 0 => il y a du contenu a lire
	- imprime les lignes une par une dans la boucle while
	- imprime la derniere ligne traitee apres la boucle while
	- gestion des cas specifiques : erreur de lecture et fin de fichier 

------------------------------------------
1) Get_next_line
------------------------------------------
1) lire le fichier recu via le fd avec read
   read (buffer size doit etre definie dans main)
2) read va :
	- stocker se qui a ete lu dans le buffer
	- retourne le nb de caracteres lus
	- buffer est ecrase a chaque appel de read
3) stash (static)
	- stocker le contenu du buffer dans stash (reserve)
	- stash doit etre static pour que le contenu ne soit pas reinitialise
	  a chaque appel


------------------------------------------
2) read_and_join
------------------------------------------
	- read fd
	- copier le contenu du buffer_read dans le buffer_static (calloc + strjoin)

------------------------------------------
3) find_new_line
------------------------------------------
    - verifier le contenu du buffer statique
	- booleen => valeur de retour est 1 si '\n' trouve et 0 si pas de '\n'
	- si '\n' trouve => ligne a imprimer
		- copier le contenu du buffer statique dans line (yc \n)
		- return (line)
	- si pas de '\n  => continuer la lecture et le remplissage du buffer statique

------------------------------------------
4) Clean_static_buffer
------------------------------------------
    - chercher '\n' dans le buffer statique
	- copier les caracteres apres \n dans le buffer temporaire
	- (calloc) reinitaliser le buffer statique
	- copier le contenu du buffer temporaire dans le buffer statique

7) Appel a get next line tant que read ne renvoie pas -1
*/

// controler aussi fd >= 0