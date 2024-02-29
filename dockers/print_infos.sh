source_ip=$(docker inspect --format='{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' source)
source_mac=$(docker inspect --format='{{range .NetworkSettings.Networks}}{{.MacAddress}}{{end}}' source)
target_ip=$(docker inspect --format='{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' target)
target_mac=$(docker inspect --format='{{range .NetworkSettings.Networks}}{{.MacAddress}}{{end}}' target)
echo "Source IP: $source_ip"
echo "Source Mac: $source_mac"
echo "Target IP: $target_ip"
echo "Target MAC: $target_mac"
echo "\n./ft_malcolm \"$source_ip\" \"$source_mac\" \"$target_ip\" \"$target_mac\""