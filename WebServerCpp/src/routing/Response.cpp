#include "Response.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include "Template.h"


std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
	std::ostringstream result;
	for (size_t i = 0; i < vec.size(); ++i) {
		result << vec[i];
		if (i != vec.size() - 1) {
			result << delimiter;
		}
	}
	return result.str();
}

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

std::string Resp::view(std::string path, Json::Value context, MetaData meta) {
	// Open the document in the local file system
	std::ifstream f(".\\www" + path);

	if (f.good())
	{
		int code = 200;
		std::string codeMessage = "OK";
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		std::string content = str;

       // Inject meta data in the <head> section
        std::string metaTags;
		if (meta.title.size() > 0)  metaTags += "<title>" + meta.title + "</title>\n";
    	if(meta.charset.size() > 0) metaTags += "<meta charset=\"" + meta.charset + "\">\n";
    	if(meta.description.size() > 0) metaTags += "<meta name=\"description\" content=\"" + meta.description + "\">\n";
    	if(meta.keywords.size() > 0) metaTags += "<meta name=\"keywords\" content=\"" + join(meta.keywords, ",") + "\">\n";
        if(meta.viewport.size() > 0) metaTags += "<meta name=\"viewport\" content=\"" + meta.viewport + "\">\n";
        if(meta.author.size() > 0) metaTags += "<meta name=\"author\" content=\"" + meta.author + "\">\n";
        if(meta.robots.size() > 0) metaTags += "<meta name=\"robots\" content=\"" + meta.robots + "\">\n";
        if(meta.ogTitle.size() > 0) metaTags += "<meta property=\"og:title\" content=\"" + meta.ogTitle + "\">\n";
        if(meta.ogDescription.size() > 0) metaTags += "<meta property=\"og:description\" content=\"" + meta.ogDescription + "\">\n";
        if(meta.ogImage.size() > 0) metaTags += "<meta property=\"og:image\" content=\"" + meta.ogImage + "\">\n";
        if(meta.ogUrl.size() > 0) metaTags += "<meta property=\"og:url\" content=\"" + meta.ogUrl + "\">\n";
        if(meta.twitterCard.size() > 0) metaTags += "<meta name=\"twitter:card\" content=\"" + meta.twitterCard + "\">\n";
        if(meta.twitterTitle.size() > 0) metaTags += "<meta name=\"twitter:title\" content=\"" + meta.twitterTitle + "\">\n";
        if(meta.twitterDescription.size() > 0) metaTags += "<meta name=\"twitter:description\" content=\"" + meta.twitterDescription + "\">\n";
        if(meta.twitterImage.size() > 0) metaTags += "<meta name=\"twitter:image\" content=\"" + meta.twitterImage + "\">\n";
        if(meta.canonical.size() > 0) metaTags += "<link rel=\"canonical\" href=\"" + meta.canonical + "\">\n";
        if(meta.schema.size() > 0) metaTags += "<script type=\"application/ld+json\">" + meta.schema + "</script>\n";


		//inset tailwind, daisyUI, alpinejs scripts
		std::string scripts;
		scripts += "<link href=\"https://cdn.jsdelivr.net/npm/daisyui@4.12.13/dist/full.min.css\" rel=\"stylesheet\" type=\"text/css\" />";
		scripts += "<script src=\"https://cdn.tailwindcss.com\"></script>";
		scripts += "<script src=\"//unpkg.com/alpinejs\" defer></script>";
	
		// Insert metadata into the head tag of the HTML
        size_t headPos = content.find("<head>");
        if (headPos != std::string::npos) {
            size_t headEndPos = content.find("</head>", headPos);
            if (headEndPos != std::string::npos) {
                content.insert(headEndPos, metaTags); // Insert meta tags before </head>
				content.insert(headEndPos, scripts); // Insert scripts tags before </head>
            }
        }

		// write the document back to the client
		std::ostringstream oss;
		oss << "HTTP/1.1 " << code << "" << codeMessage << "\r\n";
		oss << "Cache-Control: no-cache, private\r\n";
		oss << "Content-Type: text/html\r\n";
		oss << "Content-Length: " << content.size() << "\r\n";
		oss << "\r\n";

		std::string result = content;

		if (context.size() > 0) {
			Template tmp;

			result = tmp.processTemplate(content, context);
		}
		
		oss << result;

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

std::string getMimeType(const std::string& filePath) {
	// Extract the file extension
	std::string extension = filePath.substr(filePath.find_last_of('.') + 1);

	// Determine the MIME type based on the extension
	if (extension == "png") return "image/png";
	else if (extension == "jpg" || extension == "jpeg") return "image/jpeg";
	else if (extension == "gif") return "image/gif";
	else if (extension == "bmp") return "image/bmp";
	else if (extension == "svg") return "image/svg+xml";
	else return "application/octet-stream"; // Default for unknown types
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

	// Get the MIME type based on the file extension
	std::string mimeType = getMimeType(path);

	// write the document back to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << code << "" << codeMessage << "\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: "<< mimeType<<"\r\n";
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