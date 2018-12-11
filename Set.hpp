#pragma once
#ifndef SET_H
#define SET_H
#include <stack>

#include"bst_list.hpp"

template <typename T>
class Set {
public:
  Set ();
  Set(const Set &source);
  Set& operator =(const Set &source);
  Set(Set &&source);
  Set& operator =(Set &&source);

  virtual ~Set ();

private:
  BST_LIST<T> bst_;

public:
  T* insert(const T &value);
  const T* find(const T &value) const;
  T* find(const T &value); // użycie const T &value powstrzymuje kopiowanie
  bool remove(const T &value);
public:
  class Iterator;
  {
    private:
      std::stack<typename BST_LIST<T>::Node *> stack;
      typename BST_LIST<T>::Node * current;
    public:
      Iterator(typename BST_LIST<T>::Node *node);
      Iterator();
      bool operator==(const Iterator &it);
      bool operator!=(const Iterator &it);
      Iterator& operator=(const Iterator& it);
      Iterator& operator++();
      Iterator operator++(int);
      T& operator*();
  };
  Iterator begin();
  Iterator end();

};

template <typename T>
Set<T>::Set() {}
template <typename T>
Set<T>::Set(const Set &source):bst_(source.bst_) {}
template <typename T>
Set<T> & Set<T>::operator =(const Set &source)
{
  if(this != &source)
  {
    bst_ = source.bst_;
  }
  return *this;
}
template <typename T>
Set<T>::Set(Set &&source):bst_(std::move(source.bst_)) {}
template <typename T>
Set<T> & Set<T>::operator =(Set &&source)
{
  if(this != &source)
  {
    bst_ = std::move(source.bst_);
  }
  return *this;
}
template <typename T>
Set<T>::~Set(){}

template <typename T>
T* Set<T>::insert(const T &value)
{
  if(bst_.Find(value) == nullptr) return &bst_.Insert(value);
  return nullptr;
}
template <typename T>
const T* Set<T>::find(const T &value) const
{
  return &bst_.Find(value);
}
template <typename T>
T* Set<T>::find(const T &value) // użycie const T &value powstrzymuje kopiowanie
{
  T* value_ = &bst_.Find(value);
  return (value_ == nullptr) ? nullptr : &bst_.Find(value);
}
template <typename T>
bool Set<T>::remove(const T &value)
{
  return (bst_.Delete(&value) == nullptr) ? false : true;
}
//Iterator
Iterator(typename BST_LIST<T>::Node *node)
{
  current = node;
  if(node != nullptr)
  {
    stack.push_back(node);
  }
}
Iterator();
bool operator==(const Iterator &it)
{
  return current == it.current;
}
bool operator!=(const Iterator &it)
{
  return !(*this == it);
}
Iterator& operator=(const Iterator& it)
{
  bst_ = it.bst_;
  return *this;
}
Iterator& operator++()
{
  ++current;
  return *this;
}
Iterator operator++(int)
{
  Iterator it = *this;
  ++current;
  return it;
}
T& operator*()
{
  return current->value;
}
template <typename T>
Iterator Set<T>::Iterator::begin()
{
  return Iterator it(bst_.root());
}
template <typename T>
Iterator Set<T>::Iterator::end()
{
  return Iterator it(nullptr);
}
#endif
