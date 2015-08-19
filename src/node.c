/*
//	@(#) node.c
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# include	<stdio.h>
# include	<stdlib.h>
# include	"constants.h"
# include	"netaddr.h"
# include	"node.h"

struct	node	{
	NODE*	sub[2];
	haddr_t	adr;
	unsigned char	level;
	unsigned char	status;
};
/*
// While the level and adr are implicit in node's position in
// the tree, recording these in the node save passing information
// up and down during a tree walk.
*/
int	node_Create (NODE** np, haddr_t adr, int level) {
	int	result	= err;
	NODE*	n	= malloc (sizeof(*n));
	if (n) {
		n->status	= A_NONE;
		n->level	= level;
		n->adr		= adr&netmask(level);
		n->sub[N_Z]	= 0;
		n->sub[N_U]	= 0;
		*np		= n;
		result		= ok;
	}
	return	result;
}
int	node_Delete (NODE**	np) {
	if (np) {
		NODE*	n	= *np;
		if (n) {
			*np	= 0;
			n->level	= 0;
			n->adr		= 0;
			n->sub[N_Z]	= 0;
			n->sub[N_U]	= 0;
			free (n);
		}
	}
	return	true;

}
NODE*	node_subtree (NODE* n, int dir) {
	NODE*	result	= 0;
	if (n) {
		result	= n->sub[dir];
	}
	return	result;
}
int	node_setsubtree (NODE* t, int dir, NODE* n) {
	t->sub [dir]	= n;
}
int	node_setstatus (NODE* n, int status) {
	int	result	= err;
	if (n) {
		n->status	= status;
		result		= ok;
	}
	return	ok;
}
int	node_status (NODE* n) {
	int	result	= A_NONE;
	if (n) {
		result	= n->status;
	}
	return	result;
}
int	node_level (NODE* n) {
	int	result	= 0;
	if (n) {
		result	= n->level;
	}
	return	result;
}
int	node_print (NODE* n, FILE* output, int debug, int style) {
	int	level	= n->level;
	int	status	= n->status;
	char	address [IP4ADDRLEN];

	haddr_to_str (address, sizeof(address), n->adr);
	if (debug==PRN_DEBUG) {
		fprintf (output, "[%c]  ", status);
	}
	fprintf (output, "%s", address);

	switch (style) {
	case	'C':
		fprintf (output, "/%d", level);
	break;
	case	'W':	
	case	'N':	
		if (style=='N' || n->level < IP4BITS) {
			haddr_t	m	= netmask(level);
			char	mask [IP4ADDRLEN];
			haddr_to_str (mask,sizeof(mask), m);
			fprintf (output, "/%s", mask);
		}
	break;
	}
	fputc ('\n', output);
	return	ok;
}
