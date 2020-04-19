#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

struct InterferenceGraphNode
{
    std::string id;
    int color;
    std::unordered_set<std::string> neighbors;
};

typedef std::unordered_map<std::string, InterferenceGraphNode> InterferenceGraphNodes;

class InterferenceGraph
{
    InterferenceGraphNodes nodes_;
public:
    void addNode(std::string nodeId);
    void connectNodes(std::string node1, std::string node2);
    bool areConnected(std::string node1, std::string node2) const;
    void colorGraph(int k);

    const InterferenceGraphNodes & nodes () const
    {
        return nodes_;
    }
};

