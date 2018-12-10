/*
 * various utility functions
 */
#ifndef DARKVORTEX_UTILS_H
#define DARKVORTEX_UTILS_H

#include <vector>
#include <string>

bool readLines(const std::string& file, std::vector<std::string>& lines);

std::string string_strip(const std::string& line);

std::vector<std::string> string_split(const std::string& line, char sep);

#endif
