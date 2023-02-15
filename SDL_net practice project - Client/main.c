#include <stdio.h>
#include "SDL.h"
#include "SDL_net.h"
#include <string.h>

//  these are the glbal variables for the ip to connect to and the tcp.
IPaddress ip;
TCPsocket tcpsock;
SDLNet_SocketSet myset;


int main(int argc, char** argv){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	
	//get an IP.
	IPaddress ip;
	SDLNet_ResolveHost(&ip, "127.0.0.1", 1234);
	
	//TCPsocket server = SDLNet_TCP_Open(&ip);
	TCPsocket client = SDLNet_TCP_Open(&ip);
	char text[100];
	SDLNet_TCP_Recv(client, text,100+1);
	printf("text");
	
	SDLNet_TCP_Close(client);
	
	SDLNet_Quit();
	SDL_Quit();
	system("pause");
	return 0;
}
