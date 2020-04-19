#include "interference_graph.h"
#include <stack>

void InterferenceGraph::addNode (std::string nodeId, int cost)
{
    nodes_.insert_or_assign(nodeId, InterferenceGraphNode{ .id = nodeId, .cost = cost });
}

void InterferenceGraph::removeNode (std::string nodeId)
{
    for (auto & neighbor : nodes_[nodeId].neighbors)
    {
        nodes_[neighbor].neighbors.erase(nodeId);
    }

    nodes_.erase(nodeId);
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

void InterferenceGraph::colorGraph ()
{
    // create a clone to use a scratchpad, cause nodes will be removed
    InterferenceGraph workGraph = *this;
    std::stack<std::string> stack;

    while (!workGraph.empty())
    {
        auto node = workGraph.findDefinitelyColorableNode();
        if (node.empty())
        {
            node = workGraph.findMinCostNode();
        }
    
        workGraph.removeNode(node);
        stack.push(node);
    }

    while (!stack.empty())
    {
        auto node = stack.top();
        stack.pop();
        tryColorNode(node);
    }
}

std::string InterferenceGraph::findDefinitelyColorableNode () const
{
    for (auto & item : nodes_)
    {
        if ((int)item.second.neighbors.size() < numColors_) return item.first;
    }

    return "";
}

std::string InterferenceGraph::findMinCostNode () const
{
    auto node = nodes_.begin()->second;
    for (auto & item : nodes_)
    {
        if (item.second.cost < node.cost)
        {
            node = item.second;
        }
    }

    return node.id;
}

void InterferenceGraph::tryColorNode (std::string id)
{
    auto & node = nodes_[id];
    std::unordered_set<int> neighborsColors;
    for (auto & n : node.neighbors)
    {
        neighborsColors.insert(nodes_[n].color);
    }

    for (int color = 0; color < numColors_; color++)
    {
        if (neighborsColors.count(color) == 0)
        {
            node.color = color;
            return;
        }
    }
}