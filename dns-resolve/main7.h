#ifndef _MAIN7_H_
#define _MAIN7_H_
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define ETHER_ADDR_LEN  6


/* Ethernet header */ 
typedef struct gs_sniff_ethernet_s { 
    u_char  ether_dhost[ETHER_ADDR_LEN]; /* destination */ 
    u_char  ether_shost[ETHER_ADDR_LEN]; /* source */ 
    u_short ether_type;                 /* IP? ARP? RARP? etc */ 
} gs_sniff_ethernet_t;

/* IP header */
typedef struct gs_sniff_ip_s {
    u_char  ip_vhl;                     /* version << 4 | header length >> 2 */
    u_char  ip_tos;                     /* type of service */  
    u_short ip_len;                     /* total length */  
    u_short ip_id;                      /* identification */  
    u_short ip_off;                     /* fragment offset field */  
#define IP_RF 0x8000                    /* reserved fragment flag */  
#define IP_DF 0x4000                    /* dont fragment flag */  
#define IP_MF 0x2000                    /* more fragments flag */  
#define IP_OFFMASK 0x1fff               /* mask for fragmenting bits */  
    u_char  ip_ttl;                     /* time to live */  
    u_char  ip_p;                       /* protocol */  
    u_short ip_sum;                     /* checksum */  
    struct  in_addr ip_src,ip_dst;      /* source and dest address */ 
}gs_sniff_ip_t; 

/* UDP header */  
typedef struct gs_sniff_udp_s {  
  u_short sport;                       /* source port */  
  u_short dport;                       /* destination port */  
  u_short udp_length;  
  u_short udp_sum;                     /* checksum */  
} gs_sniff_udp_t; 

/* DNS header */
typedef struct gs_sniff_dns_s {
    u_short id;                  /* identification number */
    u_char  rd :1;                /* recursion desired */
    u_char  tc :1;                /* truncated message */
    u_char  aa :1;                /* authoritive answer */
    u_char  opcode :4;            /* purpose of message */
    u_char  qr :1;                /* query/response flag */
    u_char  rcode :4;             /* response code */
    u_char  cd :1;                /* checking disabled */
    u_char  ad :1;                /* authenticated data */
    u_char  z :1;                 /* its z! reserved */
    u_char  ra :1;                /* recursion available */
    u_short q_count;             /* number of question entries */
    u_short ans_count;           /* number of answer entries */
    u_short auth_count;          /* number of authority entries */
    u_short add_count;           /* number of resource entries */
}gs_sniff_dns_t;

//Constant sized fields of query structure
typedef struct gs_sniff_question_s {
    u_short qtype;
    u_short qclass;
} gs_sniff_question_t;

//Constant sized fields of the resource record structure
#pragma pack(push, 1)
typedef struct gs_sniff_res_s {
    u_short type;
    u_short class;
    u_int   ttl;
    u_short data_len;
} gs_sniff_res_t;
#pragma pack(pop)

//Pointers to resource record contents
typedef struct gs_sniff_dns_res_record_s
{
    u_char          *name;
    gs_sniff_res_t *resource;
    u_char          *data;
} gs_sniff_dns_res_record_t;

//Structure of a Query
typedef struct gs_sniff_dns_query_s {
    u_char              *name;
    gs_sniff_question_t *ques;
} gs_sniff_dns_query_t;

#endif
