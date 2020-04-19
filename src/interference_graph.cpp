#include "interference_graph.h"

void InterferenceGraph::addNode (std::string nodeId)
{
    nodes_.insert_or_assign(nodeId, InterferenceGraphNode{ .id = nodeId });
}

void InterferenceGraph::connectNodes (std::string node1, std::string node2)
{
    nodes_[node1].neighbors.insert(node2);
    nodes_[node2].neighbors.insert(node1);
}

bool InterferenceGraph::areConnected (std::string node1, std::string node2) const
{
    return nodes_.at(node1).neighbors.count(node2) > 0;
}

void InterferenceGraph::colorGraph (int k)
{

}