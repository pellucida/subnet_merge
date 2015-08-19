/*
//	@(#) util.h
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# if	!defined(UTIL_H)
# define	UTIL_H
# include	<stdio.h>

void	setprogname (const char* s);
const	char*	progname (void);
const	char*	basename (const char* s);
void	error (char* fmt,...);
void	fatal (char* fmt,...);
int	fgetline (FILE* f, char* b, size_t size);

# endif
