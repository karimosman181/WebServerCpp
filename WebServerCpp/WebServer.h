#pragma once
#include "TcpListener.h"

class WebServer : public TcpListener
{
public:
	WebServer(const char* ipAddress, int port) :
		TcpListener(ipAddress, port) { }

protected:
	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// handler for when a message is received from client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};