#pragma once

#include <map>
#include "Resource.h"

class TextResource : public Resource
{
public:
    TextResource(std::string filename);
    ~TextResource();

    virtual void Load();
    virtual void Save();

    void AddString(std::string language, std::string str);

    void SetDefaultLanguage(std::string lang);
    std::string GetString();
    std::string GetString(std::string language);

protected:
    std::string defaultLanguage;
    std::map<std::string, std::string> localizedData;
};
