/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doberes <doberes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:16:27 by doberes           #+#    #+#             */
/*   Updated: 2024/12/10 17:36:20 by doberes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================
// --------------------------------- Headers ----------------------------------
// ============================================================================
#include "get_next_line.h"



void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*byte_ptr;
	size_t			i;

	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	byte_ptr = (unsigned char *)ptr;
	i = 0;
	while (i < (count * size))
	{
		byte_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
// ============================================================================
// ------------------------------ ft_strlen -----------------------------------
// ============================================================================

//  ft_strlen : calculates the length of the string pointed by s - excluding
//  the terminating null byte ('\0')- and returns the length

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
// ============================================================================
// ------------------------------ ft_strjoin ----------------------------------
// ============================================================================

//  ft_strjoin : copies in *result : string1 + string2 + '\0 and returns *result
//   - Calculate the length of string1 and string2 (without '\0')
//   - Allocate memory for the copy (total_len = len_str1 + len_str2 + 1 => ('\0))
//   - Copy str1 (without '\0'), str2 (without '\0') and '\0' in result
//   - Return value : result

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i_str1;
	int		i_str2;
	int		len_str1;
	int		len_str2;
	char	*result;

	len_str1 = ft_strlen(s1);
	len_str2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len_str1 + len_str2 +1));
	if (result == NULL)
		return (NULL);
	i_str1 = 0;
	while (i_str1 < len_str1)
	{
		result[i_str1] = s1[i_str1];
		i_str1++;
	}
	i_str2 = 0;
	while (i_str2 < len_str2)
	{
		result[i_str1 + i_str2] = s2[i_str2];
		i_str2++;
	}
	result[i_str1 + i_str2] = '\0';
	return (result);
}

// ============================================================================
// ------------------------------ ft_substr -----------------------------------
// ============================================================================


/*

*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	i;
	char	*extract_str;

	if (s == NULL)
		return (NULL);
	str_len = 0;
	while (s[str_len] != '\0')
		str_len++;
	if (start >= str_len)
		return (ft_calloc(1, sizeof(char)));
	if (start + len > str_len)
		len = str_len - start;
	extract_str = malloc(len + 1);
	if (!extract_str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		extract_str[i] = s[start + i];
		i++;
	}
	extract_str[i] = '\0';
	return (extract_str);
}

// ============================================================================
// ------------------------------ ft_strdup -----------------------------------
// ============================================================================

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (src[length] != '\0')
		length++;
	dest = (char *)malloc(sizeof(char) * (length + 1));
	if (dest == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
// ============================================================================
// ------------------------------ ft_strchr -----------------------------------
// ============================================================================

char	*ft_strchr(const char *s, int c)
{
	unsigned char	unsig_char;

	unsig_char = (unsigned char)c;
	while (*s != '\0' && unsig_char != *s)
		s++;
	if (*s == unsig_char)
		return ((char *)s);
	return (0);
}

/*
	utils
	ft_strchr => trouver '\n' et '\0'
	ft_strlen => longueur chaine de caractere
	ft_substr => extraction sous-chaine
	ft_strjoin => concatener deux chaines

	GNL
	get_next_line
	read_and_join
	find_next_line
	clean_buffer_static
*/



