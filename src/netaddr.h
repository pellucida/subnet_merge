/*
//	@(#) netaddr.h
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# if	!defined(NETADDR_H)
# define	NETADDR_H

typedef	unsigned int	haddr_t;

enum	{
	IP4BITS	= 32,
	IP4ADDRLEN	= sizeof("111.111.111.111")+1,
};

haddr_t	netmask (int n);
int	str_to_haddr (haddr_t* adrp, const char* sa);
int	haddr_to_str (char* str, int size, haddr_t adr);

# endif
