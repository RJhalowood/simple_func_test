#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>			//gethostname
#include <sys/socket.h>		//socket
#include <string.h>
#include <arpa/inet.h>		//inet_ntoa
#include <net/if.h>			//struct ifreq
#include <sys/ioctl.h>		//ioctl
#include <error.h>

#define HOSTNAME_LEN	256
#define IF_NAME			"ens33"
#define MAC_ADDR_LEN	6

int main(void)
{
	char name[HOSTNAME_LEN];
	int fd;
	int i;
	char ip[128];
	unsigned char mac[MAC_ADDR_LEN];
	struct sockaddr_in *sa;
	struct ifreq ifr_ip;
	struct ifreq ifr_mac;
	
	if (gethostname(name, HOSTNAME_LEN) < 0) {
		perror("fail to get host name");
		return -1;
	}
	printf("hostname = %s\n", name);
	
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creat failed");
		return -1;
	}
	
	memset(&ifr_ip, 0, sizeof(ifr_ip));
	memset(&ifr_mac, 0, sizeof(ifr_mac));
	memcpy(ifr_ip.ifr_name, IF_NAME, strlen(IF_NAME));
	if (ioctl(fd, SIOCGIFADDR, &ifr_ip) < 0) {
		perror("get interface ip failed");
		close(fd);
		return -1;
	}
	sa = (struct sockaddr_in *)&ifr_ip.ifr_addr;
	if (inet_ntop(AF_INET, &sa->sin_addr, ip, sizeof(ip)) == NULL) {
		perror("inet_ntop failed");
		close(fd);
		return -1;
	}
	printf("ip = %s\n", ip);
	
	memcpy(ifr_mac.ifr_name, IF_NAME, strlen(IF_NAME));
	if (ioctl(fd, SIOCGIFHWADDR, &ifr_mac) < 0) {
		perror("get interface mac failed");
		close(fd);
		return -1;
	}
	close(fd);
	
	memcpy(mac, ifr_mac.ifr_hwaddr.sa_data, MAC_ADDR_LEN);
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2],
										mac[3], mac[4], mac[5]);
	
	return 0;
}