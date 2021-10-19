#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>

using namespace std;
using ul = unsigned long;

class FishCaughtException: public exception {
public:
    const char* what() const noexcept override {
      return "Caught fish!";
    }
};

class BootCaughtException: public exception {
public:
    const char* what() const noexcept override {
      return "Caught boot!";
    }
};

class EmptySectorException: public exception {
public:
    const char* what() const noexcept override {
      return "This sector is empty!";
    }
};

class Sector {
    bool fish = false, boot = false;
public:
    Sector(bool i_fish, bool i_boot): fish(i_fish), boot(i_boot) {}
    Sector& operator= (const Sector* S) {
      this->boot = S->boot;
      this->fish = S->fish;
      return *this;
    }
    void fishing () const {
      if (fish) throw FishCaughtException();
      else if (boot) throw BootCaughtException();
      else throw EmptySectorException();
    }
};

class Pond {
    vector<Sector> pond;
public:
    Pond() {
      for (int i = 0; i < 3; i++) pond.emplace_back(false, true);
      pond.emplace_back(true, false);
      for (int i = 0; i < 5; i++) pond.emplace_back(false, false);

      srand(time(nullptr));
      for (ul i = pond.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Sector tmp = pond[j];
        pond[j] = pond[i];
        pond[i] = tmp;
      }
    }
    void fishing (int sector, int &count) {
      if (sector > 9 || sector < 1) throw out_of_range(to_string(sector));
      count++;
      pond[sector - 1].fishing();
    }
};

int main() {
  string guess;
  int co = 0;
  Pond P;
  while (true) {
    this_thread::sleep_for(chrono::milliseconds (100));
    cout << "Enter sector to fish: ";
    try {
      cin >> guess;
      for (auto &i: guess) if (!isnumber(i)) throw invalid_argument(guess);
      P.fishing(stoi(guess), co);
    }
    catch (const FishCaughtException &x) {
      cerr << x.what() << endl;
      this_thread::sleep_for(chrono::milliseconds (100));
      cout << "You win! Total tries: " << co << endl;
      break;
    }
    catch (const BootCaughtException &x) {
      cerr << x.what() << endl;
      this_thread::sleep_for(chrono::milliseconds (100));
      cout << "You lose! Total tries: " << co << endl;
      break;
    }
    catch (const EmptySectorException &x) {
      cerr << x.what() << endl;
    }
    catch (const out_of_range &x) {
      cerr << "Incorrect sector: " << x.what() << endl;
    }
    catch (const invalid_argument &x) {
      cerr << "Incorrect argument type: " << x.what() << endl;
    }
    catch (...) {
      cout << "Something went wrong..." << endl;
    }
  }
  return 0;
}
