#include "ft_malcolm.h"

void	print_mac(const char *who, const unsigned char *address)
{
	printf("%s MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", who, address[0],
		address[1], address[2], address[3], address[4], address[5]);
}

void	print_ip(const char *who, const unsigned char *address)
{
	printf("%s IP: %d.%d.%d.%d\n", who, address[0], address[1], address[2],
		address[3]);
}