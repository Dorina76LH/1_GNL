/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:07:32 by doberes           #+#    #+#             */
/*   Updated: 2024/12/05 17:31:06 by doberes          ###   ########.fr       */
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
/*
Get_next_line
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