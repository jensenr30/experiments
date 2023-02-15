#include <stdio.h>
#include "SDL.h"
#include "SDL_net.h" 
#include <string.h>

//  these are the glbal variables for the ip to connect to and the tcp.
IPaddress ip;
TCPsocket tcpsock;
SDLNet_SocketSet myset;

IPaddress ip; // the IP to open a server on.
TCPsocket server; // for listening to data stream
TCPsocket client; // for sending messages
//this stores my IP address.
IPaddress myIP;

void close(int retval){
	SDLNet_TCP_Close(server);
	SDLNet_Quit();
	SDL_Quit();
	exit(retval);
}



int main(int argc, char** argv){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );
	SDLNet_Init();
	
	/*
	myIP.host = 0;
	myIP.port = 69;
	char *retstr;
	//get your routable IP
	retstr = SDLNet_ResolveIP(&myIP);
	printf("Your IP is %d.%d.%d.%d:%d\n", myIP.host&0x000000ff, myIP.host&0x0000ff00, myIP.host&0x00ff0000, myIP.host&0xff000000, myIP.port);
	printf("Also this: %s\n", retstr);
	*/
	
	//get an IP.
	SDLNet_ResolveHost(&ip, NULL, 25565);
	
	
	
	
	 server = SDLNet_TCP_Open(&ip); 
	if(!server){
		printf("Could NOT set up server on %d.%d.%d.%d:%d\n", ip.host&0x000000ff, ip.host&0x0000ff00, ip.host&0x00ff0000, ip.host&0xff000000, ip.port);
		close(1);
	}
	else{
		printf("Connted to %d.%d.%d.%d:%d\n", ip.host&0x000000ff, ip.host&0x0000ff00, ip.host&0x00ff0000, ip.host&0xff000000, ip.port);
	}
	
	char text[100] = "Hello Out There!";
	
	while(1){
		client = SDLNet_TCP_Accept(server);
		if(client){
			//here you can communicate with the client.
			//use the client socket to communicate to the client.
			SDLNet_TCP_Send(client, text, strlen(text)+1);
			SDLNet_TCP_Close(client);
			break;
		}
	}
	SDLNet_TCP_Close(server);
	
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}
