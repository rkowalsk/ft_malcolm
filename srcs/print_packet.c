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

void	print_sockaddr_ll(const struct sockaddr_ll *addr)
{
	printf("sll_family: 0x%x (AF_PACKET is 0x%x)\n", addr->sll_family, AF_PACKET);
	printf("sll_protocol: 0x%x ntohs(sll_protocol): 0x%x\n", addr->sll_protocol, ntohs(addr->sll_protocol));
	printf("sll_ifindex: %d\n", addr->sll_ifindex);
	printf("sll_hatype: 0x%x\n", addr->sll_hatype);
	printf("sll_halen: %d\n", addr->sll_halen);
	if (addr->sll_halen != 6)
		printf("halen != 6\n");
	else
		print_mac("received", addr->sll_addr);
}

void	print_arp_header(struct arphdr hdr)
{
	printf("ar_hrd: %d\n", ntohs(hdr.ar_hrd));
	printf("ar_pro: 0x%x\n", ntohs(hdr.ar_pro));
	printf("ar_hln: %d\n", hdr.ar_hln);
	printf("ar_pln: %d\n", hdr.ar_pln);
	printf("ar_op: %d\n", ntohs(hdr.ar_op));
}

void	print_arp_body(struct ether_arp packet)
{
	printf("arp_sha: %02x:%02x:%02x:%02x:%02x:%02x\n", packet.arp_sha[0],
		packet.arp_sha[1], packet.arp_sha[2], packet.arp_sha[3],
		packet.arp_sha[4], packet.arp_sha[5]);
	printf("arp_spa: %d.%d.%d.%d\n", packet.arp_spa[0], packet.arp_spa[1],
		packet.arp_spa[2], packet.arp_spa[3]);
	printf("arp_tha: %02x:%02x:%02x:%02x:%02x:%02x\n", packet.arp_tha[0],
		packet.arp_tha[1], packet.arp_tha[2], packet.arp_tha[3],
		packet.arp_tha[4], packet.arp_tha[5]);
	printf("arp_tpa: %d.%d.%d.%d\n", packet.arp_tpa[0], packet.arp_tpa[1],
		packet.arp_tpa[2], packet.arp_tpa[3]);
}
