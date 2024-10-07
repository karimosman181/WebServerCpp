#include "Response.h"
#include <istream>
#include <fstream>
#include <sstream>


std::string Resp::notFound() {
	std::string content = "<h1>404 Not Found !<h1>";
	int code = 404;
	std::string codeMessage = "Not Found";

	// write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << code << "" << codeMessage << "\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();

	return output;
}

std::string Resp::view(std::string path) {
	// Open the document in the local file system
	std::ifstream f(".\\www" + path);

	if (f.good())
	{
		int code = 200;
		std::string codeMessage = "OK";
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		std::string content = str;

		// write the document back to the client
		std::ostringstream oss;
		oss << "HTTP/1.1 " << code << "" << codeMessage << "\r\n";
		oss << "Cache-Control: no-cache, private\r\n";
		oss << "Content-Type: text/html\r\n";
		oss << "Content-Length: " << content.size() << "\r\n";
		oss << "\r\n";
		oss << content;

		std::string output = oss.str();

		return output;
	}
	else {
		return notFound();
	}
}

std::string Resp::json(Json::Value data)
{
	int code = 200;
	std::string codeMessage = "OK";

	Json::StreamWriterBuilder wbuilder;
	wbuilder["indentation"] = "\t";
	std::string jsonString = Json::writeString(wbuilder, data);

	std::string content = jsonString;

	// write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << code << "" << codeMessage << "\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: application/json;charset=UTF-8\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();

	return output;
}