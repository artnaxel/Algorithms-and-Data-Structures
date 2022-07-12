import java.util.ArrayList;

public class Node {
    private double priceFromSource = Double.MAX_VALUE; //represents infinity
    private boolean visited;
    private ArrayList<Edge> edges = new ArrayList<Edge>(); //list of edges linked to node

    public double getPriceFromSource(){
        return priceFromSource;
    }

    public void setPriceFromSource(double priceFromSource){
        this.priceFromSource = priceFromSource;
    }

    public boolean isVisited(){
        return visited;
    }

    public void setVisited(boolean visited){
        this.visited = visited;
    }

    public ArrayList<Edge> getEdges(){
        return edges;
    }

    public void setEdges(ArrayList<Edge> edges){
        this.edges = edges;
    }
}
