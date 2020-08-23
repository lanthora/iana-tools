#include "iana.h"
#include "util.h"
#include <iostream>

#define PARSE(key)                                                             \
  if (kv[0][0] == '-' && kv[0].substr(1) == #key) {                            \
    key = kv[1];                                                               \
    continue;                                                                  \
  }

int main(int argc, char **argv) {

  std::string file, cc, type;
  std::string prefix = "", postfix = "", headers = "";

  std::vector<std::string> kv;
  for (int i = 1; i < argc; ++i) {
    kv.clear();
    split_string(argv[i], kv, "=");
    PARSE(file);
    PARSE(cc);
    PARSE(type);
    PARSE(prefix);
    PARSE(postfix);
    PARSE(headers);
  }

  iana_analyzer analyzer(file);
  analyzer.read();
  std::cout << headers << std::endl;
  analyzer.write(cc, type, prefix, postfix);
  return 0;
}
