#include "aWorldConfig.h"
#include <OgreResourceGroupManager.h>
#include <OgreStringConverter.h>
#include <Ogre.h>
#include <OgreSingleton.h>
 

#ifndef MAP_H
#define MAP_H
#include <map>
#endif

MyConfig::MyConfig()
{}
 
void MyConfig::go(void)
{
	m_ConfigFile.load("aWorldOpts.cfg", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, "=", true);
		
	Ogre::ConfigFile::SectionIterator seci = m_ConfigFile.getSectionIterator();
	Ogre::String sectionName;
	Ogre::String keyName;
	Ogre::String valueName;
 
	while (seci.hasMoreElements())
	{
		sectionName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			keyName = i->first;
			valueName = i->second;
			m_Configs.insert(std::pair<std::string, std::string>(sectionName + "/" + keyName, valueName));
			
			// Debug
			// Ogre::String msg = "Inserted: " + sectionName + "/" + keyName, valueName;
			Ogre::String msg2 ="m_Configs: " + m_Configs[sectionName+"/"+keyName];
			Ogre::LogManager::getSingletonPtr()->logMessage(msg2);
		}
	
	}

	Ogre::LogManager::getSingletonPtr()->logMessage("***** Config Manager loaded config from file! ***********");
	
}

MyConfig::~MyConfig() { }
 
MyConfig& MyConfig::getInstance()
{
	static MyConfig Instance;
	return Instance;
}
 
bool MyConfig::getKeyExists(std::string key)
{
	if (m_Configs.count(key) > 0)
	{
		return true;
	}
	return false;
}
 
std::string MyConfig::getValueAsString(std::string key)
{
	if (getKeyExists(key) == true)
	{
		return m_Configs[key];
	}
	else
	{
		throw Ogre::Exception(Ogre::Exception::ERR_ITEM_NOT_FOUND,"Configuration key: " + key + " not found", "MyConfig::getValue");
	}
 
}
 
int MyConfig::getValueAsInt(std::string key)
{
	return atoi(getValueAsString(key).c_str());
}
Ogre::Real MyConfig::getValueAsReal(std::string key)
{
	return Ogre::StringConverter::parseReal(getValueAsString(key));
}
bool MyConfig::getValueAsBool(std::string key)
{
	return Ogre::StringConverter::parseBool(getValueAsString(key));
}
Ogre::Vector3 MyConfig::getValueAsVector3(std::string key)
{
	return Ogre::StringConverter::parseVector3(getValueAsString(key));
}
Ogre::ColourValue MyConfig::getValueAsColourValue(std::string key)
{
	return Ogre::StringConverter::parseColourValue(getValueAsString(key));
}