/*
 * various utility functions
 */
#ifndef DARKVORTEX_UTILS_H
#define DARKVORTEX_UTILS_H

#include <vector>
#include <string>
#include <map>

bool readLines(const std::string& file, std::vector<std::string>& lines);
std::string string_strip(const std::string& line);
std::vector<std::string> string_split(const std::string& line, char sep);

typedef std::map<std::string, std::string> OptionMap;

std::string option_find_str(const OptionMap& op_map, const std::string& key);
int option_find_int(const OptionMap& op_map, const std::string& key);
float option_find_float(const OptionMap& op_map, const std::string& key);
std::string option_find_str1(const OptionMap& op_map, const std::string& key, const std::string& def_value);
int option_find_int1(const OptionMap& op_map, const std::string& key, int def_value);
float option_find_float1(const OptionMap& op_map, const std::string& key, float def_value);


#endif
