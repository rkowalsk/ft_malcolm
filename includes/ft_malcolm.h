#pragma once

#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <net/ethernet.h>

#define IP_ADDRLEN 4
#define ARPPRO_IP 0x800

#define VERBOSE 1

struct	params
{
	unsigned char	src_mac[ETH_ALEN];
	unsigned char	tgt_mac[ETH_ALEN];
	unsigned char	src_ip[IP_ADDRLEN];
	unsigned char	tgt_ip[IP_ADDRLEN];
};

void	print_ip(const char *who, const unsigned char *address);
void	print_mac(const char *who, const unsigned char *address);
int		parse_params(int argc, char **argv, struct params *params);
int		parse_mac(char *str, unsigned char *dst);
void	print_arp_body(struct ether_arp packet);
void	print_arp_header(struct arphdr hdr);
void	print_sockaddr_ll(const struct sockaddr_ll *addr);
int		receive_packet(int sock, struct params params,
	struct sockaddr_ll *sender);

// Useful information

// struct ethhdr {
//         unsigned char   h_dest[ETH_ALEN];       /* destination eth addr */
//         unsigned char   h_source[ETH_ALEN];     /* source ether addr    */
//         __be16          h_proto;                /* packet type ID field */
// } __attribute__((packed));

// #define ETH_P_ARP       0x0806          /* Address Resolution packet    */

// #define ETH_ALEN        6               /* Octets in one ethernet addr   */

// struct  ether_arp {
//         struct  arphdr ea_hdr;          /* fixed-size header */
//         uint8_t arp_sha[ETH_ALEN];      /* sender hardware address */
//         uint8_t arp_spa[4];             /* sender protocol address */
//         uint8_t arp_tha[ETH_ALEN];      /* target hardware address */
//         uint8_t arp_tpa[4];             /* target protocol address */
// };

// struct arphdr {
//         __be16          ar_hrd;         /* format of hardware address   */
//         __be16          ar_pro;         /* format of protocol address   */
//         unsigned char   ar_hln;         /* length of hardware address   */
//         unsigned char   ar_pln;         /* length of protocol address   */
//         __be16          ar_op;          /* ARP opcode (command)         */
// };

// struct sockaddr_ll {
// 	unsigned short sll_family;   /* Always AF_PACKET */
// 	unsigned short sll_protocol; /* Physical-layer protocol */
// 	int            sll_ifindex;  /* Interface number */
// 	unsigned short sll_hatype;   /* ARP hardware type */
// 	unsigned char  sll_pkttype;  /* Packet type */
// 	unsigned char  sll_halen;    /* Length of address */
// 	unsigned char  sll_addr[8];  /* Physical-layer address */
// };

// #define ARPHRD_ETHER    1               /* Ethernet 10/100Mbps.  */

/* ARP protocol opcodes. */
// #define ARPOP_REQUEST   1               /* ARP request.  */
// #define ARPOP_REPLY     2               /* ARP reply.  */
// #define ARPOP_RREQUEST  3               /* RARP request.  */
// #define ARPOP_RREPLY    4               /* RARP reply.  */
// #define ARPOP_InREQUEST 8               /* InARP request.  */
// #define ARPOP_InREPLY   9               /* InARP reply.  */
// #define ARPOP_NAK       10              /* (ATM)ARP NAK.  */