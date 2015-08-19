/*
//	@(#) bit.h
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# if	!defined(BIT_H)
# define	BIT_H

unsigned 	bit (int n);
/*
//  These return op(w)
//  eg bit_set (0xf0, 0) returns 0xf1
*/  
unsigned 	bit_set (unsigned w, int n);
unsigned 	bit_clear (unsigned w, int n);
unsigned 	bit_toggle (unsigned w, int n);

int	bit_test (unsigned w, int n);

# endif
