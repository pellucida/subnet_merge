/*
//	@(#) tree.c
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# include	<stdio.h>

# include	"constants.h"
# include	"bit.h"
# include	"netaddr.h"
# include	"node.h"
# include	"tree.h"


int	tree_Create (TREE** tp) {
	TREE*	t	= 0;
	int	result	= node_Create (&t, 0, 0);
	if (result==ok) {
		*tp	= t;
	}
	return	result;
}

int	tree_Delete (TREE** tp) {
	if (tp) {
		TREE*	t	= *tp;
		if (t) {
			NODE*	left	= node_subtree (t, N_Z);
			NODE*	right	= node_subtree (t, N_U);
			if (left) {
				tree_Delete (&left);
			}
			if (right) {
				tree_Delete (&right);
			}
			node_Delete (tp);
		}
	}
	return	ok;
}

/*
// Do pre-order walk of tree - while (*f)() returns true
// When (*f)() return false prune the walk at that node
*/
void	tree_traverse (TREE* t, int (*f)(NODE*, void*), void* args) {
	if (t) {
		int	r	= f(t, args);
		if (r) {
			NODE*	left	= node_subtree (t, N_Z);
			NODE*	right	= node_subtree (t, N_U);
			tree_traverse (left, f, args);
			tree_traverse (right, f, args);
		}
	}
}

static	int	check_children (TREE* t) {
	int	result	= false;
	NODE*	left	= node_subtree (t,N_Z);
	NODE*	right	= node_subtree (t,N_U);
	if (left) {
		int	ls	= node_status (left);
		if (right) {
			int	rs	= node_status (right);
			result	=	(ls == A_ADDED || ls == A_COMBINE) &&
					(rs == A_ADDED || rs == A_COMBINE);
		}
	}
	return	result;
}
/*
// Every address/mask line input has an entry in the tree
// We could prune this if an ADDED or COMBINE entry occurs
// earlier in the tree.
// ie
// If level < mask and t->status == 'E' or 'C' => return ok
*/
int	tree_insert (TREE* t, haddr_t adr, int mask) {
	int	result	= ok;
	int	level	= node_level (t);
	int	dir	= bit_test (adr, IP4BITS-(level+1)); 
	if (level < mask) {
		NODE*	subtree	= node_subtree (t, dir);
		if (subtree == 0) {
			result	= node_Create (&subtree, adr, level+1);
			if (result == ok) {
				node_setsubtree (t, dir, subtree);
			}
		}
		result	= tree_insert (subtree, adr, mask);
		if (check_children (t)) {
		/* eg	XX.XX.X0.00/24 and XX.XX.X1.0/24 -> XX.XX.X0.0/23 */
			node_setstatus (t, A_COMBINE);
		}
	}
	else if (level == mask) {
		node_setstatus (t, A_ADDED);
	}
	return	result;
}

typedef	struct	prn_args {
	FILE*	output;
	int	style;
} PRN_ARGS;

static	int	printer (NODE* n, void* args) {
	PRN_ARGS*	pargs	= args;
	int	status	= node_status (n);
	int	style	= pargs->style;
	FILE*	output	= pargs->output;

	if (status == A_ADDED || status == A_COMBINE) {
		node_print (n, output, PRN_DEBUG, style);
	}
	return	true;
}

void	tree_print (TREE* t, int style) {
	PRN_ARGS	args	= { stdout, style };
	tree_traverse (t, printer, &args);
}
static	int	print_prune (NODE* n, void* args) {
	int	result	= true;
	PRN_ARGS*	pargs	= args;
	int	status	= node_status (n);
	int	style	= pargs->style;
	FILE*	output	= pargs->output;

	if (status == A_ADDED || status == A_COMBINE) {
		node_print (n, output, PRN_PRUNE, style);
		result	= false;
	}
	return	result;
}

void	tree_print_prune (TREE* t, int style) {
	PRN_ARGS	args	= { stdout, style };
	tree_traverse (t, print_prune, &args);
}
