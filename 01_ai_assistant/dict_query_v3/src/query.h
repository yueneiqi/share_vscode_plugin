#ifndef QUERY_H
#define QUERY_H

#include "text_query.h"

namespace seven {
class QueryBase {
  friend class Query;

 protected:
  using line_no = TextQuery::line_no;
  virtual ~QueryBase() = default;

 private:
  // Eval returns the QueryResult that matches a given word
  [[nodiscard]] virtual QueryResult Eval(const TextQuery&) const = 0;
  // Rep is a string representation of the query
  [[nodiscard]] virtual string Rep() const = 0;
};

// interface class to manage the `QueryResult` inheritance hirarchy
class Query {
  friend Query operator~(const Query&);
  friend Query operator|(const Query&, const Query&);
  friend Query operator&(const Query&, const Query&);

 public:
  explicit Query(string_view);

  [[nodiscard]] QueryResult Eval(const TextQuery& t) const {
    return q_->Eval(t);
  }
  [[nodiscard]] string Rep() const {
    return q_->Rep();
  }

 private:
  explicit Query(shared_ptr<QueryBase> query) : q_(std::move(query)) {}

  shared_ptr<QueryBase> q_;
};

ostream& operator<<(ostream& os, const Query& query);

class WordQuery : public QueryBase {
  // TODO(seven): implement `MakeShared`

  friend class Query;
  explicit WordQuery(string_view sv) : query_word_(sv) {}
  [[nodiscard]] QueryResult Eval(const TextQuery& t) const override {
    return t.Query(query_word_);
  }
  [[nodiscard]] string Rep() const override {
    return query_word_;
  }

  string query_word_;
};

inline Query::Query(string_view sv)
    : q_(WordQuery::MakeShared(sv)) {}  

class NotQuery : public QueryBase {
  // TODO(seven): implement `MakeShared`

  friend Query operator~(const Query&);
  explicit NotQuery(const Query& q) : query_(std::move(q)) {}
  [[nodiscard]] QueryResult Eval(const TextQuery& t) const override;
  [[nodiscard]] string Rep() const override {
    return "~(" + query_.Rep() + ")";
  }

  Query query_;
};

inline Query operator~(const Query& operand) {
  // return static_cast<Query>(shared_ptr<QueryBase>(new NotQuery(operand)));
  return static_cast<Query>(NotQuery::MakeShared(operand));
}

class BinaryQuery : public QueryBase {
 protected:
  BinaryQuery(const Query& l, const Query& r, string_view s)
      : lhs_(std::move(l)), rhs_(std::move(r)), op_sym_(s) {}

  [[nodiscard]] string Rep() const override {
    return "(" + lhs_.Rep() + " " + op_sym_ + " " + rhs_.Rep() + ")";
  }

  Query lhs_, rhs_;
  string op_sym_;
};

class AndQuery : public BinaryQuery {
  // TODO(seven): implement `MakeShared`

  friend Query operator&(const Query&, const Query&);
  AndQuery(const Query& left, const Query& right)
      : BinaryQuery(left, right, "&") {}
  [[nodiscard]] QueryResult Eval(const TextQuery& t) const override;
};

inline Query operator&(const Query& lhs, const Query& rhs) {
  // return static_cast<Query>(shared_ptr<QueryBase>(new AndQuery(lhs, rhs)));
  return static_cast<Query>(AndQuery::MakeShared(lhs, rhs));
}

class OrQuery : public BinaryQuery {
  // TODO(seven): implement `MakeShared`

  friend Query operator|(const Query&, const Query&);
  OrQuery(const Query& left, const Query& right)
      : BinaryQuery(left, right, "|") {}
  [[nodiscard]] QueryResult Eval(const TextQuery&) const override;
};

inline Query operator|(const Query& lhs, const Query& rhs) {
  // return static_cast<Query>(shared_ptr<QueryBase>(new OrQuery(lhs, rhs)));
  return static_cast<Query>(OrQuery::MakeShared(lhs, rhs));
}

}  // namespace seven

#endif  // QUERY_H