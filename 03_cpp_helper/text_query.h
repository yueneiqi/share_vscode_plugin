#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H


namespace seven {
class QueryResult;

class TextQuery {
 public:
  using line_no = QueryResult::line_no;
  explicit TextQuery(ifstream &);
  [[nodiscard]] QueryResult Query(string_view) const;

 private:
  shared_ptr<vector<string>> file_;
  // map of each word to the set of the lines in which that word appears
  map<string, shared_ptr<set<line_no>>> wm_;
};

void RunQueries(ifstream &infile);
}  // namespace seven

#endif  // TEXT_QUERY_H
