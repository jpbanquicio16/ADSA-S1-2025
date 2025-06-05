import sys

class PrimMST:
    def __init__(self):
        self.remove_total = 0

    def min_key(self, key, mst_set):
        min_val = float('inf')
        min_index = -1

        for v in range(len(key)):
            if not mst_set[v] and key[v] < min_val:
                min_val = key[v]
                min_index = v

        return min_index

    def prims(self, graph):
        parent = [-1] * len(graph)
        key = [float('inf')] * len(graph)
        mst_set = [False] * len(graph)

        key[0] = 0

        for _ in range(len(graph) - 1):
            u = self.min_key(key, mst_set)
            mst_set[u] = True

            for v in range(len(graph)):
                if graph[u][v] > 0 and not mst_set[v] and graph[u][v] < key[v]:
                    parent[v] = u
                    key[v] = graph[u][v]
                elif graph[u][v] < 0:
                    self.remove_total += graph[u][v]

        total = sum(key[1:])
        return total

def l2n(c):
    return ord(c) - ord('A') if c.isupper() else ord(c) - ord('a') + 26

def driver():
    # Sample test input:
    i1 = "110,011,001"       # binary road existence
    i2 = "abcabcabc"         # build cost
    i3 = "xyzxyzxyz"         # remove cost

    p = PrimMST()
    v1 = [[]]
    count = 0
    remove_total = 0

    for i in range(len(i1)):
        if i1[i] == ',':
            v1.append([])
            count += 1
            continue

        if i1[i] == '0':
            v1[count].append(l2n(i2[i]))
        else:
            val = -l2n(i3[i])
            v1[count].append(val)
            remove_total += -val

    if remove_total % 2 != 0:
        remove_total += 1
    remove_total //= 2

    result = p.prims(v1) + remove_total
    print("Total cost:", result)

def driver():
    # Sample test input (3x3 matrix):
    i1 = "110,011,001"       # Road existence
    i2 = "abcabcabc"         # Build cost (no road)
    i3 = "xyzxyzxyz"         # Remove cost (existing road)

    p = PrimMST()
    v1 = [[]]
    count = 0
    remove_total = 0

    # Separate index for i2 and i3 since i1 contains commas
    cost_index = 0

    for i in range(len(i1)):
        if i1[i] == ',':
            v1.append([])
            count += 1
            continue

        if i1[i] == '0':
            v1[count].append(l2n(i2[cost_index]))
        else:
            val = -l2n(i3[cost_index])
            v1[count].append(val)
            remove_total += -val

        cost_index += 1  # Only advance when we process a character

    if remove_total % 2 != 0:
        remove_total += 1
    remove_total //= 2

    result = p.prims(v1) + remove_total
    print("Total cost:", result)


# Run the test driver
if __name__ == "__main__":
    driver()
