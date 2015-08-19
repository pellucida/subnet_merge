/*
//	@(#) util.c
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# include	<stdio.h>
# include	<string.h>
# include	<stdarg.h>
# include	<stdlib.h>


static	const	char*	program_name = "program";

const	char*	basename (const char* str) {
	const	char*	result	= str;
	char*	t	= strrchr (str, '/');
	if (t==0) 
		t	= strrchr (str, '\\');
	if (t) 
		result	= t+1;
	return	result;
}
void	setprogname (const char* argv0) {
	const	char*	name	= basename (argv0);
	if (name) {
		program_name	= name;
	}
}
const	char*	progname (void) {
	return	program_name;
}

void*	error (char* fmt,...) {
	va_list	ap;
	va_start(ap, fmt);
	fprintf (stderr, "ERROR: %s : ", progname());
	vfprintf (stderr, fmt, ap);
	va_end(ap);
}
void*	fatal (char* fmt,...) {
	va_list	ap;
	va_start(ap, fmt);
	fprintf (stderr, "ERROR: %s : ", progname());
	vfprintf (stderr, fmt, ap);
	va_end(ap);
	exit (EXIT_FAILURE);
}

int	fgetline (FILE* input, char* buf, size_t bufsiz) {
	size_t	maxchars	= bufsiz-1;
	int	i		= 0;
	int	ch		= fgetc (input);
	if (ch == EOF)
		return	EOF;
	while (ch != EOF && ch != '\n' && i < maxchars) {
		buf [i++]	= ch;
		ch		= fgetc (input);
	}
	buf[i]	= '\0';
	return	i;
}
