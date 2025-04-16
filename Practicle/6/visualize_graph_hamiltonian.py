import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph_with_euler_tour():
    graph = nx.Graph()
    euler_tour_edges = []

    try:
        with open("graph_edges_hamiltonian.txt", "r") as f:
            for line in f:
                parts = line.strip().split()
                if len(parts) == 4:
                    u, v, weight, is_euler_tour = parts
                    u, v, weight = int(u), int(v), int(weight)
                    graph.add_edge(u, v, weight=weight)
                    if is_euler_tour == '1':
                        euler_tour_edges.append((u, v))
                else:
                    print("Skipping invalid line:", line.strip())
    except FileNotFoundError:
        print("Error: 'graph_edges_euler.txt' not found. Please run the C++ implementation.")
        return
    except ValueError:
        print("Error: Invalid format in 'graph_edges.txt'.")
        return
    except Exception as e:
        print(f"Error: An unexpected error occurred: {e}")
        return

    pos = nx.spring_layout(graph)

    # Draw all nodes and edges
    nx.draw(graph, pos, with_labels=True, node_color='skyblue', node_size=1500, font_size=10, font_weight='bold', edge_color='gray', width=1.5)

    # Highlight Euler tour edges
    nx.draw_networkx_edges(graph, pos, edgelist=euler_tour_edges, edge_color="red", width=3)

    # Edge labels
    edge_labels = nx.get_edge_attributes(graph, 'weight')
    nx.draw_networkx_edge_labels(graph, pos, edge_labels=edge_labels, font_size=10)

    plt.title("Graph Visualization with Euler Tour (Bold Red Edges)")
    plt.show()

if __name__ == "__main__":
    visualize_graph_with_euler_tour()