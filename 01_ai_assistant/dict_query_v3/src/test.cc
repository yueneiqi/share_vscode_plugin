#include "query.h"

int main(int argc, char *argv[]) {
  using seven::Query;
  using seven::TextQuery;

  ARGS_CHECK(argc, 2);

  ifstream is(argv[1]);
  TextQuery t1(is);
  string word;
  Query q = ((Query("fiery")) & (Query("bird"))) | (Query("wind"));
  // Query q = Query("fiery");
  // Query q = Query("A");
  std::cout << q << std::endl;
  seven::Print(cout, q.Eval(t1));
}