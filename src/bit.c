/*
//	@(#) bit.c
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# include	"bit.h"

unsigned 	bit (int n) {
	unsigned	result	= 1u << n;
	return	result;
}
int	bit_test (unsigned w, int n) {
	int	result	=  (bit(n) & w)==0?0:1;
	return	result;
}
unsigned	bit_set (unsigned w, int n) {
	return	bit(n) | w;
}	
unsigned	bit_clear (unsigned w, int n) {
	return	~bit(n) & w;
}
unsigned	bit_toggle (unsigned w, int n) {
	return	bit(n) ^ w;
}
