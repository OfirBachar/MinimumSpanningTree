#include "definitions.h"
#include "Graph.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Arguments did not found.";
        exit(1);
    }

    ofstream fileToPrint(argv[2]);

    if (!fileToPrint.is_open())
    {
        cout << "Can not open file to print.";
        exit(1);
    }

    Graph G(argv[1], fileToPrint);

    if (!G.isConnectedGraph())
    {
        cout << "No MST";
        fileToPrint << "No MST";
        G.freeGraph();
        exit(1);
    }

    int kruskalMinSpanTreeWeight = G.calcWeightOfEdgeArr(G.Kruskal(false));
    cout << "Kruskal " << kruskalMinSpanTreeWeight << "\n";
    fileToPrint << "Kruskal " << kruskalMinSpanTreeWeight << "\n";

    int primMinSpanTreeWeight = G.calcWeightsInParentArr(G.Prim());
    cout << "Prim " << primMinSpanTreeWeight << "\n";
    fileToPrint << "Prim " << primMinSpanTreeWeight << "\n";

    G.removeEdgeToRemove();
    
    if(!G.isConnectedGraph())
    {
        cout << "No MST";
        fileToPrint << "No MST";
        G.freeGraph();
        exit(1);
    }

    kruskalMinSpanTreeWeight = G.calcWeightOfEdgeArr(G.Kruskal(true));
    cout << "Kruskal " << kruskalMinSpanTreeWeight << "'\n";
    fileToPrint << "Kruskal " << kruskalMinSpanTreeWeight << "'\n";

    fileToPrint.close();
}

