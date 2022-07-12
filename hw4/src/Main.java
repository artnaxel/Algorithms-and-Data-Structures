/*
There is a list of roads between cities. Every road has an owner and the price. You can have a 50% discount on a road of a given owner.
Find the cheapest route from one city to another, determine the case when the route doesn't exist.
(Graph implementation based on adjacency list using Dijkstra's algorithm)
 */
public class Main {
    public static void main(String[] args) {
        int source = 5;
        int numberOfNodes = 16;
        String myOwner = "Monica";

        Edge[] edges = {new Edge(0,1, 4, "Andrew", myOwner),
                        new Edge(0, 7, 8, "Monica", myOwner),
                        new Edge(1, 7, 11, "Jim", myOwner),
                        new Edge(1, 2, 8, "Tyson", myOwner),
                        new Edge(7, 8, 7, "Andrew", myOwner),
                        new Edge(7, 6, 1, "Monica", myOwner),
                        new Edge(8, 6, 6, "Jim", myOwner),
                        new Edge(2, 8, 2, "Bob", myOwner),
                        new Edge(5, 6, 2, "Bob", myOwner),
                        new Edge(2, 5, 4, "John", myOwner),
                        new Edge(3, 5, 14, "John", myOwner),
                        new Edge(3, 4, 9, "John", myOwner),
                        new Edge(2, 3,7, "Andrew", myOwner),
                        new Edge(4, 5, 10, "Monica", myOwner),
                        new Edge(9,10,10,"Andrew", myOwner),
                        new Edge(4, 12,3,"Jim", myOwner),
                        new Edge(11,12, 7,"Monica", myOwner),
                        new Edge(12, 14, 7, "Bob", myOwner),
                        new Edge(15, 1, 30, "Tyson", myOwner),
                        new Edge(13, 2, 9, "Tyson", myOwner)};

        Graph g = new Graph(edges, numberOfNodes);
        g.setValue(0, "Klaipeda");
        g.setValue(1, "Palanga");
        g.setValue(7, "Kretinga");
        g.setValue(6,"Skuodas");
        g.setValue(8, "Mazeikiai");
        g.setValue(2, "Telsiai");
        g.setValue(5,"Siauliai");
        g.setValue(3, "Kaunas");
        g.setValue(4, "Vilnius");
        g.setValue(9, "Plunge");
        g.setValue(10, "Ginduliai");
        g.setValue(11,"Kedainiai");
        g.setValue(12, "Elektrenai");
        g.setValue(13, "Birzai");
        g.setValue(14,"Marijampole");
        g.setValue(15,"Alytus");
        g.calculateCheapestRoute(source);
        g.printResult(source);
    }
}