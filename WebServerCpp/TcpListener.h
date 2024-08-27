#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

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

private:

	const char* m_ipAddress;	// IP Adddress server will run on
	int			m_port;			// Port # for the web server
	int			m_socket;		// Internal FD for the listening socket
	fd_set      m_master;       // master file descriptor
};