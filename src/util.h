#ifndef __UTIL_H__
#define __UTIL_H__

#include <cstring>
#include <string>
#include <vector>

bool is_space_or_tabs(const char &c);

bool is_end_with(const std::string &line, const char *model);

bool is_end_with(const std::string &line, const std::string &model);

bool is_start_with(const std::string &line, const char &model);

void split_string(const std::string &src, std::vector<std::string> &ret,
                  const std::string &delim);

#endif