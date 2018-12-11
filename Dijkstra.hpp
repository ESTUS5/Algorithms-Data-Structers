#pragma once
#include <vector>
#include <limits>
#include <utility>
#include <list>
#include <deque>
#include <queue>
#include <set>
#include <functional>

#include "Graph.hpp"

template <typename V, typename E>
std::pair<double, std::deque<int>> Dijkstra(Graph<V, E> &graph, int source, int destination)
{
    double limit = std::numeric_limits<double>::max();
    int nrOfVertices_ = graph.nrOfVertices();

    std::vector<int> unvisited;
    std::vector<int> path(nrOfVertices_,-1);
    std::vector<double> distance(nrOfVertices_,limit);
    unvisited.reserve(nrOfVertices_);

    for (int k = 0; k < nrOfVertices_; k++)
    {
        unvisited.push_back(k);
    }
    distance[source] = 0.0;

    while (!unvisited.empty())
    {
        double min_distance = limit;
        int temp;
        int min_index = -1;

        for (int i = 0; i < unvisited.size(); i++)
        {
            if (distance[unvisited[i]] <= min_distance)
            {
                min_distance = distance[unvisited[i]];
                min_index = i;
            }
        }
        temp = min_index;
        min_index = unvisited[temp];
        unvisited.erase(unvisited.begin() + temp);

        for (int i = 0; i < unvisited.size(); i++)
        {

            if (graph.matrix_neighbour[min_index][unvisited[i]] != NULL)
            {

                min_distance = distance[min_index] + graph.matrix_neighbour[min_index][unvisited[i]];

                if (min_distance < distance[unvisited[i]])
                {
                    distance[unvisited[i]] = min_distance;
                    path[unvisited[i]] = min_index;
                }
            }
        }
    }
    std::deque<int> final_path;
    int temp = destination;
    while (path[temp] != -1)
    {
        final_path.push_front(temp);
        temp = path[temp];
    }
    final_path.push_front(temp);

    return (std::pair<double, std::deque<int>>(distance[destination], final_path));
}
