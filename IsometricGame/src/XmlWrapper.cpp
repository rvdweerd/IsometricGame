#include "XmlWrapper.h"

XmlWrapper::XmlWrapper()
{
}

XmlWrapper::~XmlWrapper()
{
}

std::string XmlWrapper::GetAttribute(const std::string& attribute)
{
	return currentNode.attribute(attribute.c_str()).value();
}

bool XmlWrapper::FirstChild()
{
	pugi::xml_node nextNode = currentNode.first_child();
	if (!nextNode)
	{
		return false;
	}
	currentNode = nextNode;
	return true;
}

bool XmlWrapper::NextSibbling()
{
	pugi::xml_node nextNode = currentNode.next_sibling();
	if (!nextNode)
	{
		return false;
	}
	currentNode = nextNode;
	return true;
}

bool XmlWrapper::ReturnToParent()
{
	pugi::xml_node nextNode = currentNode.parent();
	if (!nextNode)
	{
		return false;
	}
	currentNode = nextNode;
	return true;
}

bool XmlWrapper::LoadFile(const std::string& aFilePath)
{
	pugi::xml_parse_result result = document.load_file(aFilePath.c_str());
	if (result.status != pugi::xml_parse_status::status_ok)
	{
		return false;
	}
	//pugi::xml_node child = doc.child("map");
	//printf("Element name: %s", doc.child("map").attribute("width").value());
	currentNode = document.first_child();
	return true;
}
