#pragma once
#include <string>
#include "json.h"


struct MetaData {
    std::string title;
    std::string description;
    std::vector<std::string> keywords; // Relevant keywords
    std::string viewport = "width=device-width, initial-scale=1.0"; // Viewport meta tag
    std::string canonical; // Canonical URL
    std::string robots; // Control indexing
    std::string author; // Author of the content
    std::string ogTitle; // Open Graph title
    std::string ogDescription; // Open Graph description
    std::string ogImage; // Open Graph image URL
    std::string ogUrl; // Canonical URL for Open Graph
    std::string twitterCard; // Twitter card type
    std::string twitterTitle; // Twitter card title
    std::string twitterDescription; // Twitter card description
    std::string twitterImage; // URL for Twitter card image
    std::string schema; // Schema.org markup
    std::string charset = "UTF-8"; // Character set
    std::string language; // Language code
};


struct Response {
	std::string body;
    MetaData metaData;
};


class Resp
{

public :
	std::string notFound();
	std::string view(std::string path, Json::Value context = {}, MetaData meta = {});
	std::string js(std::string path);
	std::string css(std::string path);
	std::string image(std::string path);
	std::string json(Json::Value data);


};