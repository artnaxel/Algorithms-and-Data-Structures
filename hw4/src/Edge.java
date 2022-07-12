
public class Edge {
    private int fromNodeIndex;
    private int toNodeIndex;
    private double price;

    public Edge(int fromNodeIndex, int toNodeIndex, double price, String owner, String myOwner){
        this.fromNodeIndex = fromNodeIndex;

        this.toNodeIndex = toNodeIndex;
        if (owner.equalsIgnoreCase(myOwner)) {
            this.price = price / 2;
        }
        else{
            this.price = price;
        }
    }

    public int getFromNodeIndex(){
        return fromNodeIndex;
    }

    public int getToNodeIndex(){
        return toNodeIndex;
    }
    public double getPrice(){
        return price;
    }

    // determines the neighbouring node of a supplied node, based on the two nodes connected by this edge
    public int getNeighbourIndex(int nodeIndex){
        if (this.fromNodeIndex == nodeIndex){
            return this.toNodeIndex;
        }else{
            return this.fromNodeIndex;
        }
    }
}
