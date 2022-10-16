#include <iostream>

template <typename T> class DynamicArray {
private:
  T *m_array;
  int m_length;

public:
  DynamicArray(int length) : m_array(new T[length]), m_length(length) {}

  ~DynamicArray() { delete[] m_array; }

  // Copy constructor
  DynamicArray(const DynamicArray &arr) : m_length(arr.m_length) {
    m_array = new T[m_length];
    for (int i = 0; i < m_length; ++i)
      m_array[i] = arr.m_array[i];
  }

  // Copy assignment
  DynamicArray &operator=(const DynamicArray &arr) {
    if (&arr == this)
      return *this;

    delete[] m_array;

    m_length = arr.m_length;
    m_array = new T[m_length];

    for (int i = 0; i < m_length; ++i)
      m_array[i] = arr.m_array[i];

    return *this;
  }

  int getLength() const { return m_length; }
  T &operator[](int index) { return m_array[index]; }
  const T &operator[](int index) const { return m_array[index]; }
};

template <typename T> class DynamicArray_2 {
private:
  T *m_array;
  int m_length;

public:
  DynamicArray_2(int length) : m_array(new T[length]), m_length(length) {}

  ~DynamicArray_2() { delete[] m_array; }

  // Move constructor
  DynamicArray_2(DynamicArray_2 &&arr) noexcept
      : m_array(arr.m_array), m_length(arr.m_length) {
    arr.m_length = 0;
    arr.m_array = nullptr;
  }

  // Move assignment
  DynamicArray_2 &operator=(DynamicArray_2 &&arr) {
    if (&arr == this)
      return *this;

    delete[] m_array;

    m_length = arr.m_length;
    m_array = arr.m_array;

    arr.m_length = 0;
    arr.m_array = nullptr;

    return *this;
  }

  int getLength() const { return m_length; }
  T &operator[](int index) { return m_array[index]; }
  const T &operator[](int index) const { return m_array[index]; }
};