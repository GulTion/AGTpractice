import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph_with_vertex_cover():
    graph = nx.Graph()
    vertex_cover = set()

    try:
        with open("graph_edges_vc.txt", "r") as f:
            for line in f:
                parts = line.strip().split()
                if len(parts) == 4:
                    u, v, weight, is_vertex_cover = parts
                    u, v, weight = int(u), int(v), int(weight)
                    graph.add_edge(u, v, weight=weight)
                    if is_vertex_cover == '1':
                        vertex_cover.add(u)
                        vertex_cover.add(v)  # Add both vertices to the cover
                else:
                    print("Skipping invalid line:", line.strip())
    except FileNotFoundError:
        print("Error: 'graph_edges.txt' not found. Please run the C++ implementation.")
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

    # Highlight vertex cover nodes
    nx.draw_networkx_nodes(graph, pos, nodelist=list(vertex_cover), node_color='lightgreen', node_size=1500)

    # Edge labels
    edge_labels = nx.get_edge_attributes(graph, 'weight')
    nx.draw_networkx_edge_labels(graph, pos, edge_labels=edge_labels, font_size=10)

    plt.title("Graph Visualization with Vertex Cover (Highlighted in Green)")
    plt.show()

if __name__ == "__main__":
    visualize_graph_with_vertex_cover()