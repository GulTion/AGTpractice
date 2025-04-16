import networkx as nx
import matplotlib.pyplot as plt
import sys

def kruskal_mst(edges, V):
    # Sort edges by weight
    edges = sorted(edges, key=lambda x: x[2])

    parent = list(range(V))  # Union-find parent array
    rank = [0] * V  # Union-find rank array
    mst = []  # List to store edges of MST
    total_cost = 0  # Total cost of MST

    def find(x):
        if parent[x] != x:
            parent[x] = find(parent[x])  # Path compression
        return parent[x]

    def union(x, y):
        root_x = find(x)
        root_y = find(y)
        if root_x != root_y:
            # Union by rank
            if rank[root_x] > rank[root_y]:
                parent[root_y] = root_x
            elif rank[root_x] < rank[root_y]:
                parent[root_x] = root_y
            else:
                parent[root_y] = root_x
                rank[root_x] += 1

    # Process each edge
    for u, v, weight in edges:
        root_u = find(u)
        root_v = find(v)

        if root_u != root_v:
            mst.append((u, v, weight))
            total_cost += weight
            union(u, v)

        if len(mst) == V - 1:
            break

    return mst, total_cost

def visualize_graph(edges, mst, V):
    # Create a graph object
    G = nx.Graph()

    # Add edges to the graph
    for u, v, weight in edges:
        G.add_edge(u, v, weight=weight)

    # Create a new graph for MST edges
    mst_edges = [(u, v) for u, v, weight in mst]

    # Plot the original graph
    plt.figure(figsize=(8, 6))
    pos = nx.spring_layout(G, seed=42)  # Layout for node positioning

    # Plot all edges in gray
    nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=1500, font_size=10, font_weight='bold', edge_color='gray', width=1.5)

    # Highlight the MST edges in red
    nx.draw_networkx_edges(G, pos, edgelist=mst_edges, edge_color='red', width=2)

    # Edge labels with weights
    edge_labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=10)

    plt.title('Graph Visualization with MST (bold red edges)', fontsize=14)
    plt.show()

def main():
    # Example number of vertices and edges
    V = 9
    E = 14

    # Edges (src, dest, weight)
    edges = []

     # Read graph data from the file
    try:
        with open("graph_edges.txt", "r") as f:
            for line in f:
                u, v, weight, is_mst = map(str, line.strip().split())
                edges.append((int(u), int(v), int(weight)))
                
    except FileNotFoundError:
        print("Error: 'graph_edges.txt' not found, please run the c++ implementation")
       
    except ValueError:
       print("Error: invalid graph_edges.txt, check the file")
       
    except Exception as e:
       print(f"Error: An unexpected error occurred {e}")
    # Compute MST
    mst, total_cost = kruskal_mst(edges, V)

    # Display the MST
    print('Edges in MST:')
    for u, v, weight in mst:
        print(f'{u} - {v} : {weight}')
    print(f'Total cost of MST: {total_cost}')

    # Visualize the graph and MST
    visualize_graph(edges, mst, V)

if __name__ == "__main__":
    main()