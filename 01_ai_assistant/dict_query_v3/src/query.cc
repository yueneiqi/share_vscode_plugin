#include "query.h"

namespace seven {

ostream& operator<<(ostream& os, const Query& query) {
  return os << query.Rep();
}

QueryResult NotQuery::Eval(const TextQuery& text) const {
  auto result = query_.Eval(text);
  auto ret_lines = make_shared<set<line_no>>();
  auto beg = result.Begin();
  auto end = result.End();
  auto sz = result.GetFile()->size();
  for (size_t n = 0; n < sz; ++n) {
    if (beg == end || *beg != n) {
      ret_lines->insert(n);
    } else if (beg != end) {
      ++beg;
    }
  }
  return QueryResult(Rep(), ret_lines, result.GetFile());
}

QueryResult AndQuery::Eval(const TextQuery& text) const {
  auto left = lhs_.Eval(text);
  auto right = rhs_.Eval(text);
  auto ret_lines = make_shared<set<line_no>>();
  std::set_intersection(left.Begin(), left.End(), right.Begin(), right.End(),
                        std::inserter(*ret_lines, ret_lines->begin()));
  return QueryResult(Rep(), ret_lines, left.GetFile());
}

QueryResult OrQuery::Eval(const TextQuery& text) const {
  auto left = lhs_.Eval(text);
  auto right = rhs_.Eval(text);
  auto ret_lines = make_shared<set<line_no>>(left.Begin(), left.End());
  ret_lines->insert(right.Begin(), right.End());
  return QueryResult(Rep(), ret_lines, left.GetFile());
}

}  // namespace seven