#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
NumericVector sort_rcpp(NumericVector x) {
  std::vector<double> tmp = Rcpp::as< std::vector<double> > (x);
  std::sort(tmp.begin(), tmp.end());
  return wrap(tmp);
}

// [[Rcpp::export]]
IntegerVector rank(NumericVector x) {
  return match(x, sort_rcpp(x));
}

// [[Rcpp::export]]
double auc_(NumericVector actual, NumericVector predicted) {

  IntegerVector Ranks = rank(predicted);
  int NPos = sum(actual == 1);
  int NNeg = actual.size() - NPos;

  int sumranks = 0;
  double n = actual.size();

  for(int i = 0; i < n; ++i) {
    if (actual[i] == 1){
      sumranks = sumranks + Ranks[i];
    }
  }

  double p1 = pow(n, -10) * (sumranks - NPos*( NPos + 1 ) / 2);
  long double p2 = pow(n, -10) * NPos*NNeg;

  double auc =  p1 / p2;
  return auc ;

}

