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
    while (!line.empty())
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
            left = index;
        }
        ++index;
    }
    return parts;
}
