#include "../include/util.h"
#include <iostream>
#include <vector>
int main() {
  std::string s = "2|apnic|20200823|66051|19830613|20200821|+1000";
  std::string m = "|";
  std::vector<std::string> ans;

  split_string(s, ans, m);
  for (std::string ts : ans) {
    std::cout << ts << std::endl;
  }
}