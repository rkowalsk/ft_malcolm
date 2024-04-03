#include "ft_malcolm.h"

int	create_socket(void)
{
	int	sock;

	sock = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_ARP));
	if (sock < 0)
	{
		dprintf(2, "socket: %s\n", strerror(errno));
		return (-1);
	}
	return (sock);
}

void	create_response(struct params params, char *response)
{
	struct ether_arp	data;

	data.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
	data.ea_hdr.ar_pro = htons(ARPPRO_IP);
	data.ea_hdr.ar_hln = ETH_ALEN;
	data.ea_hdr.ar_pln = IP_ADDRLEN;
	data.ea_hdr.ar_op = htons(ARPOP_REPLY);
	memcpy(data.arp_sha, params.src_mac, ETH_ALEN);
	memcpy(data.arp_spa, params.src_ip, IP_ADDRLEN);
	memcpy(data.arp_tha, params.tgt_mac, ETH_ALEN);
	memcpy(data.arp_tpa, params.tgt_ip, IP_ADDRLEN);
	memcpy(response, &data, sizeof(struct ether_arp));
	if (VERBOSE)
	{
		printf("Response packet:\n");
		print_arp_header(data.ea_hdr);
		print_arp_body(data);
	}
}

int	send_response(struct params params, int sock, struct sockaddr_ll sender)
{
	int		ret;
	char	response[sizeof(struct ether_arp)];

	create_response(params, response);
	ret = sendto(sock, response, sizeof(struct ether_arp), 0, (struct sockaddr *) &sender,
		sizeof(sender));
	if (ret < 0)
	{
		dprintf(2, "sendto: %s\n", strerror(errno));
		return (1);
	}
	if (ret != sizeof(struct ether_arp))
	{
		dprintf(2, "sendto: couldn't send everything.\n");
		return (1);
	}
	dprintf(1, "Response sent.\n");
	return (0);
}

int main(int argc, char **argv)
{
	int					sock;
	struct params		params;
	struct sockaddr_ll	addr;
	int					ret;

	if (parse_params(argc, argv, &params))
		return (1);
	sock = create_socket();
	if (sock < 0)
		return (2);
	ret = receive_packet(sock, params, &addr);
	if (ret)
		return (ret);
	ret = send_response(params, sock, addr);
	return (ret);
}