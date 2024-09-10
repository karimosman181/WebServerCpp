#include <string>
#include <sstream>
#include <istream>
#include <iterator>
#include <fstream>
#include <iostream>
#include <vector>
#include "WebServer.h"

// handler for when a message is received from client
void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{

	// Parse out the document requested
	std::istringstream iss(msg);
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());


	// parsed request
	//  parsed[0] => method
	// parsed[1] => route

	// Create request and response object.
	if (parsed.size() >= 3) {
		Request req;
		Response res;
		req.method = parsed[0];
		req.path = "/";

		if (parsed[1] != "/")
			req.path = parsed[1];

		// Route
		router->route_handler(&req, &res);

		std::string output = res.body;
		int size = output.size() + 1;


		sendToClient(clientSocket, output.c_str(), size);
	}
	else {
	// send bad request
	}
}

// Handler for client connections
void WebServer::onClientConnected(int clientSocket)
{

}

// Handler for client disconnections
void WebServer::onClientDisconnected(int clientSocket)
{

}