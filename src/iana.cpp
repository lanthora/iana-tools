#include "iana.h"
#include "util.h"
#include <cmath>
#include <iostream>
#include <string>

void iana_version::update(const std::string line) {
  std::vector<std::string> ans;
  split_string(line, ans, "|");
  version = ans[0];
  registry = ans[1];
  serial = ans[2];
  records = ans[3];
  startdate = ans[4];
  enddate = ans[5];
  UTCoffset = ans[6];
}

void iana_summary::update(const std::string line) {
  std::vector<std::string> ans;
  split_string(line, ans, "|");
  registry = ans[0];
  type = ans[2];
  count = ans[4];
}

void iana_record::update(const std::string line) {
  std::vector<std::string> ans;
  split_string(line, ans, "|");
  registry = ans[0];
  cc = ans[1];
  type = ans[2];
  start = ans[3];
  value = ans[4];
  date = ans[5];
  status = ans[6];
  if (type == "ipv4") {
    value = iana_record::len_to_prefix[value];
  }
}

bool iana_analyzer::is_comment(std::string line) {
  return is_start_with(line, '#');
}

bool iana_analyzer::is_version(std::string line) {
  return is_start_with(line, '2');
}

bool iana_analyzer::is_summary(std::string line) {
  return is_end_with(line, "summary");
}

std::map<std::string, std::string> iana_record::len_to_prefix;

iana_analyzer::iana_analyzer(const std::string &file_path) {
  file.open(file_path, std::ios_base::out);

  for (unsigned int i = 0; i < 32; ++i) {
    iana_record::len_to_prefix[std::to_string(1ULL << i)] =
        std::to_string(32 - i);
  }
}

iana_analyzer::~iana_analyzer() { file.close(); }

void iana_analyzer::update_status(const std::string &line) {
  switch (current_status) {
  case iana_status::COMMENT:
    if (!is_comment(line)) {
      current_status = iana_status::VERSION;
    }
    break;
  case iana_status::VERSION:
    if (!is_version(line)) {
      current_status = iana_status::SUMMERY;
    }
    break;
  case iana_status::SUMMERY:
    if (!is_summary(line)) {
      current_status = iana_status::RECORD;
    }
    break;
  case iana_status::RECORD:
    break;
  }
}

void iana_analyzer::read() {
  std::string line;
  iana_summary sumarry_item;
  iana_record record_item;
  while (std::getline(file, line)) {
    update_status(line);
    switch (current_status) {
    case iana_status::COMMENT:
      break;
    case iana_status::VERSION:
      version.update(line);
      break;
    case iana_status::SUMMERY:
      sumarry_item.update(line);
      summary.push_back(sumarry_item);
      break;
    case iana_status::RECORD:
      record_item.update(line);
      records.push_back(record_item);
      break;
    default:
      break;
    }
  }
}

void iana_analyzer::write(const std::string &cc, const std::string &type,
                          const std::string &prefix,
                          const std::string &postfix) {
  for (iana_record record : records) {
    if (record.cc == cc && record.type == type) {
      std::cout << prefix << record.start << "/" << record.value << postfix
                << std::endl;
    }
  }
}