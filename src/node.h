/*
//	@(#) node.c
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# if	!defined(NODE_H)
# define	NODE_H

# include	<stdio.h>
# include	"netaddr.h"

enum	{
	N_Z	= 0,
	N_U	= 1,
};
enum	{
	PRN_DEBUG	= 1,
	PRN_PRUNE	= 0,
};

enum	{
	A_NONE		= '.',
	A_ADDED		= 'E',
	A_COMBINE	= 'C',
};

typedef	struct	node	NODE;	/* OPAQUE */
/*
struct	node	{
	NODE*	sub[2];
	haddr_t	adr;
	unsigned char	level;
	unsigned char	status;
};
*/

int	node_Create (NODE** np, haddr_t adr, int level);
int	node_Delete (NODE** np);
int	node_setstatus (NODE* n, int status);
int	node_status (NODE* n);
int	node_setstatus (NODE* n, int status);
NODE*	node_subtree (NODE* n, int dir);
int	node_setsubtree (NODE* t, int dir, NODE* n);
int	node_level (NODE* n);
int	node_print (NODE* n, FILE* output, int debug, int style);

# endif
