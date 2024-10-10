#pragma once

#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class TcpListener
{
public:

	TcpListener(const char* ipAddress, int port) :
		m_ipAddress(ipAddress), m_port(port) { }

	// Initialize the listener
	int init();

	// Run the listener
	int run();
	
protected:

	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// handler for when a message is received from client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);

	// send a message to client
	void sendToClient(int clientSocket, const char* msg, int length);

	// Broadcast a message from a client
	void broadCastToClient(int sendingClient, const char* msg, int length);

private:

	const char* m_ipAddress;	// IP Adddress server will run on
	int			m_port;			// Port # for the web server
	int			m_socket;		// Internal FD for the listening socket
	fd_set      m_master;       // master file descriptor
};