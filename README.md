
### Summarize, condense or merge IPv4 network/mask lists

A while ago I was looking for something to summarize network 
access lists where the lists were either /1..32 or /dotted quad
format. I found a few perl and some python scripts but they
produced conflicting output for the same files and even
when the same file had its line ordering changed.


I thought about the easiest way of doing this and one way of
sorting the entries and coalescing adjacent entries seemed 
reasonable "[http://cidrmerge.sourceforge.net/](cidr_merge) does this.
The other was to build a binary tree and merge adjacent entries
while inserting into the tree.
I found the second easier to implement.

### SYNOPSIS

```subnet_merge [ -D ] [ -m C|N|W ] -f network_mask_list_file
               -D	debug info
               -m	mask style for list output
                   C	xx.xx.xx.0/cc		[C]idr
                   N	xx.xx.xx.0/mm.mm.mm.0	[N]etmask
                   W	xx.xx.xx.xx		tcp_[W]rapper
               -f file	input file one entry per line
```
### EXAMPLES</h4>
<p>
Given an input file containing this list

	10.78.76.0/24
	10.78.77.0/24

the program should write to stdout

	10.78.76.0/23

The input could equivalently be given as

	10.78.76.0/255.255.255.0
	10.78.76.0/255.255.255.0

To have the output printed as

	10.78.76.0/255.255.254.0

use the `-m N` switch.  The `-m W` switch is identical 
except for 255.255.255.255 masks for host addresses.

eg 10.78.80.17 instead of 10.78.80.17/255.255.255.255 


If the list is too big for the program to handle in one go
sort the list and split the output into a number of pieces
Run subnet_merge on the pieces separately and then on the output.

### PREREQUISITES

The code doesn't use any networking headers or libraries and
should be compilable by any C89 compiler. Unsigned int has to
be 4 bytes or more (otherwise change unsigned int to unsigned long.)

### SEE ALSO
[http://cidrmerge.sourceforge.net/](http://cidrmerge.sourceforge.net/)

### LICENSE
Creative Commons CC0
[http://creativecommons.org/publicdomain/zero/1.0/legalcode]
(http://creativecommons.org/publicdomain/zero/1.0/legalcode)

### AUTHOR
[mailto:toves@sdf.lonestar.org](James Sainsbury)
