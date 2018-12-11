#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include "bst_list.hpp"
#include <utility>
#include <ostream>

template <typename KEY,typename VALUE>
class Map{
private:
  struct MapNode
  {
    std::pair<KEY,VALUE> p;
    bool operator <= (MapNode other){ return p.first <= other.p.first;}
    bool operator >= (MapNode other){ return p.first >= other.p.first;}
    bool operator == (MapNode* other)
    {
      if(other == NULL) return p.first == NULL;
      return p.first == other->p.first;
    }
    bool operator > (MapNode other){ return p.first > other.p.first;}
    bool operator < (MapNode other){ return p.first > other.p.first;}
    friend std::ostream& operator << (std::ostream& os, MapNode& mn){ os << mn.p.second; return os;}
    MapNode& operator = (MapNode* other)
    {
      if(other == NULL)
      {
        p.first = NULL;
        p.second = NULL;
        return *this;
      }
      p = other->p;
      return *this;
    }
  };
  BST_LIST<MapNode> bst_;

public:
  void Insert(KEY add_key,VALUE add_value);
  void Lookup(KEY key);
  void Delete(KEY Key);
  void Reasign(KEY key,VALUE reasign_value);
};

template <typename KEY,typename VALUE>
void Map<KEY,VALUE>::Insert(KEY add_key,VALUE add_value)
{
  MapNode n;
  n.p = std::make_pair(add_key,add_value);
  bst_.Insert(n);
}

template <typename KEY,typename VALUE>
void Map<KEY,VALUE>::Lookup(KEY key)
{
  MapNode n;
  n.p = std::make_pair(key,NULL);
  bst_.Find(n);
}

template <typename KEY,typename VALUE>
void Map<KEY,VALUE>::Delete(KEY key)
{
  MapNode n;
  n.p = std::make_pair(key,NULL);
  bst_.Delete(n);
}

template <typename KEY,typename VALUE>
void Map<KEY,VALUE>::Reasign(KEY key,VALUE reasign_value)
{
  MapNode n;
  n.p = std::make_pair(key,reasign_value);
  if( bst_.Find(n) ) bst_.Insert(n);
}

#endif
