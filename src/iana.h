/**
 * 读取iana文件，存储数据结构，根据不同的需求导出不同的文件
 */

#ifndef __IANA_H__
#define __IANA_H__

#include <fstream>
#include <istream>
#include <map>
#include <ostream>
#include <vector>

// 保存version信息
struct iana_version {
  void update(const std::string line);
  std::string version, registry, serial, records, startdate, enddate, UTCoffset;
};

// 保存summary信息
struct iana_summary {
  void update(const std::string line);
  std::string registry, type, count;
};

// 保存record信息
struct iana_record {
  static std::map<std::string, std::string> len_to_prefix;
  void update(const std::string line);
  std::string registry, cc, type, start, value, date, status;
};

class iana_analyzer {
  enum struct iana_status { COMMENT, VERSION, SUMMERY, RECORD };
  friend std::ostream &operator<<(std::ostream &os, iana_status current_status);

public:
  static bool is_comment(std::string line);
  static bool is_version(std::string line);
  static bool is_summary(std::string line);

public:
  iana_analyzer(const std::string &file_path);
  ~iana_analyzer();
  void update_status(const std::string &line);
  void read();
  void write(const std::string &cc, const std::string &type,
             const std::string &prefix, const std::string &postfix);

private:
  std::ifstream file;
  iana_status current_status = iana_status::COMMENT;
  iana_version version;
  std::vector<iana_summary> summary;
  std::vector<iana_record> records;
};

#endif
