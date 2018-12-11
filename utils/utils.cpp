#include "utils.h"
#include <fstream>

bool readLines(const std::string &file, std::vector<std::string>& lines)
{
    std::ifstream stream;
    stream.open(file);
    if (!stream.is_open())
        return false;
    
    lines.clear();
    std::string line;
    std::getline(stream, line);
    while (!stream.eof())
    {
        lines.push_back(line);
        std::getline(stream, line);
    }
    return true;
}

std::string string_strip(const std::string& line)
{
    size_t n = line.size();
    if (n == 0)
        return line;
    
    int left = 0;
    char c = line[left];
    while ((c == ' ' || c == '\t' || c == '\n') && left <= n - 1)
    {
        left += 1;
        c = line[left];
    }
    
    int right = int(n - 1);
    c = line[right];
    while ((c == ' ' || c == '\t' || c == '\n') && right >= 0)
    {
        right -= 1;
        c = line[right];
    }
    return line.substr(left, right - left + 1);
}

std::vector<std::string> string_split(const std::string& line, char sep)
{
    std::vector<std::string> parts;
    int left = 0;
    int index = 0;
    while (index < line.size())
    {
        if (line[index] == sep)
        {
            parts.push_back(line.substr(left, index - left));
            left = index + 1;
        }
        ++index;
    }
	if (index > left)
		parts.push_back(line.substr(left, index - left));
    return parts;
}

std::string option_find_str(const OptionMap& op_map, const std::string& key)
{
	OptionMap::const_iterator it;
	it = op_map.find(key);
	if (it != op_map.cend())
		return it->second;
	return "";
}

int option_find_int(const OptionMap& op_map, const std::string& key)
{
	OptionMap::const_iterator it;
	it = op_map.find(key);
	if (it != op_map.cend())
		return atoi(it->second.c_str());
	return 0;
}

float option_find_float(const OptionMap& op_map, const std::string& key)
{
	OptionMap::const_iterator it;
	it = op_map.find(key);
	if (it != op_map.cend())
		return (float)atof(it->second.c_str());
	return 0.0f;
}

std::string option_find_str1(const OptionMap& op_map, const std::string& key, const std::string& def_value)
{
	OptionMap::const_iterator it;
	it = op_map.find(key);
	if (it != op_map.cend())
		return it->second;
	return def_value;
}

int option_find_int1(const OptionMap& op_map, const std::string& key, int def_value)
{
	OptionMap::const_iterator it;
	it = op_map.find(key);
	if (it != op_map.cend())
		return atoi(it->second.c_str());
	return def_value;
}

float option_find_float1(const OptionMap& op_map, const std::string& key, float def_value)
{
	OptionMap::const_iterator it;
	it = op_map.find(key);
	if (it != op_map.cend())
		return (float)atof(it->second.c_str());
	return def_value;
}

