#include "TextResource.h"
#include "pugixml.hpp"
using namespace std;
using namespace pugi;

TextResource::TextResource(string path) : Resource(path)
{
}

TextResource::~TextResource()
{
}

void TextResource::Load()
{
    xml_document doc;
    xml_parse_result result = doc.load_file(path_to_resource.c_str());
    if (result.status == xml_parse_status::status_ok)
    {
        xml_node textRes = doc.child("TextResource");
        xml_node DefaultLanguage = textRes.child("DefaultLanguage");
        defaultLanguage = DefaultLanguage.attribute("Value").as_string();
        for (xml_node LocalizedString = textRes.child("LocalizedString"); LocalizedString; LocalizedString = LocalizedString.next_sibling())
        {
            string Language = LocalizedString.attribute("Language").as_string();
            string Value = LocalizedString.attribute("Value").as_string();
            localizedData.insert(pair<string, string>(Language, Value));
        }
    }
}

void TextResource::Save()
{
    xml_document doc;
    xml_node textRes = doc.append_child("TextResource");
    xml_node DefaultLanguage = textRes.append_child("DefaultLanguage");
    DefaultLanguage.append_attribute("Value") = defaultLanguage.c_str();
    for (auto iter = localizedData.begin(); iter != localizedData.end(); iter++)
    {
        xml_node LocalizedString = textRes.append_child("LocalizedString");
        LocalizedString.append_attribute("Language") = iter->first.c_str();
        LocalizedString.append_attribute("Value") = iter->second.c_str();
    }

    doc.save_file(path_to_resource.c_str(), "    ", format_default, encoding_utf8);
}

void TextResource::AddString(std::string language, std::string str)
{
    localizedData[language] = str;
}

void TextResource::SetDefaultLanguage(string lang)
{
    defaultLanguage = lang;
}

string TextResource::GetString()
{
    string retVal = "";

    if (defaultLanguage.size() > 0) 
    {
        retVal = GetString(defaultLanguage);
    }

    return retVal;
}

string TextResource::GetString(string language)
{
    string retVal = "";

    if (localizedData.find(language) != localizedData.end()) 
    {
        retVal = localizedData.at(language);
    }

    return retVal;
}
