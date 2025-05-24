#ifndef JSON_READER
#define JSON_READER

#include <nlohmann/json.hpp>
#include <string>

class JsonReader
{
public:
    void readJsonFile(const std::string &jsonFile);
};

#endif  // !JSON_READER
