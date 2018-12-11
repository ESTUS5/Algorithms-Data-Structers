#pragma once
#ifndef MY_HEADER_HPP
#define MY_HEADER_HPP

#include <memory>
#include <assert.h>

using namespace std;

template <typename T>
struct node {
  T data;
  unique_ptr<node> left;
  unique_ptr<node> right;
};

template <typename T>
class BST_LIST{
public:
  node<T>* root;

public:
  BST_LIST();
  BST_LIST(const BST_LIST &bst);
  BST_LIST& operator=(const BST_LIST &bst);
  BST_LIST(BST_LIST &&bst);
  BST_LIST& operator=(BST_LIST &&bst);
  ~BST_LIST();

public:
  void Insert(const T x);
  node* Find(const T x);
  node* FindParent(const T x);
  node* Delete(const T x);
};

template <typename T>
BST_LIST<T>::BST_LIST():root(new node<T>){}
template <typename T>
BST_LIST<T>::~BST_LIST()
  {
    delete root;
  }
//COPY CONSTRUCTOR
template <typename T>
BST_LIST<T>::BST_LIST(const BST_LIST<T> &bst):root(bst.root){}
//ASSGINMENT OPERATOR
template <typename T>
BST_LIST<T> & BST_LIST<T>::operator=(const BST_LIST& bst)
{
  if(this != &bst)
  {
    root = bst.root;
  }
  return *this;
}
//ASSGINMENT OPERATOR
template <typename T>
BST_LIST<T> & BST_LIST<T>::operator=(BST_LIST &&bst)
{
  if(this != &bst)
  {
    root = exchange(bst.root, nullptr);
  }
  return *this;
}
//MOVE CONSTRUCTOR
template <typename T>
BST_LIST<T>::BST_LIST(BST_LIST<T> &&bst):root(move(bst.root)){}

template <typename T>
void BST_LIST<T>::Insert(T x)
{
  if(root->data == NULL)
  {
    root->data = x;
    std::cout << "Dodano element: " << x << "\n";
  }
  else
  {
    node<T>* deeper_node = root;
    node<T>* less_deeper_node;
    while (deeper_node != NULL)
    {
      less_deeper_node = deeper_node;
      if(deeper_node->data <= x)
      {
        deeper_node = deeper_node->right.get();
      }
      else
      {
        deeper_node = deeper_node->left.get();
      }
    }

    if(less_deeper_node->data < x)
    {
      less_deeper_node->right.reset(new node<T>);
      less_deeper_node->right->data = x;
    }
    else if(less_deeper_node->data > x)
    {
      less_deeper_node->left.reset(new node<T>);
      less_deeper_node->left->data = x;
    }
    else
    {
      less_deeper_node->data = x;
    }
    std::cout << "Dodano element: " << x << "\n";

  }
}
template <typename T>
bool BST_LIST<T>::Find(const T x)
{
  if(root == NULL)
  {
    printf("Nie ma elementow\n");
  }
  else
  {
    node<T>* node_to_find = root;
    while (node_to_find != NULL)
    {
      if(node_to_find->data < x)
      {
        node_to_find = node_to_find->right.get();
      }
      else if(node_to_find->data > x)
      {
        node_to_find = node_to_find->left.get();
      }
      else
      {
        std::cout << "Znaleziono: " << node_to_find->data << '\n';
        return true;
      }
    }
    printf("Nie ma elemetu\n");
    return false;
  }
}
template <typename T>
bool BST_LIST<T>::FindParent(const T x)
{
  if(root == NULL)
  {
    printf("Nie ma elementow\n");
  }
  else
  {
    node<T>* node_to_find = root;
    node<T>* parent;
    while (node_to_find != NULL)
    {
      if(node_to_find->data < x)
      {
        parent = node_to_find;
        node_to_find = node_to_find->right.get();
      }
      else if(node_to_find->data > x)
      {
        parent = node_to_find;
        node_to_find = node_to_find->left.get();
      }
      if(node_to_find->data == x)
      {
        printf("Parent dla %i to %i\n",x,parent->data );
        break;
      }
    }
    if(node_to_find->data != x)
    {
      printf("Nie ma elemetu\n");
    }
  }
}
template <typename T>
bool BST_LIST<T>::Delete(const T x)
{
  if(root == NULL)
  {
    printf("Nie ma elementow do usuniecia\n");
  }
  else
  {
    node<T>* node_to_delete = root;
    node<T>* parent = NULL;
    do
    {
      if(node_to_delete->data > x)
      {
        parent = node_to_delete;
        node_to_delete = node_to_delete->left.get();
      }
      else if(node_to_delete->data < x)
      {
        parent = node_to_delete;
        node_to_delete = node_to_delete->right.get();
      }
      else
      {
        assert(node_to_delete != NULL);
        break;
      }
    }while (node_to_delete != NULL);
    if(node_to_delete == NULL)
    {
      printf("Nie ma elementu do usuniecia\n");
    }
    else
    {
      if(node_to_delete->right == NULL && node_to_delete->left == NULL)
      {
        if(parent == NULL)
        {
          assert(node_to_delete == root);
          std::cout << "Usunieto: " << node_to_delete->data << '\n';
          root->data = NULL;
        }
        else
        {
          if(node_to_delete->data < parent->data)
          {
            parent->left.reset();
          }
          else
          {
            parent->right.reset();
          }

        }
      }
      else if(node_to_delete->right == NULL || node_to_delete->left == NULL)
      {
        node<T>* child;
        if(node_to_delete->right != NULL)
        {
          child = node_to_delete->right.get();
        }
        else
        {
          child = node_to_delete->left.get();
        }

        if(parent == NULL)
        {
          root = child;
        }
        else
        {
          if(child->data > parent->data)
          {
            parent->right = move(node_to_delete->right);
          }
          else
          {
            parent->left = move(node_to_delete->left);
          }
        }
      }
      else
      {
        node<T>* parent_replacement = node_to_delete;
        node<T>* replacement = node_to_delete->left.get();
        while (replacement->right != NULL)
        {
          parent_replacement = replacement;
          replacement = replacement->right.get();
        }
        node_to_delete->data = replacement->data;
        if(replacement->right == NULL)
        {
          node_to_delete->left = move(replacement->left);
        }
        else
        {
          parent_replacement->right = move(replacement->left);
        }
      }
    }
  }
}

#endif // MY_HEADER_HPP
