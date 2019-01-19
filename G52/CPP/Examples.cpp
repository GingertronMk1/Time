#include <iostream>
#include <array>

using namespace std;

#if 0
void parti(double &i) {
  i = i*1.1;
}


class partii {
  public:
    partii() {};
    void operator() (double val) {
      cout << val << endl;
    };
};

// Part i: Global function will need to be added here // Part ii: Definition for Functor goes here
int main()
{
  // Calculate the total price - using function
  array<double,7> arrf = { 10.99,12.43,11.31,9.99,5.99,1.00,2.00 };
  for_each(arrf.begin(), arrf.end(), parti);

  // Part i: You need to use the global function here to add 10%
  // Output the final prices - using functor
  cout << "Final prices..." << endl;
  partii PrintVal;
  for_each(arrf.begin(), arrf.end(), PrintVal);

  // Part ii: You need to use the functor here to output prices
  // Calculate and output the final total price
  double dTotal = 0;
  for_each(arrf.begin(), arrf.end(), [&](double i)/*->void*/{dTotal += i;});
  // Part iii: You need to use a lambda function to calculate total
  cout << "Total is: " << dTotal << endl;
  return 0;
}

class BaseClass {
  private:
    int i, j, k;
  public:
    BaseClass() : i(10), j(50), k(97) {};
    friend class FriendClass;
};

class FriendClass {
  public:
    int f_i, f_j, f_k;
    FriendClass(BaseClass* b) : f_i(b->i), f_j(b->j), f_k(b->k) {};
    FriendClass() : f_i(8), f_j(6), f_k(7) {cout << "Default Constructor Used for FriendClass" << endl;};
    const void printVals() {
      cout << "FriendClass Values: " << endl
        << "f_i: " << f_i << endl
        << "f_j: " << f_j << endl
        << "f_k: " << f_k << endl;
    };
    FriendClass operator+ (int i) {
      f_i += i;
      f_j += i;
      f_k += i;
      cout << "Added " << i << " to all values in FriendClass" << endl;
      return *this;
    }
    FriendClass operator- (int i) {
      f_i -= i;
      f_j -= i;
      f_k -= i;
      cout << "Subtracted " << i << " from all values in FriendClass" << endl;
      return *this;
    }
    bool operator== (FriendClass &f1) {
      return f1.f_i == this->f_i && f1.f_j == this->f_j && f1.f_k == this->f_k;
    }
};

class FriendClassChild : public FriendClass {
  public:
    FriendClassChild() {cout <<  "FriendClassChild Values: " << f_i << ", " << f_j << ", " << f_k << endl;};

    //int f_i, f_j, f_k;
};

int main() {
  BaseClass b;
  FriendClass f(&b);
  FriendClass f2(&b);
  f.printVals();
  f = f + 6;
  f.printVals();
  printf("The values of f and f2 are: %s\n", (f == f2) ? "The Same" : "Different");
  f = f - 6;
  f.printVals();
  printf("The values of f and f2 are: %s\n", (f == f2) ? "The Same" : "Different");
  return 0;
}

#endif

static int staticglobal = 1;
int global = 2;

class MyClass
{
  private:
    int member;
    static int staticmember;
  public:
    MyClass()
    {
    staticmember = 10;
    member = 11;
    }
    void test1( int i1, int& i2 )
    {
      static int staticlocal = 20;
      int local = 21;
      cout << ++staticglobal  << ' ' << ++global << ' '
        << ++staticmember  << ' ' << ++member << ' '
        << ++staticlocal   << ' ' << ++local  << ' '
        << ++i1            << ' ' << ++i2     << endl;
    }
    // Note: test1 and test2 only differ in the initialisation values
    void test2( int i1, int& i2 )
    {
      static int staticlocal = 30;
      int local = 31;
      cout << ++staticglobal  << ' ' << ++global << ' '
        << ++staticmember  << ' ' << ++member << ' '
        << ++staticlocal   << ' ' << ++local  << ' '
        << ++i1            << ' ' << ++i2     << endl;
    }
};

int MyClass::staticmember = 40;
int main()
{
  int i = 50;
  int j = 51;

  cout << "ob1 created" << endl;
  MyClass ob1;
  cout << "ob1 test1 1: ";
  ob1.test1( i, j );
  cout << "ob1 test1 2: ";
  ob1.test1( i, j );
  cout << "ob2 created" << endl;
  MyClass ob2;
  cout << "ob1 test1 3: ";
  ob1.test1( i, j );
  cout << "ob2 test1 1: ";
  ob2.test1( i, j );
  cout << "ob2 test2 2: ";
  ob2.test2( i, j );
  cout << "ob1 test2 1: ";
  ob1.test2( i, j );
}

