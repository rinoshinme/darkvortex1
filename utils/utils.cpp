#include "utils.h"
#include <fstream>

#ifdef _WIN32
#include <io.h>
#include <direct.h>
#include <windows.h>
#else

#endif


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

bool string_starts_with(const std::string& line, const std::string& prefix)
{
	if (prefix.size() > line.size())
		return false;

	for (size_t i = 0; i < prefix.size(); ++i)
	{
		if (prefix[i] != line[i])
			return false;
	}
	return true;
}

bool string_ends_with(const std::string& line, const std::string& suffix)
{
	if (suffix.size() > line.size())
		return false;

	for (int i = int(suffix.size()) - 1; i >= 0; --i)
	{
		if (suffix[i] != line[i])
			return false;
	}
	return true;
}

std::string path_join(const std::string& dir, const std::string& file)
{
	if (string_ends_with(dir, "/"))
		return dir + file;
	else
		return dir + "/" + file;
}

std::string path_join(const std::vector<std::string>& parts)
{
	if (parts.size() == 0)
		return "";
	size_t total_size = 0;
	for (size_t i = 0; i < parts.size(); ++i)
		total_size += (parts[i].size() + 1);

	char* buf = new char[total_size];
	int len = 0;
	for (size_t i = 0; i < parts.size(); ++i)
		len += sprintf(buf + len, "%s/", parts[i].c_str());
	std::string result = std::string(buf);
	delete[] buf;
	return result;
}

#ifdef _WIN32

bool path_exists(const std::string& path)
{
	int ret = ::_access(path.c_str(), 0);
	if (ret == -1)
		return false;
	else
		return true;
}

bool is_dir(const std::string& path)
{
	if (!path_exists(path))
		return false;

	DWORD ret = GetFileAttributes(path.c_str());
	if (ret & FILE_ATTRIBUTE_DIRECTORY)
		return true;
	else
		return false;
}

bool is_file(const std::string& path)
{
	if (!path_exists(path))
		return false;

	DWORD ret = GetFileAttributes(path.c_str());
	if (ret & FILE_ATTRIBUTE_NORMAL)
		return true;
	else
		return false;
}

std::vector<std::string> list_dir(const std::string& dir, ListDirType type)
{
	std::vector<std::string> files;
	if (!is_dir(dir))
		return files; // empty vector

	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(dir).append("/*").c_str(), &fileinfo)) != -1)
	{
		do 
		{
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (type == ListDirType::FILE_AND_DIR || type == ListDirType::FILE_AND_DIR_AND_DOT)
					files.push_back(fileinfo.name);
			}
			else
			{
				files.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return files;
}

#else

bool path_exists(const std::string& path)
{
	return false;
}

bool is_dir(const std::string& path)
{
	return false;
}

bool is_file(const std::string& path)
{
	return false;
}

std::vector<std::string> list_dir(const std::string& dir, ListDirType type)
{
	if (!is_dir(dir))
		return false;

	return false;
}


#endif
