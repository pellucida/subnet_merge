/*
//	@(#) tree.h
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# if 	!defined(TREE_H) 
# define	TREE_H
# include	"node.h"
typedef	NODE	TREE;

int	tree_Create (TREE** tp);
void	tree_traverse (TREE* t, int (*f)(NODE*, void*), void* args);
void	tree_print (TREE* t, int style);
void	tree_print_prune (TREE* t, int style);


# endif
