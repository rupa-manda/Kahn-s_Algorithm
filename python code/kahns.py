from collections import defaultdict, deque

def read_input(filename):
    with open(filename, 'r') as file:
        vertices, edges = map(int, file.readline().split())
        graph = defaultdict(list)
        in_degree = {v: 0 for v in range(vertices)}
        for _ in range(edges):
            src, dest = map(int, file.readline().split())
            graph[src].append(dest)
            in_degree[dest] += 1
    return graph, in_degree

def kahns_algorithm(filename):
    graph, in_degree = read_input(filename)
    queue = deque([v for v in in_degree if in_degree[v] == 0])
    topological_order = []

    while queue:
        vertex = queue.popleft()
        topological_order.append(vertex)
        for neighbor in graph[vertex]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    if len(topological_order) != len(graph):
        return "Graph contains cycle"
    return topological_order

if __name__ == "__main__":
    filename = "kahns.txt"
    result = kahns_algorithm(filename)
    print(result)
