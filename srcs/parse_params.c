#include "ft_malcolm.h"

void	print_usage(void)
{
	dprintf(1, "Usage: ./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>\n");
}

void	print_params(struct params params)
{
	// printf("Params:\n");
	print_mac("src", params.src_mac);
	print_mac("tgt", params.tgt_mac);
}

int	parse_params(int argc, char **argv, struct params *params)
{
	int	ret;

	if (argc != 5)
	{
		print_usage();
		return (1);
	}
	ret = parse_mac(argv[2], params->src_mac);
	if (ret == 1)
		print_usage();
	if (ret)
		return (ret);
	ret = parse_mac(argv[4], params->tgt_mac);
	if (ret == 1)
		print_usage();
	if (ret)
		return (ret);
	if (inet_pton(AF_INET, argv[1], params->src_ip) != 1
		|| inet_pton(AF_INET, argv[3], params->tgt_ip) != 1)
	{
		print_usage();
		return (1);
	}
	return (0);
}
