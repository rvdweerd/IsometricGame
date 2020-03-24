#pragma once
#include <PUGUXML/pugixml.hpp>
#include <string>

class XmlWrapper
{
public:
	XmlWrapper();
	~XmlWrapper();
	std::string GetAttribute(const std::string& attribute);
	bool FirstChild();
	bool NextSibbling();
	bool ReturnToParent();
	bool LoadFile(const std::string& aFilePath);

private:
	pugi::xml_document document;
	pugi::xml_node currentNode;
};