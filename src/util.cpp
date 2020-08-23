#include "util.h"
#include <cstring>
#include <string>
#include <vector>
bool is_space_or_tabs(const char &c) { return c == ' ' || c == '\t'; }

bool is_end_with(const std::string &line, const char *model) {
  const size_t model_size = std::strlen(model);
  return (line.rfind(model, model_size) + model_size == line.length());
}

bool is_end_with(const std::string &line, const std::string &model) {
  return is_end_with(line, model.c_str());
}

bool is_start_with(const std::string &line, const char &model) {
  for (char c : line) {
    if (is_space_or_tabs(c)) {
      continue;
    } else {
      return c == model;
    }
  }
  return false;
}

void split_string(const std::string &src, std::vector<std::string> &ret,
                  const std::string &delim) {
  const std::size_t delim_size = delim.length();
  std::size_t begin = 0UL;
  std::size_t end = 0UL;
  while ((end = src.find(delim, begin)) != std::string::npos) {
    ret.push_back(src.substr(begin, end - begin));
    begin = end + delim_size;
  }
  ret.push_back(src.substr(begin));
}