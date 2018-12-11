#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class BST {
private:
  int size = 0;
  vector <int> Tree_arr;
public:
  BST(){
    printf("Klasa BST stworzona\n");
  }
  BST(const BST &bst){
    Tree_arr = bst.Tree_arr;
    size = bst.size;
    printf("Klasa BST skopiowana\n");
  }
  virtual ~BST ();
  void Insert_At_the_End(int x);
  void Find(int x);
  void FindParentOfX(int x, int root);
};

virtual BST::~BST (){
  printf("Klasa BST zniszczona\n");
}

void BST::Insert_At_the_End(int x){
  Tree_arr.push_back(x);
  size = Tree_arr.size();
  printf("Dodano element: %i\n",x );
}

void BST::Find(int x){
  int i = 0;
  while (Tree_arr[i] != x) i++;
  printf("%i znaleziony w wezle nr: %i\n",x ,i);
}

void BST::FindParentOfX(int x, int root){
  if(Tree_arr[2*root+1] == x || Tree_arr[2*root+2] == x) printf("Parent dla wezla %i to %i\n",x ,Tree_arr[root] );
  else{
    if(2*root+1 < size) FindParentOfX(x, 2*root+1);
    if(2*root+2 < size) FindParentOfX(x, 2*root+2);
  }
}

int main() {
  BST bst;
  bst.Insert_At_the_End(1);
  bst.Insert_At_the_End(4);
  bst.Insert_At_the_End(7);
  bst.Insert_At_the_End(3);
  bst.Insert_At_the_End(2);
  bst.Insert_At_the_End(5);
  bst.Insert_At_the_End(9);
  bst.Find(7);
  BST better(bst); // konstruktor kopiujacy
  //better = bst; // przypisanie
  better.Find(7);
  better.FindParentOfX(3,0);
  return 0;
}
