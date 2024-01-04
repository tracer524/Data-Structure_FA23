import networkx as nx
import matplotlib.pyplot as plt

G = nx.graph

G.add_node('1')
G.add_node('2')
G.add_node('3')
G.add_node('4')
G.add_node('5')
G.add_node('6')

G.add_edge('1', '2')
G.add_edge('1', '3')
G.add_edge('1', '4')
G.add_edge('1', '5')
G.add_edge('2', '5')
G.add_edge('3', '5')

pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True)
plt.show