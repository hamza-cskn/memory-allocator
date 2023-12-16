/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aborter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:14:08 by hamza             #+#    #+#             */
/*   Updated: 2023/12/16 15:15:19 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator.h"
#include <stdlib.h>

/*
	Frees all memory blocks which allocated by using safe_malloc
	function.
*/
void	abort_memory(void)
{
	memory_block	*memory_blocks;
	memory_block	*next;

	register_pre_abort_func(NULL);
	memory_blocks = get_memory_blocks()->next;
	while (memory_blocks != NULL)
	{
		next = memory_blocks->next;
		FREE_MEMORY(memory_blocks->ptr);
		FREE_MEMORY(memory_blocks);
		memory_blocks = next;
	}
	get_memory_blocks()->next = NULL;
	register_post_abort_func(NULL);
}

/*
	Registers abort function to call before when abort_memory
	function is called.
*/
void	register_pre_abort_func(void (*abort_func)(void))
{
	static void	(*func)(void) = NULL;

	if (abort_func != NULL)
		func = abort_func;
	else if (func != NULL)
		func();
}

/*
	Registers abort function to call after when abort_memory
	function is called.
*/
void	register_post_abort_func(void (*abort_func)(void))
{
	static void	(*func)(void) = NULL;

	if (abort_func != NULL)
		func = abort_func;
	else if (func != NULL)
		func();
}
