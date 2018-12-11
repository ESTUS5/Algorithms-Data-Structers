#pragma once
#include<bitset>

class UniversalSet
{
public:
  UniversalSet();
  virtual ~UniversalSet();
  int* CreateUS(int input);
  auto CreateEigen(int input);
  void Add();
  void Subtract();
  void Multiply();
  void Divide();
};

UniversalSet::UniversalSet(){

}
UniversalSet::~UniversalSet(){

}
int* UniversalSet::CreateUS(int input){
  int a[]={input};
  return a;
}
/*
auto UniversalSet::CreateEigen(int input){
  std::bitset<8> eigen(string(input));
  return eigen;
}
*/
