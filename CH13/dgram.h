#ifndef _DGRAM_H_
#define _DGRAM_H_
int make_dgram_server_socket(int);
int make_dgram_client_socket(void);
int make_internet_address(char *, int , struct sockaddr_in *);
int get_internet_address(char *, int , int *, struct sockaddr_in *);
#endif
