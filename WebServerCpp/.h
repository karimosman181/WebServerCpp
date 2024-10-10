#pragma once
#include "TcpListener.h"

class MultiClientChat : public TcpListener
{
public:
	MultiClientChat(const char* ipAddress, int port) :
		TcpListener(ipAddress, port) { }

protected:
	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// handler for when a message is received from client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};