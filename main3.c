#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>          //close
#include <string.h>          //strcpy,memset,memcpy
#include <sys/types.h>       //unit8_t, unit_16_t, uint32_t
#include <sys/socket.h>      //socket
#include <netinet/in.h>      //IPPROTO_ICMP,INET_ADDRSTRLEN
#include <netinet/ip.h>      //struct ip and IP_MAXPACKET(which is 65535)
#include <netinet/ip_icmp.h> //struct icmp, ICMP_ECHO
#include <arpa/inet.h>       //inet_pton,inet_ntop
#include <sys/ioctl.h>       //macro ioctl is defined
#include <net/if.h>          //struct ifreq
#include <linux/if_ether.h>  //ETH_P_IP=0x0800, ETH_P_IPV6=0x86DD
#include <linux/if_packet.h> //struct sockaddr_LL(see man 7 packet)
#include <net/ethernet.h>
#include <error.h>           //error, perror

#define ETH_P_DEAN 		0x8874    //customized ethernet protocol type
#define MAC_ADDR_LEN 	6
#define ETH_TYPE_LEN 	2
#define SMAC_OFF 		MAC_ADDR_LEN
#define ETH_TYPE_OFF 	MAC_ADDR_LEN * 2
#define ETH_PAYLOAD_OFF ETH_TYPE_OFF + 2

int main(int argc, char **argv)
{
	int i, datalen, frame_len, sk, bytes;
	char *if_name = "ens33";
	uint8_t data[IP_MAXPACKET];
	uint8_t smac[6];
	uint8_t dmac[6];
	uint8_t ether_frame[IP_MAXPACKET];
	struct sockaddr_ll device;
	struct ifreq ifr;
	
	if ((sk = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		//used to get local netcard info
		perror("socket create failed!");
		return -1;
	}
		
	memset(&ifr, 0, sizeof(ifr));
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", if_name);
	if (ioctl(sk, SIOCGIFHWADDR, &ifr) < 0) {
		perror("ioctl failed to get smac");
		return -1;
	}
	close(sk);
	
	memcpy(smac, ifr.ifr_hwaddr.sa_data, MAC_ADDR_LEN);
	for (i = 0; i < MAC_ADDR_LEN; i++) {
		if (i < MAC_ADDR_LEN -1) {
			printf("%02x:", smac[i]);
		} else {
			printf("%02x\n", smac[i]);
		}	
	}
	
	memset(&device, 0, sizeof(device));
	if ((device.sll_ifindex = if_nametoindex(if_name)) == 0) {
		perror("if_nametoindex failed");
		return -1;
	}
	
	printf("Index for interface %s is %d\n", if_name, device.sll_ifindex);
	dmac[0] = 0x10;
	dmac[1] = 0xd2;
	dmac[2] = 0xc6;
	dmac[3] = 0xc6;
	dmac[4] = 0x2f;
	dmac[5] = 0x89;
	
	device.sll_family = AF_PACKET;
	memcpy(device.sll_addr, smac, MAC_ADDR_LEN);
	device.sll_halen = htons(MAC_ADDR_LEN);
	datalen = 5;
	data[0] = 'a';
	data[1] = 'b';
	data[2] = 'c';
	data[3] = 'd';
	data[4] = 'e';
	frame_len = MAC_ADDR_LEN + MAC_ADDR_LEN + ETH_TYPE_LEN + datalen;
	
	memcpy(ether_frame, dmac, MAC_ADDR_LEN);
	memcpy(ether_frame + SMAC_OFF, smac, MAC_ADDR_LEN);
	ether_frame[ETH_TYPE_OFF] = ETH_P_DEAN >> 8;
	ether_frame[ETH_TYPE_OFF + 1] = ETH_P_DEAN & 0x00FF;
	memcpy(ether_frame + ETH_PAYLOAD_OFF, data, datalen);
	if ((sk = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
		perror("socket failed!");
		return -1;
	}
	
	if ((bytes = sendto(sk, ether_frame, frame_len, 0, (struct sockaddr *)&device, sizeof(device))) < 0) {
		perror("sendto failed!");
		close(sk);
		return -1;
	}
	printf("send num = %d, read num = %d\n", frame_len, bytes);
	close(sk);
	
	return 0;
}
