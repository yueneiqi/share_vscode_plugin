#include "text_query.h"

namespace seven {
TextQuery::TextQuery(ifstream& ifs)
    : file_(std::make_shared<vector<string>>()) {
  string text;
  while (getline(ifs, text)) {
    file_->push_back(text);
    uint64_t n = file_->size() - 1;
    istringstream line(text);
    string word;
    while (line >> word) {
      auto& lines = wm_[word];
      if (!lines) {
        lines = make_shared<set<line_no>>();
      }
      lines->insert(n);
    }
  }
}

QueryResult TextQuery::Query(string_view sought) const {
  static shared_ptr<set<line_no>> nodata(make_shared<set<line_no>>());
  auto loc = wm_.find(sought.data());
  if (loc == wm_.end()) {
    return {sought.data(), nodata, file_};
  }
  return {sought.data(), loc->second, file_};
}

// Better than overload operator<<
std::ostream& Print(std::ostream& os, const QueryResult& qr) {
  fmt::print(os, "{} occurs {} {}\n", qr.sought_, qr.lines_->size(),
             (qr.lines_->size() > 1 ? "times" : "time"));
  for (auto num : *qr.lines_) {
    fmt::print(os, "\t(line {}) {}\n", num + 1, (*qr.file_)[num]);
  }
  return os;
}

void RunQueries(ifstream& infile) {
  fmt::print(stdout, "test");
  TextQuery tq(infile);
  while (true) {
    fmt::print("enter word to look for, or q to quit: ");
    string s;
    if (!(cin >> s) || s == "q") {
      break;
    }
    seven::Print(cout, tq.Query(s));
  }
}
}  // namespace seven