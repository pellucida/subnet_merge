/*
//	@(#) netaddr.c
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# include	<ctype.h>
# include	<string.h>
# include	<stdio.h>
# include	"constants.h"
# include	"bit.h"
# include	"netaddr.h"

haddr_t	netmask (int n) {
	return	(~0u) << (IP4BITS-n);
}

int	str_to_haddr (haddr_t* adrp, const char* sa) {
	int	result	= ok;
	haddr_t	adr	= 0;
	char	copy [IP4ADDRLEN];
	char*	s	= copy;
	char*	t	= 0;
	int	i	= 0;
	int	fin	= 4;
	strncpy (copy, sa, IP4ADDRLEN);
	while (i != fin) {
		unsigned	octet	= 0;
		t	= strchr (s, '.');
		if (t) {
			*t	= '\0';
			octet	= atoi (s);
			s	= t+1;
		}
		else 	{
			octet	= atoi (s);
		}
		if (octet < 256) {
			adr	= (adr<<8)|octet;
			++i;
		}
		else	{
			result	= err;
			fin	= i;
		}
	}	
	if (result == ok)
		*adrp	= adr;
	return	result;
}

int	mask_to_cidr (int* cidrp, const char* mask) {
	int	result	= ok;
	haddr_t	u	= 0;
	int	cidr	= IP4BITS;
	int	i	= IP4BITS;
	str_to_haddr (&u, mask);
	
	while (i>0 && bit_test (u, i-1)==1) {
		--i;
	}
	cidr	= IP4BITS - i;
	if ( (~netmask(cidr) & u)!=0) {
		result	= err; /* non contiguous netmask */
	}
	*cidrp	= cidr;
	return	result;
}

int	haddr_to_str (char* str, int size, haddr_t adr) {
	unsigned	octet [4];
	int	i	= 0;
	for (i=3; i >=0 ; --i) {
		octet [i]	= adr & 0xff;
		adr	>>= 8;
	}
	return	snprintf (str, size, "%d.%d.%d.%d",
		octet[0], octet[1], octet[2], octet[3]);
}
