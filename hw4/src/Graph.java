import java.util.ArrayList;

public class Graph {
    private Node[] nodes;
    private int noOfNodes;
    private Edge[] edges;
    private int noOfEdges;
    private String[] cityNames;


    public Graph(Edge[] edges, int noOfNodes){
        this.edges = edges;
        this.noOfNodes = noOfNodes;
        this.cityNames = new String[noOfNodes];

        //creating Nodes
        this.nodes = new Node[this.noOfNodes];

        for (int n = 0; n < this.noOfNodes; n++){
            this.nodes[n] = new Node();
        }

        //Adding all the edges to the nodes, each edge added to two nodes (to and from)
        this.noOfEdges = edges.length;
        for (int edgeToAdd = 0; edgeToAdd < this.noOfEdges; edgeToAdd++) {
            this.nodes[edges[edgeToAdd].getFromNodeIndex()].getEdges().add(edges[edgeToAdd]);
            this.nodes[edges[edgeToAdd].getToNodeIndex()].getEdges().add(edges[edgeToAdd]);
        }
    }

    public Node[] getNodes() {
        return nodes;
    }

    public int getNoOfNodes() {
        return noOfNodes;
    }

    public Edge[] getEdges() {
        return edges;
    }

    public int getNoOfEdges() {
        return noOfEdges;
    }

    /*Set the value of node with index*/
    public void setValue (int v, String name) {
        if (this.cityNames[v] != null) {
            throw new IndexOutOfBoundsException("This index is taken");
        }
        this.cityNames[v] = name;
    }

    /*Get the value of node with index*/
    public String getValue (int v) {
        return this.cityNames[v];
    }


    /*Implementing Dijkstra’s Algorithm*/
    public void calculateCheapestRoute(int source){
        //source node
        this.nodes[source].setPriceFromSource(0);
        int currentNode = source;

        //visit every node
        for (int i = 0; i < this.nodes.length; i++){

            //loop around the edges of current node
            ArrayList<Edge> currentNodeEdges = this.nodes[currentNode].getEdges();
            for (int joinedEdge = 0; joinedEdge < currentNodeEdges.size(); joinedEdge++) {
                int neighbourIndex = currentNodeEdges.get(joinedEdge).getNeighbourIndex(currentNode);

                //only if not visited
                if (!this.nodes[neighbourIndex].isVisited()) {
                    double tentativePrice = this.nodes[currentNode].getPriceFromSource() + currentNodeEdges.get(joinedEdge).getPrice();

                    if (tentativePrice < nodes[neighbourIndex].getPriceFromSource()) {
                        nodes[neighbourIndex].setPriceFromSource(tentativePrice);
                    }
                }
            }

                //all neighbours checked so node visited
                nodes[currentNode].setVisited(true);

                //next node must be with the smallest route price
                currentNode = getNodeSmallestPrice();
            }
        }

        private int getNodeSmallestPrice() {
            int storedNodeIndex = 0;
            double storedDist = Double.MAX_VALUE;

            for (int i = 0; i < this.nodes.length; i++){
                double currentDist = this.nodes[i].getPriceFromSource();
                if(!this.nodes[i].isVisited() && currentDist < storedDist){
                    storedDist = currentDist;
                    storedNodeIndex = i;
                }
            }
            return storedNodeIndex;
        }

    /*Display result*/
    public void printResult(int source) {
        String output = "Number of nodes = " + this.noOfNodes;
        output += "\nNumber of edges = " + this.noOfEdges;
        for (int i = 0; i < this.nodes.length; i++) {
            if(nodes[i].getPriceFromSource()!= Double.MAX_VALUE) {
                output += ("\nThe cheapest way from " + getValue(source) + " to " + getValue(i) + " is: " + nodes[i].getPriceFromSource());
            }
            else {
                output += ("\nThe road from " + getValue(source) + " to " + getValue(i) + " does not exist");
            }
        }
       System.out.println(output);
    }
}
