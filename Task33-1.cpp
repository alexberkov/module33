#include <iostream>
#include <map>
#include <string>
#include <thread>

using namespace std;

class ItemNotExistException: public exception {
    const char* what() const noexcept override {
      return "No such item in store.";
    }
};

class ItemRanOutException: public exception {
    const char* what() const noexcept override {
      return "Item out of stock.";
    }
};

class NotEnoughItemException: public exception {
    const char* what() const noexcept override {
      return "Quantity not available.";
    }
};

class ItemNotInCart: public exception {
    const char* what() const noexcept override {
      return "No such item in cart.";
    }
};

class InvalidTypeException: public exception {
    const char* what() const noexcept override {
      return "Incorrect input type!";
    }
};

int check_entry(const string &entry) {
  int sep = (int) entry.find('-');
  if (sep == -1) throw invalid_argument(entry);
  else {
    string quantity = entry.substr(sep + 1);
    for (auto &i: quantity) if (!isnumber(i)) throw InvalidTypeException();
    if (stoi(quantity) <= 0) throw invalid_argument(quantity);
  }
  return sep;
}

void print(const map<string, int>& d, const string& name) {
  cout << name << ": " << endl;
  for (auto &i: d) cout << "\t" << i.first << " " << i.second << endl;
}

class ShoppingCart {
    map<string, int> cart;
public:
    void add(const string& article, map<string, int> &store);
    void remove(const string& article, map<string, int> &store);
    bool isEmpty() { return cart.empty(); }
    void show() { print(cart, "Cart"); }
};

void ShoppingCart::add(const string& article, map<string, int> &store) {
  int pos = check_entry(article);
  string item = article.substr(0, pos);
  string quantity = article.substr(pos + 1);
  int number = stoi(quantity);
  auto it = store.find(item);
  if (it != store.end()) {
    if (it->second == 0) throw ItemRanOutException();
    else if (number <= it->second) {
      cart.insert(make_pair(item, number));
      it->second -= number;
      cout << "Item added!" << endl;
    } else throw NotEnoughItemException();
  } else throw ItemNotExistException();
}

void ShoppingCart::remove(const string& article, map<string, int> &store) {
  int pos = check_entry(article);
  string item = article.substr(0, pos);
  string quantity = article.substr(pos + 1);
  int number = stoi(quantity);
  auto it = cart.find(item);
  if (it != cart.end()) {
    if (number <= it->second) {
      it->second -= number;
      store.find(item)->second += number;
      if (it->second == 0) cart.erase(it);
      cout << "Item removed!" << endl;
    } else throw NotEnoughItemException();
  } else throw ItemNotInCart();
}

int main() {
  map<string, int> store;
  string article, product;
  int total;
  // заполнение магазина, без исключений
  while (true) {
    cout << "Enter article and quantity: ";
    cin >> article;
    if (article == "end") break;
    int sep = (int) article.find('-');
    product = article.substr(0, sep);
    total = stoi(article.substr(sep + 1));
    store.insert(make_pair(product, total));
  }

  ShoppingCart S;
  string act;
  bool exit = false;
  while (!exit) {
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "\n1. Add to cart\n2. Remove from cart\n3. See cart\n4. See store\n5. Exit\nWhat do you want to do: ";
    cin >> act;
    cout << endl;
    try {
      for (auto &i: act) if (!isnumber(i)) throw InvalidTypeException();
      switch (stoi(act)) {
        case 1:
          cout << "Enter article and quantity: ";
          cin >> article;
          S.add(article, store);
          break;
        case 2:
          if (!S.isEmpty()) {
            cout << "Enter article and quantity: ";
            cin >> article;
            S.remove(article, store);
          } else cout << "Cart is empty!" << endl;
          break;
        case 3:
          if (!S.isEmpty()) S.show();
          else cout << "Cart is empty!" << endl;
          break;
        case 4:
          print(store, "Store");
          break;
        case 5:
          exit = true;
          break;
        default:
          throw invalid_argument(act);
      }
    }
    catch (const invalid_argument &x) {
      cerr << "Error: Invalid argument supplied - " << x.what() << endl;
    }
    catch (const exception &x) {
      cerr << "Error: " << x.what() << endl;
    }
    catch(...) {
      cerr << "Error: Something went wrong." << endl;
    }
  }
  return 0;
}
