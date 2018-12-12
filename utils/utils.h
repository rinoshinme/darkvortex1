/*
 * various utility functions
 */
#ifndef DARKVORTEX_UTILS_H
#define DARKVORTEX_UTILS_H

#include <vector>
#include <string>
#include <map>

template<typename T>
bool in_vector(T& val, const std::vector<T>& vec)
{
	for (size_t k = 0; k < vec.size(); ++k)
	{
		if (val == vec[k])
			return true;
	}
	return false;
}

// string operations
bool readLines(const std::string& file, std::vector<std::string>& lines);
std::string string_strip(const std::string& line);
std::vector<std::string> string_split(const std::string& line, char sep);
bool string_starts_with(const std::string& line, const std::string& prefix);
bool string_ends_with(const std::string& line, const std::string& suffix);

// file system operations
// path separator is set to be '/' even on windows system
bool path_exists(const std::string& path);
bool is_dir(const std::string& path);
bool is_file(const std::string& path);

std::string path_join(const std::string& dir, const std::string& file);
std::string path_join(const std::vector<std::string>& parts);

enum class ListDirType
{
	FILE_ONLY,
	FILE_AND_DIR,
	FILE_AND_DIR_AND_DOT,
};

std::vector<std::string> list_dir(const std::string& dir, ListDirType type = ListDirType::FILE_ONLY);

// configuration operations
typedef std::map<std::string, std::string> OptionMap;

std::string option_find_str(const OptionMap& op_map, const std::string& key);
int option_find_int(const OptionMap& op_map, const std::string& key);
float option_find_float(const OptionMap& op_map, const std::string& key);
std::string option_find_str1(const OptionMap& op_map, const std::string& key, const std::string& def_value);
int option_find_int1(const OptionMap& op_map, const std::string& key, int def_value);
float option_find_float1(const OptionMap& op_map, const std::string& key, float def_value);

#endif
