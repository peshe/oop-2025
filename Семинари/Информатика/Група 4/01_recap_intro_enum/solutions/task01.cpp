typedef unsigned (*OneParamFunction) (unsigned);
typedef unsigned (*TwoParamFunction) (unsigned, unsigned);

unsigned factorial(unsigned n) {
  unsigned result = 1;
  for (unsigned i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

unsigned square(unsigned n) {
  return n * n;
}

unsigned g(OneParamFunction f, unsigned n) {
  unsigned result = 0;
  for (unsigned i = 1; i <= n; ++i) {
    result += f(i);
  }
  return result;
}


void task1() {
  cout << "S = 1 + 2^2 + 3^2 + ... + 10^2 = " << g(square, 10) << endl;
  cout << "S = 1 + 2! + ... + 6! = " << g(factorial, 6) << endl;
}
