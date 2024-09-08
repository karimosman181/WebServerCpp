#pragma once
#include "TcpListener.h"
#include "Controller.h"
#include "router.h"

class WebServer : public TcpListener
{
	//Controller controller;
	/*Router* router;*/
	Controller controller;
	Router* router = controller.getRouter();


public:
	WebServer(const char* ipAddress, int port) :
		TcpListener(ipAddress, port) { 
			/*Controller controller;
			controller.RegisterRoutes();
			router = controller.getRouter();*/
		}

protected:
	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// handler for when a message is received from client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};