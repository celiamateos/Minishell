/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iarradd.c                                       :+:      :+:    :+:   */
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
int	*ft_iarradd(int array[], int nb)
{
	int	*new_arr;
	int		i;
	int		j;

	if (!array)
	{
		new_arr[1] = nb;
		// return (NULL);
		return (new_arr);
	}
    j = ft_iarrlen(array) + 1;
		printf("Array LEN %d\n", j);
	i = -1;
	while (array[++i])
    	new_arr[i] = array[i];
	new_arr[i++] = nb;
	return (new_arr);
}

// int	main(void)
// {
// 	int array1[3];
// 	int array2[0];
// 	int *array3;
	
//     array1[0] = 11;
//     array1[1] = 12;
//     array1[2] = 13;

// 	int i = -1;
// 	while (array1[++i])
// 		printf("Array 1 %d\n", array1[i]);
// 	i = -1;
// 	array3 = ft_iarradd(array1, 41);
// 	while (array3[++i])
// 		printf("Array 3 %d\n", array3[i]);
// 	i = -1;
// 	// array3 = ft_iarradd(array2, 789);
// 	// while (array3[++i])
// 	// 	printf("Array 32 %d\n", array3[i]);
// 	return (0);

// }