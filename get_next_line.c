/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:07:32 by doberes           #+#    #+#             */
/*   Updated: 2024/12/09 17:16:54 by doberes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================
// -------------------------------- headers -----------------------------------
// ============================================================================

#include "get_next_line.h"

// ============================================================================
// ---------------------------- get_next_line ---------------------------------
// ============================================================================

char	*get_next_line(int fd)
{
	// Variables
	static char	*static_buffer; // [FD_MAX] c'est le nb de fd - double tableau
	size_t		count_char;
	char		*line;

	// fd only positive | read test -> read returns -1 if problem on reading
	if (fd < 0 || fd > 1023, BUFFER_SIZE <= 0 || read(fd, &line , 0) < 0)
		return (NULL);
	
	count_char = 1; // initialise a 1 pour pouvoir entrer dans le boucle
	line = NULL;
	
	// 1. read from fd and add to static_buffer
	read_and_add_to_buffer(fd, &static_buffer, &count_char);
	// si le fichier est vide
	if (static_buffer == NULL)
		return (NULL);
	
	
	
	// 2. extract line from concatened_buffer
	// 3. celan un concatened_buffer

	return (line);
}

// ============================================================================
// ---------------------- read_fd_and_add_to_static_buffer --------------------
// ============================================================================

// uses read() to add characters to the static buffer


void read_and_add_to_buffer(int fd, **ptr_static_buffer, size_t *ptr_count_char)
{
	 // Variables
	 char	*buffer;

	 // Allocation memoire pour la copie et ctrl de l'allocation
	 buffer= malloc(sizeof(char) * (BUFFER_SIZE + 1));
	 if (buffer == NULL)
	 	return; // pas de valeur de retour car fonction void

	// Lire fd, affecter le contenu au buffer et ajouter le '\0'
	
	// boucle pas de new line et pas de problem de lecture
	*ptr_count_char = read(fd, buffer, BUFFER_SIZE); // buffer rempli avec buffer_size
	// gerer les anomalies de lecture
	buffer[*ptr_count_char] = '\0';
}

// ============================================================================
// ----------------------------- add_to_stash ---------------------------------
// ============================================================================

// adds the content of the buffer to the stash

void add_to_stash()
{

}

// ============================================================================
// ----------------------------- extract_line ---------------------------------
// ============================================================================

// extract all charcaters from the "stash" and stores them in "line", stopping
// after the first '\n' it encounters

void extract_stash()
{

}

// ============================================================================
// ----------------------------- clean_stash ----------------------------------
// ============================================================================

// after extracting the line, we need to remove from stash the characters read
// the static stash have to contain only the characters not jet extracted 

void clean_stash()
{

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
*/

int	main(int argc, char **argv)
{
	// Variable declaration
	int		fd;
	int		count_line;
	int		return_value;
	char	*buffer;

	// Variable initialisation
	count_line = 0;

	// when argc == 2
	if (argc == 2)
	{
		// read the file line by line, while return_value of get_next_line is > 0
		while ((return_value = get_next_line(fd, &buffer))>0)
		
		// open the file - read only
		fd = open(argv[1], O_RDONLY);
		while (1)
		{
			line = get_next_line(fd);
			if (line == NULL)
			break;
			printf("%s", line);
			free(line);
		}
	}
	return (0);
}

/* Get_next_line
1) lire le fichier recu via le fd avec read
   read (buffer size doit etre definie dans main)
2) read va :
	- stocker se qui a ete lu dans le buffer
	- retourne le nb de caracteres lus
	- buffer est ecrase a chaque appel de read
3) stash (static)
	- stocker le contenu du buffer dans stash (reserve)
	- stash doit etre static pour que le contenu ne soit pas reinitialise a chaque appel
4) verifier le contenu de stash (recherche)
	- si '/n' -> ligne entiere a ete lue -> extraire la ligne et nettoyer stash
	- si par de '/n' -> nouvelle appelle a read
5) Copier la ligne trouvee dans line
    - extraire les caracteres + '\n'
	- les stocker dans line -> copy
6) Nettoyer stash
    - enlever le contenu line
	- garder que le contenu restant lu
7) Appel a get next line tant que read ne renvoie pas -1
*/

// controler aussi fd >= 0