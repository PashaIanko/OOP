#pragma once

#include <memory>
#include <string>

class Document;

struct Parameters {
	std::weak_ptr<Document> doc;
	std::string str;
	size_t from;
	size_t to;
};