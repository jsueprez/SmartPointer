#include <iostream>

// With default copy semantics
template <typename T> class Auto_ptr1 {
  T *m_ptr;

public:
  Auto_ptr1(T *ptr = nullptr) : m_ptr(ptr) {}
  ~Auto_ptr1() { delete m_ptr; }

  T &operator*() const { return *m_ptr; }
  T *operator->() const { return m_ptr; }
};

// Copy semantics redefined to implement move semantics. (Shallow copy)
template <typename T> class Auto_ptr2 {
  T *m_ptr;

public:
  Auto_ptr2(T *ptr = nullptr) : m_ptr(ptr) {}
  ~Auto_ptr2() { delete m_ptr; }

  // copy consturctor with move semantincs
  Auto_ptr2(Auto_ptr2 &a) {
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
  }

  Auto_ptr2 &operator=(Auto_ptr2 &a) {
    if (&a == this)
      return *this;

    delete m_ptr; // make sure we deallocate any pointer the destination is
    // already holding
    m_ptr = a.m_ptr;   // transfer the dumb pointer from the source to the dest
    a.m_ptr = nullptr; // make sure the source no longer owns the pointer
    return *this;
  }

  T &operator*() const { return *m_ptr; }
  T *operator->() const { return m_ptr; }
  bool isnull() const { return m_ptr == nullptr; }
};

// Copy semantics redefined to implement move semantics.(Doing deep copy)
template <typename T> class Auto_ptr3 {
  T *m_ptr;

public:
  Auto_ptr3(T *ptr = nullptr) : m_ptr(ptr) {}
  ~Auto_ptr3() { delete m_ptr; }

  // Copy constructor
  // Do deep copy of a.m_ptr to m_ptr
  Auto_ptr3(const Auto_ptr3 &a) {
    m_ptr = new T;
    *m_ptr = *a.m_ptr;
  }

  Auto_ptr3 &operator=(const Auto_ptr3 &a) {
    // Self-assignment detection
    if (&a == this)
      return *this;

    // Release any resource we're holding
    delete m_ptr;

    m_ptr = new T;
    *m_ptr = *a.m_ptr; // transfer the dumb pointer from the source to the dest
    return *this;
  }

  T &operator*() const { return *m_ptr; }
  T *operator->() const { return m_ptr; }
  bool isnull() const { return m_ptr == nullptr; }
};

// Finally using move semantics
template <typename T> class Auto_ptr4 {
  T *m_ptr;

public:
  Auto_ptr4(T *ptr = nullptr) : m_ptr(ptr) {}
  ~Auto_ptr4() { delete m_ptr; }

  // Move constructor
  // Transfer ownership of a.m_ptr to m_ptr
  Auto_ptr4(Auto_ptr4 &&a) noexcept : m_ptr(a.m_ptr) { a.m_ptr = nullptr; }

  Auto_ptr4 &operator=(Auto_ptr4 &&a) noexcept {
    // Self-assignment detection
    if (&a == this)
      return *this;

    // Release any resource we're holding
    delete m_ptr;

    // Transfer ownership of a.m_ptr to m_ptr
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
    return *this;
  }

  T &operator*() const { return *m_ptr; }
  T *operator->() const { return m_ptr; }
  bool isnull() const { return m_ptr == nullptr; }
};

class Resource {
public:
  Resource() { std::cout << "Resource aquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
  void sayHi() { std::cout << "Hi\n"; }
};