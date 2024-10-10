#include <string>
#include <sstream>
#include <istream>
#include <iterator>
#include <fstream>
#include <iostream>
#include <vector>
#include "WebServer.h"
#include "json.h"

Json::Value parseQueryParams(const std::string& url) {
	Json::Value Json;

	// Find the position of '?' to locate the query parameters
	size_t pos = url.find("?");

	// If there is no '?', return an empty JSON object
	if (pos == std::string::npos) {
		return Json;
	}

	// Extract the query string (everything after '?')
	std::string queryString = url.substr(pos + 1);

	// Use stringstream to split the query string by '&' and '='
	std::stringstream ss(queryString);
	std::string param;

	// Iterate over each key-value pair separated by '&'
	while (getline(ss, param, '&')) {
		size_t eqPos = param.find("=");
		if (eqPos != std::string::npos) {
			// Split into key and value
			std::string key = param.substr(0, eqPos);
			std::string value = param.substr(eqPos + 1);
			Json[key] = value;  // Store key-value pair in the map
		}
	}

	return Json;
}

std::string extractPath(const std::string& url) {
	// Find the position of '?'
	size_t pos = url.find("?");

	// If no '?' is found, return the whole URL as the path
	if (pos == std::string::npos) {
		return url;
	}

	// Return the substring before the '?'
	return url.substr(0, pos);
}

// handler for when a message is received from client
void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{

	// Parse out the document requested
	std::istringstream iss(msg);
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());


	// parsed request
	//  parsed[0] => method
	// parsed[1] => route
	Json::Value Json;
	
	for (int index = 0; index < parsed.size(); ++index)
	{
		Json["parsed"][index] = parsed[index];
	}

	Json::StreamWriterBuilder wbuilder;
	wbuilder["indentation"] = "\t";
	std::string jsonString = Json::writeString(wbuilder, Json);

	/*fprintf(stdout, jsonString.c_str());*/

	// Create request and response object.
	if (parsed.size() >= 3) {
		Request req;
		Response res;
		req.method = parsed[0];
		req.path = "/";

		if (parsed[1] != "/")
			req.path = extractPath(parsed[1]);

		req.params = parseQueryParams(parsed[1]);

		//get body for POST, PATCH, PUT
		if (req.method == "POST" || req.method == "PATCH" || req.method == "PUT") 
		{
			if (parsed[6] == "application/json") 
			{
				//int bodyContentSize = std::stoi(parsed[12]);

				std::string bodyString = "";
				bool inBody = false;
				for (const auto& elem : parsed) {
					if (elem == "{") {
						inBody = true;
					}
					if (inBody) {
						bodyString += elem;
					}
				}

				Json::Value reqBodyJson;

				Json::Reader reader;
				bool ok = reader.parse(bodyString.c_str(), reqBodyJson);
				if (ok)
					req.body = reqBodyJson;
				else 
					fprintf(stdout, reader.getFormattedErrorMessages().c_str());
			}
		}

		// Route
		router.route_handler(&req, &res);

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