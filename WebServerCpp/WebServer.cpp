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
	// GET /index.html  HTTP/1.1

	// Parse out the document requested
	std::istringstream iss(msg);
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());



	std::string content = "<h1>404 Not Found !<h1>";
	int code = 404;
	std::string codeMessage = "Not Found";
	std::string path = "\\index.html";
	
	
	if (parsed.size() >= 3 && parsed[0] == "GET")
	{

		if (parsed[1] != "/")
			path = parsed[1];

		// Open the document in the local file system
		std::ifstream f(".\\www" + path);


		if (f.good())
		{
			code = 200;
			codeMessage = "OK";

			std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
			content = str;
		}
	}
	
	// write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << code << "" << codeMessage << "\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();
	int size = output.size() + 1;


	sendToClient(clientSocket, output.c_str(),  size);
}

// Handler for client connections
void WebServer::onClientConnected(int clientSocket)
{

}

// Handler for client disconnections
void WebServer::onClientDisconnected(int clientSocket)
{

}