#include "Server_Functions.h"
#define FAIL_IF(EXP,MSG) ({if(EXP){error(MSG);}})
#define PORT 30000
#define SA struct sockaddr_in

int main()
{
	int reuse = 1;
	int listener_d = socket(AF_INET,SOCK_STREAM,0);
	char buf[255];
	char *input = malloc(255);
	char *input_to_send = malloc(260);
	pid_t process;
	FAIL_IF(listener_d == -1,"Can't open socket");

	SA name; //Creates a port
	name.sin_family = AF_INET;
	name.sin_port = (in_port_t)htons(PORT);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	FAIL_IF(bind (listener_d,(struct sockaddr *) &name,sizeof(name)),"Can't bind to socket");
	FAIL_IF((setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1),"Can't set the reuse option on the socket");
	FAIL_IF(listen(listener_d, 10) == -1,"Can't listen");
	puts("Waiting for connection");

	SA client_addr;
	unsigned int address_size = sizeof client_addr;

	while (1) {
		int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
		FAIL_IF(connect_d == -1,"Can’t open secondary socket");


		if (!(process = fork())){
			if (say(connect_d,
				"Simple Chat Server\r\nVersion 1.0\r\n> ") != -1) {

				while(1)
					if(strcmp(buf,"\0")){
						read_in(connect_d, buf, sizeof(buf));
						printf("%s - %s\n",inet_ntoa(client_addr.sin_addr), buf);
		 	 		}
					else{
						printf("%s has left the room\n",inet_ntoa(client_addr.sin_addr));
						close(connect_d);
						break;
					}
			}
			close(connect_d);
			exit(0);
		}
		else if(process > 0){
			while(1){
				memset(input, 0, strlen(input));
				fgets(input,255,stdin);
				sprintf(input_to_send,"Host- %s",input);
				say(connect_d, input_to_send);
			}
		}
		else
			FAIL_IF(false, "Couldn't create fork");
	}

close(listener_d);
return 0;
}
