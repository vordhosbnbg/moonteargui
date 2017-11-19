#pragma once

#include <map>
#include "Resource.h"

class TextResource : public Resource
{
public:
    TextResource(const std::string& filename);
    ~TextResource();

    virtual void Load();
    virtual void Save();

    void AddString(const std::string& language, const std::string& str);

    void SetDefaultLanguage(const std::string& lang);
    std::string GetString();
    std::string GetString(const std::string& language);

protected:
    std::string defaultLanguage;
    std::map<std::string, std::string> localizedData;
};
