/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarradd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:11:28 by daviles-          #+#    #+#             */
/*   Updated: 2023/04/01 18:41:33 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

//@brief add a string to the provided array. 
//I array is null, creates a new one, add the string and return it.
char	**ft_sarradd(char **array, char *str)
{
	char	**new_arr;
	int		i;

	if (!array)
	{
		new_arr = (char **) malloc (2 * sizeof(char *));
		if (!new_arr)
			return (NULL);
		new_arr[0] = str;
		new_arr[1] = NULL;
		return (new_arr);
	}
	new_arr = (char **) malloc (ft_sarrlen(array) + 2 * sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = -1;
	while (array[++i])
		new_arr[i] = ft_strdup(array[i]);
	new_arr[i++] = ft_strdup(str);
	new_arr[i] = NULL;
	return (new_arr);
}

/*int	main(void)
{
	char **array1;
	char **array2;
	char **array3;
	
	array1 = (char **) malloc (2 * sizeof(char *));
	array1[0] = ft_strdup("Hola que tal");
	array1[1] = NULL;
	array2 = (char **) malloc (1 * sizeof(char *));
	array2 = NULL;
	array3 = NULL;
	int i = -1;
	while (array1[++i])
		printf("Array 1 %s\n", array1[i]);
	i = -1;
	array3 = ft_sarradd(array1, "LALALALAL");
	while (array3[++i])
		printf("Array 3 %s\n", array3[i]);
	i = -1;
	array3 = ft_sarradd(array2, "LALALALAL");
	while (array3[++i])
		printf("Array 32 %s\n", array3[i]);
	return (0);

}*/