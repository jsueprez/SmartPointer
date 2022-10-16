#include <iostream>

#include "dynamicArray.h"
#include "pointer.h"
#include "timer.h"

void someFunction() {
  Auto_ptr1<Resource> res(new Resource());

  int x;
  std::cout << "Enter an integer: ";
  std::cin >> x;

  if (x == 0)
    return;

  res->sayHi();
}

// Danling pointer
void passByValue(Auto_ptr1<Resource> res) { auto value{*res}; }

Auto_ptr3<Resource> generateResource3() {
  Auto_ptr3<Resource> res{new Resource};
  return res; // this return value will invoke the copy constructor
}

Auto_ptr4<Resource> generateResource4() {
  Auto_ptr4<Resource> res{new Resource};
  return res; // this return value will invoke the move constructor
}

// Return a copy of arr with all of the values doubled
DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr) {
  DynamicArray<int> dbl(arr.getLength());
  for (auto i{0}; i < arr.getLength(); i++) {
    dbl[i] = arr[i] * 2;
  }
  return dbl;
}
// Return a copy of arr with all of the values doubled
DynamicArray_2<int> cloneArrayAndDouble_2(const DynamicArray_2<int> &arr) {
  DynamicArray_2<int> dbl(arr.getLength());
  for (auto i{0}; i < arr.getLength(); i++) {
    dbl[i] = arr[i] * 2;
  }
  return dbl;
}

int main() {
  // someFunction();
  // Auto_ptr1<Resource> res1(new Resource());
  // when res2 get destroyed, it delete the Resource leaving res1 with a
  // dablging pointer. This is due to the default copy-constructor makes a
  // shallow copy. so both res1 and res2 are pointing to the same Resource.
  // Same happens with the function passByValue
  // Auto_ptr1<Resource> res2(res1);
  // passByValue(res2);

  // Auto_ptr2<Resource> res1(new Resource());
  // Auto_ptr2<Resource> res2;

  // std::cout << "res1 is " << (res1.isnull() ? "null\n" : "not null \n");
  // std::cout << "res2 is " << (res2.isnull() ? "null\n" : "not null \n");

  // res2 = res1; // res2 takes ownershipf the pointer, now res1 is set to null.
  // std::cout << "Ownership transferred\n";

  // std::cout << "res1 is " << (res1.isnull() ? "null\n" : "not null \n");
  // std::cout << "res2 is " << (res2.isnull() ? "null\n" : "not null \n");

  // std::cout << '\n';

  // Auto_ptr3<Resource> mainres;
  //  mainres = generateResource3();
  // Auto_ptr4<Resource> mainres;
  // mainres = generateResource4();

  Timer t;
  DynamicArray<int> arr(1000000);
  for (auto i{0}; i < arr.getLength(); i++) {
    arr[i] = i;
  }

  arr = cloneArrayAndDouble(arr);

  std::cout << t.elapsed() << '\n';
  Timer t2;
  DynamicArray_2<int> arr2(1000000);
  for (auto i{0}; i < arr2.getLength(); i++) {
    arr2[i] = i;
  }

  arr2 = cloneArrayAndDouble_2(arr2);

  std::cout << t2.elapsed() << '\n';
  return 0;
}