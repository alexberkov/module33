#include <iostream>
#include <vector>

using namespace std;

template <typename T1, typename T2>
class Container {
    vector<pair<T1,T2>> data;
public:
    void add(T1 key, T2 value);
    void remove(T1 key);
    void print();
    bool empty() { return data.empty(); }
    vector<pair<T1,T2>*> find(T1 key);
};

template <typename T1, typename T2>
void Container<T1,T2>::add(T1 key, T2 value) {
  data.push_back(make_pair(key, value));
}

template<typename T1, typename T2>
void Container<T1, T2>::print() {
  if (this->empty()) cout << "Container is empty!" << endl;
  else {
    cout << "Contents:" << endl;
    for (int i = 0; i < data.size(); i++) cout << "(" << data[i].first << ", " << data[i].second << ")" << endl;
    cout << endl;
  }
}

template<typename T1, typename T2>
vector<pair<T1, T2>*> Container<T1, T2>::find(T1 key) {
  vector<pair<T1, T2>*> res;
  if (this->empty()) cout << "Container is empty!" << endl;
  else for (int i = 0; i < data.size(); i++) if (data[i].first == key) res.push_back(&data[i]);
  return res;
}

template<typename T1, typename T2>
void Container<T1, T2>::remove(T1 key) {
  if (this->empty()) cout << "Container is empty!" << endl;
  else if (this->find(key).empty()) cout << "No such element found!" << endl;
  else for (int i = 0; i < data.size(); ) {
    if (data[i].first == key) {
      pair<T1,T2> tmp = data[i];
      data[i] = data[data.size() - 1];
      data[data.size() - 1] = tmp;
      data.pop_back();
    } else i++;
  }
}

template<typename T1, typename T2>
void showSearchResults(vector<pair<T1, T2>*> v) {
  if (v.empty()) cout << "No match found!" << endl;
  else {
    cout << "Search results:" << endl;
    for (int i = 0; i < v.size(); i++) cout << "(" << v[i]->first << ", " << v[i]->second << ")" << endl;
  }
  cout << endl;
}

int main() {
  Container<int,string> IS;
  Container<string,double> SD;
  Container<double,int> DI;
  for (int i = 0; i < 6; i++) {
    IS.add(i, (to_string(i) + "elem"));
    SD.add((to_string(i) + "pos"), ((double) i + 0.5));
    DI.add(((double) i + 0.3), i + 10);
  }
  IS.print();
  SD.print();
  DI.print();

  IS.remove(4);
  IS.add(2, "2elem");
  IS.print();
  showSearchResults(IS.find(4));
  IS.remove(2);
  IS.print();

  SD.remove("3pos");
  SD.add("5pos", 5.5);
  showSearchResults(SD.find("5pos"));
  SD.remove("5pos");
  SD.print();

  return 0;
}
