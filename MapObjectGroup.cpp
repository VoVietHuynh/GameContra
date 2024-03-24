#include"MapObjectGroup.h"

MapObjectGroup::MapObjectGroup(TiXmlElement *node)
{
	ReadXML(node);
}

MapObjectGroup::~MapObjectGroup()
{
	for (std::size_t i = 0; i < NumOnjects; i++)
	{
		MapObject *obj = Objects.at(i);
		delete obj;
	}
}
void MapObjectGroup::ReadXML(TiXmlElement *node)
{
	name =(char *) node->Attribute("name");
	TiXmlElement *indexml = NULL;
	NumOnjects = 0;
	for (indexml = node->FirstChildElement(); indexml != NULL; indexml = indexml->NextSiblingElement())
	{
		NumOnjects++;
		MapObject *obj = new MapObject(indexml,name);
		Objects.push_back(obj);
		int dd = 0;
	}
}