#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

struct InterferenceGraphNode
{
    std::string id;
    int cost;
    int color = -1;
    std::unordered_set<std::string> neighbors;

    bool hasColor () const
    {
        return color > -1;
    }

    std::string toString () const
    {
        return std::string("Node(") + id
            + ",cost:" + std::to_string(cost)
            + ",color:" + std::to_string(color) + ")";
    }
};

typedef std::unordered_map<std::string, InterferenceGraphNode> InterferenceGraphNodes;

class InterferenceGraph
{
    InterferenceGraphNodes nodes_;
    int numColors_;
    // returns a node with degree < numColors or empty string if none exists
    std::string findDefinitelyColorableNode() const;
    void tryColorNode (std::string node);
public:

    void addNode(std::string nodeId, int cost = 1);
    void removeNode(std::string node);
    void connectNodes(std::string node1, std::string node2);
    bool areConnected(std::string node1, std::string node2) const;
    void colorGraph();

    InterferenceGraph(int numColors): numColors_(numColors) {}

    int numColors () const
    {
        return numColors_;
    }

    bool empty () const
    {
        return nodes_.empty();
    }

    const InterferenceGraphNode & node (const std::string & nodeId) const
    {
        return nodes_.at(nodeId);
    }

    const InterferenceGraphNodes & nodes () const
    {
        return nodes_;
    }
};

