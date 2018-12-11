#pragma once
#ifndef MY_GRAF_HPP
#define MY_GRAF_HPP

#include <vector>
#include <stack>
#include <queue>

template <typename V,typename E>
class Graph
{
  public:
    std::vector<V> vertexVector;
    std::vector< std::vector<E> > matrix_neighbour;
    std::size_t matrix_size;
  public:
    Graph();
  public:
    class VerticesIterator
    {
      public:
        VerticesIterator(Graph<V,E> &graph, std::size_t current_vertex_id = 0);
      private:
        Graph<V,E> *graph_ptr_;
        std::size_t current_vertex_id_;
      public:
        bool operator==(const VerticesIterator &vi) const ;
        bool operator!=(const VerticesIterator &vi) const ;
        VerticesIterator& operator++();//PREFIX
        VerticesIterator operator++(int); //POSTFIX
        V& operator*(); //OVERLOADING OPERATOR
    };
    class EdgesIterator
    {
      public:
        EdgesIterator(Graph<V,E> &graph, std::size_t nm_row = 0, std::size_t mn_col = 0);
      private:
        Graph<V,E> *graph_ptr_;
        std::size_t nm_row_;
        std::size_t mn_col_;
      public:
        bool operator==(const EdgesIterator &ei) const;
        bool operator!=(const EdgesIterator &ei) const;
        EdgesIterator& operator++();
        EdgesIterator operator++(int);
        E& operator*();
    };
    class DFSIterator
    {
      public:
        DFSIterator(Graph<V,E> &graph,int &current_vertex_id);
        DFSIterator();
      private:
        Graph<V,E> *graph_ptr_;
        std::vector<bool> visited;
        std::stack<int> vertex_id_stack;
      public:
        bool operator== (const DFSIterator &DFSi);
        bool operator!= (const DFSIterator &DFSi);
        DFSIterator& operator++();
        DFSIterator operator++(int);
        V& operator*();
    };
    class BFSIterator
    {
      public:
        BFSIterator(Graph<V,E> &graph,int &current_vertex_id);
        BFSIterator();
      private:
        Graph<V,E> *graph_ptr_;
        std::vector<bool> visited;
        std::queue<int> vertex_id_queue;
      public:
        bool operator== (const BFSIterator &BFSi);
        bool operator!= (const BFSIterator &BFSi);
        BFSIterator& operator++();
        BFSIterator operator++(int);
        V& operator*();
    };
  public:
    bool insertEdge(std::size_t vertex1_id,std::size_t vertex2_id,const E & label, bool replace = true);
    bool insertVertex(const V &vertex_data);
    bool removeEdge(std::size_t vertex1_id,std::size_t vertex2_id);
    bool removeVertex(std::size_t vertex_id);
  public:
    V& vertexData(std::size_t vertex_id);
    E& edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id);
    std::size_t nrOfVertices() const;
    std::size_t nrOfEdges() const;
    void printNeighborhoodMatrix() const;
  public:
    VerticesIterator beginVertices();
    VerticesIterator endVertices();
    EdgesIterator beginEdges();
    EdgesIterator endEdges();
    DFSIterator beginDFS(int first_index );
    DFSIterator endDFS();
    BFSIterator beginBFS(int first_index);
    BFSIterator endBFS();
};
template <typename V,typename E>
Graph<V,E>::Graph():matrix_size(0),W(0)
{}
template <typename V,typename E>
std::size_t Graph<V,E>::nrOfVertices() const
{
  return vertexVector.size();
}
template <typename V,typename E>
std::size_t Graph<V,E>::nrOfEdges() const
{
  int nr = 0;
  for (auto &row : matrix_neighbour)
  {
      for (auto &col : row )
      {
        if(col != NULL) nr++;
      }
  }
  return nr;
}
template <typename V,typename E>
void Graph<V,E>::printNeighborhoodMatrix() const
{
  for (auto &row : matrix_neighbour)
  {
      for (auto &col : row )
      {
        std::cout << col << " ";
      }
      std::cout << '\n';
  }
}
// INSERT EDGE
template <typename V,typename E>
bool Graph<V,E>::insertEdge(std::size_t vertex1_id,std::size_t vertex2_id,const E & label, bool replace)
{
  if(matrix_neighbour[vertex1_id][vertex2_id] == NULL || replace == true)
  {
    matrix_neighbour[vertex1_id][vertex2_id] = label;
    if(W < label) W = label;
    return replace;
  }
  replace = false;
  if(vertex1_id >= matrix_size || vertex2_id >= matrix_size)
  {
    printf("Out of matrix\n");
    return replace;
  }
  else
  {
    printf("Edge exsists\n");
    replace = false;
  }
}
// INSERT VERTEX
template <typename V,typename E>
bool Graph<V,E>::insertVertex(const V &vertex_data)
{
  //Dodanie elementu do tablicy węzłów
  vertexVector.push_back(vertex_data);
  //Dodanie kolumny...
  matrix_neighbour.resize( ++matrix_size );
  //... i wiersza do macierzy
  for( auto &it : matrix_neighbour )
  {
      it.resize( matrix_size );
  }
  return 1;
}
//REMOVE VERTEX
template <typename V,typename E>
bool Graph<V,E>::removeVertex(std::size_t vertex_id)
{
  if(vertexVector.size() <= vertex_id) return 0;

  vertexVector.erase(vertexVector.begin() + vertex_id);
  for (auto &it : matrix_neighbour)
  {
      it.erase(it.begin() + vertex_id );
  }
  matrix_neighbour.erase(matrix_neighbour.begin() + vertex_id );
  return 1;
}
//REMOVE EDGE
template <typename V,typename E>
bool Graph<V,E>::removeEdge(std::size_t vertex1_id,std::size_t vertex2_id)
{
  if(matrix_neighbour[vertex1_id][vertex2_id] == NULL || vertex1_id >= matrix_size || vertex2_id >= matrix_size) return 0;
  else
  {
    matrix_neighbour[vertex1_id][vertex2_id] = NULL;
    return 1;
  }
}
template<>
bool Graph<std::string,std::string>::removeEdge(std::size_t vertex1_id,std::size_t vertex2_id)
{
  if(matrix_neighbour[vertex1_id][vertex2_id] == "" || vertex1_id >= matrix_size || vertex2_id >= matrix_size) return 0;
  else
  {
    matrix_neighbour[vertex1_id][vertex2_id] =  "";
    return 1;
  }
}
// VERTEX Iterator
template<typename V,typename E>
Graph<V,E>::VerticesIterator::VerticesIterator(Graph<V,E> &graph, std::size_t current_vertex_id)
:
graph_ptr_(&graph) ,
current_vertex_id_(current_vertex_id)
{}
template<typename V,typename E>
bool Graph<V,E>::VerticesIterator::operator==(const VerticesIterator &vi) const
{
  return current_vertex_id_ == vi.current_vertex_id_;
}
template<typename V,typename E>
bool Graph<V,E>::VerticesIterator::operator!=(const VerticesIterator &vi) const
{
  return !(current_vertex_id_ == vi.current_vertex_id_);
}
template<typename V,typename E>
typename Graph<V,E>::VerticesIterator& Graph<V,E>::VerticesIterator::operator++()
{
  current_vertex_id_++; return *this; //PREFIX
}
template<typename V,typename E>
typename Graph<V,E>::VerticesIterator Graph<V,E>::VerticesIterator::operator++(int)
{
  VerticesIterator vi = *this; ++(*this); return vi; //POSTFIX
}
template<typename V,typename E>
V& Graph<V,E>::VerticesIterator::operator*()
{
  return graph_ptr_->vertexVector[current_vertex_id_]; //OVERLOADING OPERATOR
}
// EDGES Iterator
template<typename V,typename E>
Graph<V,E>::EdgesIterator::EdgesIterator(Graph<V,E> &graph, std::size_t nm_row, std::size_t mn_col)
 :
 graph_ptr_(&graph),
 nm_row_(nm_row),
 mn_col_(mn_col)
 {}
template<typename V,typename E>
bool Graph<V,E>::EdgesIterator::operator==(const EdgesIterator &ei) const
{
  return ( (nm_row_ == ei.nm_row_) || (mn_col_ == ei.mn_col_) );
}
template<typename V,typename E>
bool Graph<V,E>::EdgesIterator::operator!=(const EdgesIterator &ei) const
{
  return !( (nm_row_ == ei.nm_row_) || (mn_col_ == ei.mn_col_) );
}
template<typename V,typename E>
typename Graph<V,E>::EdgesIterator& Graph<V,E>::EdgesIterator::operator++()
{
  ++mn_col_;
  if(mn_col_ > graph_ptr_->matrix_size)
  {
    mn_col_ = 0;
    nm_row_++;
  }
  return (*this);
}
template<typename V,typename E>
typename Graph<V,E>::EdgesIterator Graph<V,E>::EdgesIterator::operator++(int)
{
  EdgesIterator ei = *this;
  ++(*this);
  return ei;
}
template<typename V,typename E>
E& Graph<V,E>::EdgesIterator::operator*()
{
  return graph_ptr_->matrix_neighbour[nm_row_][mn_col_];
}
// DFS Iterator
template<typename V,typename E>
Graph<V,E>::DFSIterator::DFSIterator(Graph<V,E> &graph,int &current_vertex_id)
 :
 graph_ptr_(&graph)
 {
   visited.resize(graph_ptr_->matrix_size,false); // fill vector of visited with false
   vertex_id_stack.push(current_vertex_id);
 }
template<typename V,typename E>
Graph<V,E>::DFSIterator::DFSIterator(){};
template<typename V,typename E>
bool Graph<V,E>::DFSIterator::operator== (const DFSIterator &DFSi)
{
  return (vertex_id_stack == DFSi.vertex_id_stack);
}
template<typename V,typename E>
bool Graph<V,E>::DFSIterator::operator!= (const DFSIterator &DFSi)
{
  return !((*this) == DFSi);
}
template<typename V,typename E>
typename Graph<V,E>::DFSIterator& Graph<V,E>::DFSIterator::operator++()
{
  int current_index;
  if (vertex_id_stack.empty())
  {
    current_index = -1;
    return *this;
  }
  current_index = vertex_id_stack.top();
  visited[current_index] = true;
  vertex_id_stack.pop();

  auto vertex_neighbours = graph_ptr_->matrix_neighbour[current_index];
  for(size_t i = 0; i < vertex_neighbours.size(); ++i)
  {
    if( visited[i] == false)
    {
      if(vertex_neighbours[i] != NULL)
      {
        if (i != current_index)
        {
          vertex_id_stack.push(i);
          visited[i] = true;
        }
      }
    }
  }
  return *this;
}
template<typename V,typename E>
typename Graph<V,E>::DFSIterator Graph<V,E>::DFSIterator::operator++(int)
{
  DFSIterator DFSi = *this;
  ++*this;
  return DFSi;
}
template<typename V,typename E>
V& Graph<V,E>::DFSIterator::operator*()
{
  return graph_ptr_->vertexVector[vertex_id_stack.top()];
}

// BFS Iterator
template<typename V,typename E>
Graph<V,E>::BFSIterator::BFSIterator(Graph<V,E> &graph,int &current_vertex_id)
 :
 graph_ptr_(&graph)
 {
  visited.resize(graph_ptr_->matrix_size,false); // fill vector of visited with false
  vertex_id_queue.push(current_vertex_id);
}
template<typename V,typename E>
Graph<V,E>::BFSIterator::BFSIterator(){};
template<typename V,typename E>
bool Graph<V,E>::BFSIterator::operator== (const BFSIterator &BFSi)
{
  return (vertex_id_queue == BFSi.vertex_id_queue);
}
template<typename V,typename E>
bool Graph<V,E>::BFSIterator::operator!= (const BFSIterator &BFSi)
{
  return !((*this) == BFSi);
}
template<typename V,typename E>
typename Graph<V,E>::BFSIterator& Graph<V,E>::BFSIterator::operator++()
{
          int current_index;
          if (vertex_id_queue.empty())
          {
            current_index = -1;
            return *this;
          }
          current_index = vertex_id_queue.front();
          visited[current_index] = true;
          vertex_id_queue.pop();

           auto vertex_neighbours = graph_ptr_->matrix_neighbour[current_index];
           for(size_t i = 0; i < vertex_neighbours.size(); ++i)
           {
             if( visited[i] == false)
             {
               if (vertex_neighbours[i] != NULL)
               {
                 if (i != current_index)
                 {
                     vertex_id_queue.push(i);
                     visited[i] = true;
                 }
               }
             }
           }
           return *this;
       }
template<typename V,typename E>
typename Graph<V,E>::BFSIterator Graph<V,E>::BFSIterator::operator++(int)
{
  BFSIterator BFSi = *this;
  ++*this;
  return BFSi;
}
template<typename V,typename E>
V& Graph<V,E>::BFSIterator::operator*()
{
  return graph_ptr_->vertexVector[vertex_id_queue.front()];
}

//BEGIN END FUNCTIONS
template<typename V,typename E>
typename Graph<V,E>::VerticesIterator Graph<V,E>::beginVertices()
{
  return VerticesIterator(*this);
}
template<typename V,typename E>
typename Graph<V,E>::VerticesIterator Graph<V,E>::endVertices()
{
  return VerticesIterator(*this,this->matrix_size);
}
template<typename V,typename E>
typename Graph<V,E>::EdgesIterator Graph<V,E>::beginEdges()
{
  return EdgesIterator(*this);
}
template<typename V,typename E>
typename Graph<V,E>::EdgesIterator Graph<V,E>::endEdges()
{
  return EdgesIterator(*this,this->matrix_size, this->matrix_size);
}
template<typename V,typename E>
typename Graph<V,E>::DFSIterator Graph<V,E>::beginDFS(int first_index )
{
  return DFSIterator(*this,first_index);
}
template<typename V,typename E>
typename Graph<V,E>::DFSIterator Graph<V,E>::endDFS()
{
  return DFSIterator();
}
template<typename V,typename E>
typename Graph<V,E>::BFSIterator Graph<V,E>::beginBFS(int first_index)
{
  return BFSIterator(*this,first_index);
}
template<typename V,typename E>
typename Graph<V,E>::BFSIterator Graph<V,E>::endBFS()
{
  return BFSIterator();
}
#endif
