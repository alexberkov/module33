#include <iostream>
#include <vector>

using namespace std;

template <typename T>
double mean(vector<T> v) {
  T sum = 0;
  for (int i = 0; i < v.size(); i++) sum += v[i];
  return ((double) sum / v.size());
}

template <typename T>
void print(vector<T> v) {
  for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
  cout << endl;
}

int main() {
  vector<int> I;
  vector<double> D;
  vector<float> F;
  vector<long> L;
  vector<short> S;
  vector<unsigned long long> ULL;

  for (int i = 0; i < 10; i++) {
    I.push_back(i * 10);
    double j = (double) i + 0.4;
    D.push_back(j);
    F.push_back((float) (j - 0.2));
    L.push_back((long) (i * 100));
    S.push_back((short) (i));
    ULL.push_back((unsigned long long) (i * 100000));
  }

  print(I);
  print(D);
  print(F);
  print(L);
  print(S);
  print(ULL);
  cout << endl;

  cout << "int: "<< mean(I) << endl;
  cout << "double: " << mean(D) << endl;
  cout << "float: " << mean(F) << endl;
  cout << "long: " << mean(L) << endl;
  cout << "short: " << mean(S) << endl;
  cout << "unsigned long long: " << mean(ULL) << endl;

  return 0;
}
