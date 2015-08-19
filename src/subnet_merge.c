/*
//	@(#) subnet_merge.c
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	"constants.h"
# include	"tree.h"
# include	"util.h"

void	Usage() {
	fprintf (stderr, "Usage: %s [-D] [-m N|C|W] -f file\n", progname());
	fprintf (stderr, " -D    - debug\n");
	fprintf (stderr, " -m ?  - netmask output style\n");
	fprintf (stderr, "    C  - xx.xx.xx.xx/nn\n");
	fprintf (stderr, "    N  - xx.xx.xx.xx/mm.mm.mm.mm\n");
	fprintf (stderr, "    W  - like N but tcpwrapper compatible.\n");
	exit (EXIT_FAILURE);
}
const	static	char	STYLES[]	= "CNW";

main (int argc, char* argv[]) {
	TREE*	tree	= 0;
	haddr_t	u	= 0;
	char	line [BUFSIZ];
	FILE*	input	= stdin;
	char*	infile	= 0;
	int	opt	= EOF;
	int	D_flag	= 0;
	int	f_flag	= 0;
	int	m_flag	= 0;
	int	style	= 'C';

	setprogname (argv[0]);

	if (sizeof(haddr_t) < 4)	/* very old compilers */ 
		fatal ("Unsigned is too small %d < 4\n", sizeof(haddr_t));

	opterr	= 0;
	while ((opt = getopt (argc, argv, "f:m:D"))!=EOF) {
		switch (opt) {
		case	'f':
			if (f_flag++)
				Usage ();
			infile	= optarg;
		break;
		case	'm':
			if (m_flag++)
				Usage ();
			style	= optarg[0];
		break;
		case	'D':
			D_flag++;
		break;
		default:
			Usage ();
		}
	}
	if (f_flag) {
		input	= fopen (infile, "r");
		if (input==0) {
			fatal ("Cannot open file: \"%s\"\n", infile);
		}
	}
	if (strchr (STYLES, style)==0) {
		fatal ("style %c not in <%s>\n", style, STYLES);
	}
		
	tree_Create (&tree);
	while (fgetline (input, line, sizeof(line)) != EOF) {
		unsigned	mask	= 32;
		char*		mptr	= 0;
		char*	t	= strchr (line, '/');
		if (t) {
			*t	= '\0';
			mptr	= t+1;
			if (strchr (mptr, '.')==0) {
				mask	= atoi (mptr);
			}
			else	{
				mask_to_cidr (&mask, mptr);
			}
		}
		if (mask <= IP4BITS && str_to_haddr (&u, line) == ok) {
			tree_insert (tree, u, mask);
		}
	}
	if (D_flag)
		tree_print (tree, style);
	else
		tree_print_prune (tree, style);

	tree_Delete (&tree);
}
