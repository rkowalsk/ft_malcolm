#include "ft_malcolm.h"

int	create_sockets(struct sockets *socks)
{
	socks->receive = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_ARP));
	socks->send = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_ARP));
	if (socks->receive < 0 || socks->send < 0)
	{
		dprintf(2, "socket: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}

int check_packet(ssize_t size, char *buffer, struct params params)
{
	struct ethhdr	ethhdr;
	(void) params;

	if (size != 42)
	{
		dprintf(2, "Received something weird (size of %ld), exiting.", size);
		return (-1);
	}
	(void) buffer;
	ft_memcpy(&ethhdr, buffer, sizeof(struct ethhdr));
	buffer += sizeof(struct ethhdr);
	print_mac("Source", ethhdr.h_source);
	print_mac("Dest", ethhdr.h_dest);
	if (ntohs(ethhdr.h_proto) != ETH_P_ARP)
	{
		dprintf(1, "Wrong protocol received. Wtf.\n");
		return (0);
	}
	// if (memcmp(ethhdr.h_source, )
	return (1);
}

int	receive_packet(struct sockets socks, struct params params)
{
	char				buffer[64];
	ssize_t				ret;
	while (1)
	{
		ret = recvfrom(socks.receive, buffer, 64, 0, NULL, NULL);
		dprintf(1, "> [%ld] bytes received\n", ret);
		if (ret < 0)
		{
			dprintf(2, "recvfrom: %s\n", strerror(errno));
			return (1);
		}
		ret = check_packet(ret, buffer, params);
		if (ret < 0)
			return (1);
		else if (ret > 0)
			return (0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	struct sockets	socks;
	struct params	params;

	if (parse_params(argc, argv, &params))
		return (1);
	if (create_sockets(&socks))
		return (2);
	printf("sockets created\n");
	printf("sizeof(struct ethhdr): %ld\n", sizeof(struct ethhdr));
	printf("sizeof(struct arphdr): %ld\n", sizeof(struct arphdr));
	// printf("sizeof(struct ether_arp): %ld\n", sizeof(struct ether_arp));
	receive_packet(socks, params);
	return (0);
}