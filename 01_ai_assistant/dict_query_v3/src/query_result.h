#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include <my_hfile/mycpp17.h>

namespace seven {
class QueryResult {
  friend std::ostream &Print(std::ostream &, const QueryResult &);

 public:
  using line_no = std::vector<std::string>::size_type;
  QueryResult(string_view s, const shared_ptr<set<line_no>>& p,
              const shared_ptr<vector<string>> &f)
    : sought_(s), lines_(std::move(p)), file_(std::move(f)) {}

  [[nodiscard]] auto Begin() const { return lines_->begin(); };
  [[nodiscard]] auto End() const { return lines_->end(); };
  [[nodiscard]] auto GetFile() { return file_; }

 private:
  string_view sought_;
  const shared_ptr<set<line_no>> lines_;
  const shared_ptr<vector<string>> file_;
};

ostream &Print(ostream &, const QueryResult &);
} // namespace seven

#endif // QUERY_RESULT_H