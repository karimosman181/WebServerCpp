#include "Response.h"
#include <iostream>
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

std::string Resp::js(std::string path) {
	// Open the document in the local file system
	std::ifstream f(".\\www\\assets\\js\\" + path);

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
		oss << "Content-Type: application/javascript\r\n";
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

std::string Resp::css(std::string path) {
	// Open the document in the local file system
	std::ifstream f(".\\www\\assets\\css\\" + path);

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
		oss << "Content-Type: text/css\r\n";
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

std::string Resp::image(std::string path) {
	// Open the image file in binary mode
	std::ifstream file(".\\www\\assets\\images\\" + path, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		fprintf(stdout, "Failed to open the image file!\r\n");
		return notFound();
	}

	// Get the size of the image
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	// Read the image content into a buffer
	std::vector<char> buffer(size);
	if (!file.read(buffer.data(), size)) {
		fprintf(stdout, "Failed to read the image file!\r\n");
		return notFound();
	}

	int code = 200;
	std::string codeMessage = "OK";

	// write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << code << "" << codeMessage << "\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: image/jpeg\r\n";
	oss << "Content-Length: " << size << "\r\n";
	oss << "Connection: close\r\n";
	oss << "\r\n";  // End of headers

	// Add the image content to the string stream
	oss.write(buffer.data(), size);

	std::string output = oss.str();

	return output;
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