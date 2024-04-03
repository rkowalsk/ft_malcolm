#include "ft_malcolm.h"


int	check_sockaddr(struct sockaddr_storage *addr, socklen_t len,
	struct params params)
{
	if (len != sizeof(struct sockaddr_ll) || addr->ss_family != AF_PACKET)
	{
		dprintf(2, "Received the wrong address format, exiting.\n");
		return (-1);
	}
	if (((struct sockaddr_ll *) addr)->sll_protocol != htons(ETH_P_ARP)) // doesn't work ??? it actually seems to work
	{
		dprintf(2, "Received the wrong protocol. Wtf.\n");
		return (-1);
	}
	if (((struct sockaddr_ll *) addr)->sll_pkttype != PACKET_BROADCAST
		|| ((struct sockaddr_ll *) addr)->sll_halen != ETH_ALEN
		|| memcmp(((struct sockaddr_ll *) addr)->sll_addr, params.tgt_mac, ETH_ALEN))
	{
		dprintf(2, "Wrong source or destination.\n");
		return (0);
	}
	return (1);
}

// returns 1 on "all good", 0 on "packet not conform" and -1 on "critical error"
int check_arp_header(struct arphdr header)
{
	if (ntohs(header.ar_hrd) != ARPHRD_ETHER
		|| ntohs(header.ar_pro) != ARPPRO_IP)
	{
		dprintf(2, "Wrong protocol in packet header.\n");
		return (0);
	}
	if (header.ar_hln != ETH_ALEN || header.ar_pln != IP_ADDRLEN)
	{
		dprintf(2, "Wrong address size in packet header.\n");
		return (0);
	}
	if (ntohs(header.ar_op) != ARPOP_REQUEST)
	{
		dprintf(2, "Wrong OP code.\n");
		return (0);
	}
	return (1);
}

int	check_arp_body(struct ether_arp packet, struct params params)
{
	if (memcmp(packet.arp_sha, params.tgt_mac, ETH_ALEN)
		|| memcmp(packet.arp_spa, params.tgt_ip, IP_ADDRLEN))
	{
		dprintf(2, "Wrong source.\n");
		return (0);
	}
	if (memcmp(packet.arp_tpa, params.src_ip, IP_ADDRLEN))
	{
		dprintf(2, "Wrong target.\n");
		return (0);
	}
	return (1);
}

int check_packet(ssize_t size, char *buffer, struct params params)
{
	struct ether_arp	packet;
	int					ret;

	if (size != sizeof(struct ether_arp))
	{
		dprintf(2, "Received something weird (size of %ld).\n", size);
		return (0);
	}
	ft_memcpy(&packet, buffer, sizeof(struct ether_arp));
	if (VERBOSE)
	{
		printf("Received packet:\n");
		print_arp_header(packet.ea_hdr);
		print_arp_body(packet);
	}
	ret = check_arp_header(packet.ea_hdr);
	if (ret < 1)
		return (ret);
	ret = check_arp_body(packet, params);
	if (ret < 1)
		return (ret);
	return (1);
}

int	receive_packet(int sock, struct params params, struct sockaddr_ll *sender)
{
	char					buffer[64];
	int						ret;
	ssize_t					size;
	socklen_t				addr_len;
	struct sockaddr_storage	addr;

	printf("Listening.\n");
	while (1)
	{
		addr_len = sizeof(struct sockaddr_storage);
		size = recvfrom(sock, buffer, 64, 0, (struct sockaddr *) &addr,
			&addr_len);
		dprintf(1, "> new packet (%ld bytes) received\n", size);
		if (size < 0)
		{
			dprintf(2, "recvfrom: %s\n", strerror(errno));
			return (1);
		}
		ret = check_sockaddr(&addr, addr_len, params);
		if (ret < 0)
			return (1);
		else if (ret == 0)
			continue;
		*sender = *((struct sockaddr_ll *) &addr);
		ret = check_packet(size, buffer, params);
		if (ret < 0)
			return (1);
		else if (ret > 0)
			return (0);
	}
	return (0);
}