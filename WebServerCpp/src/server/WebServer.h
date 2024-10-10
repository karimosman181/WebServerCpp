#pragma once
#include "TcpListener.h"
#include "ControllerFactory.cpp"
#include "router.h"

class WebServer : public TcpListener
{
	Router router;


public:
	WebServer(const char* ipAddress, int port) :
		TcpListener(ipAddress, port) { 
			RegisterAllRoutes();
		}

protected:
	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// handler for when a message is received from client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);

private: 
	void RegisterAllRoutes() {
		auto controllers = ControllerFactory::GetControllers();
		for (auto controller : controllers) {
			controller->RegisterRoutes(&router);
		}

		// Clean up controllers
		for (auto controller : controllers) {
			delete controller;
		}
	}
};