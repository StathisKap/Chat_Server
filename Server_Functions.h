#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
int read_in(int socket, char *buf, int len);
void error(char *msg);
int open_listener_socket();
void bind_to_port(int socket, int port);
int say(int socket, char *s);
