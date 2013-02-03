#include <OgreConfigFile.h>
#include <map>
 
class MyConfig
{
public:
	MyConfig();
	~MyConfig();
 

	void go(void);
	static MyConfig &getInstance();
 
	int getValueAsInt(std::string key);
	Ogre::Real getValueAsReal(std::string key);
	std::string getValueAsString(std::string key);
	Ogre::Vector3 getValueAsVector3(std::string key);
	bool getValueAsBool(std::string key);
	Ogre::ColourValue getValueAsColourValue(std::string key);
	bool getKeyExists(std::string key);
 
private:

	Ogre::ConfigFile m_ConfigFile;					// Config file
	std::map<std::string, std::string> m_Configs;	// Config variable
};