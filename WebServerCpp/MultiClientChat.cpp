#include "MultiClientChat.h"
#include <string>

// Handler for client connections
void MultiClientChat::onClientConnected(int clientSocket) 
{
	fprintf(stdout, "connected\n");
	//Send a welcome message to the connected client
	std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
	sendToClient(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1);
}

// Handler for client disconnections
void MultiClientChat::onClientDisconnected(int clientSocket)
{
	fprintf(stdout, "disconnected\n");
	std::string welcomeMsg = "Disconnected!\r\n";
	sendToClient(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1);
}

// handler for when a message is received from client
void MultiClientChat::onMessageReceived(int clientSocket, const char* msg, int length)
{
	broadCastToClient(clientSocket, msg, length);
}
