---
title: Dijkstra to A-star
layout: default
parent: Robotics
permalink: /docs/robotics/05-dijkstra-to-a-star
---

# Dijkstra to A-star

**Keywords:** `A-star`{: .label }, `A*`{: .label }

A-star 알고리즘은 single-source-single-destination 최단경로 문제를 풀 수 있는 알고리즘이다.
이 알고리즘은 꽤나 기초적인 알고리즘이기 때문에 포스팅 페이지까지 할애해가며 정리하기에는 조금 아까운 주제일지도 모르겠다.
하지만, 필자는 최근 A-star 알고리즘에 대해서 한번 정리해둘 필요가 있다고 느끼게 되었다.
그 이유는 아래와 같다:

- Dijkstra 알고리즘을 구현할 때 priority queue를 사용하는 방식이 ICPC 등의 대회 또는 실무에서 자주 사용된다 (Gen-Z는 이것을 [종만북](https://product.kyobobook.co.kr/detail/S000001032946) 방법이라고 부르는 것 같음).
- Priority queue를 사용하는 Dijkstra의 구현을 알고 있다면, A-star는 Dijkstra의 구현에서 코드 1-2줄을 수정하면 될 정도로 간단한 heuristic일 뿐이다.
- 그런데, 많은 온라인 자료들에는 A-star 알고리즘을 설명하기 위헤 open-list니 close-list니 하는 군더더기 가득한 설명들뿐이다.
- 그래서, (1) prioirity queue를 사용하는 Dijkstra의 구현을 한번 더 clarify하고, (2) 자연스럽게 A-star로 확장해보기 위해서 이 포스팅을 작성한다.

## Dijkstra review

우선, Dijkstra 알고리즘에 대해서 (아주 간략히) 리뷰해보도록 하겠다.
$$G=(V, E)$$에 대해서, $$v_{start} \in V$$로부터 $$\forall v \in V \backslash \{v_{start}\}$$으로 가는 최단거리를 구하는 문제가 주어졌다고하자.
이 문제를 푸는 Dijkstra 알고리즘은 아래와 같이 기술할 수 있다.

1. 최단거리가 확정된 정점들의 집합 $$S$$를 준비한다. 자명하게 최초에는 $$S=\{v_{start}\}$$이다.
2. $$dist(v)$$가 $$v_{start}$$로부터 $$v$$에 도달하는 최단거리를 나타낸다고하자. 자명하게 최초에는 $$dist(v_{start}) = 0$$이고, $$\forall v \in V \backslash \{v_{start}\}, dist(v) = \inf$$이다.
3. $$S \neq V$$인 동안 아래 (a-d) 를 반복한다.
   1. $$V \backslash S$$에서 $$S$$에 인접한 정점들 $$\underset{\in V \backslash S}{neighbor(S)}$$ 찾는다 (i.e., $$S$$와 edge 하나로 연결되는 $$V \backslash S$$ 내 정점들).
   2. $$\underset{\in V \backslash S}{neighbor(S)}$$ 내 정점들의 최단거리를 갱신한다.
   3. $$\underset{\in V \backslash S}{neighbor(S)}$$ 내 정점들 중 가장 짧은 최단거리를 갖는 정점 $$v_{mindist}$$를 찾는다.
   4. $$dist(v_{mindist})$$는 $$v_{start}$$에서 $$v_{mindist}$$에 이르는 최단거리가 된다 (i.e., 최단거리가 확정됨). 따라서, $$S$$에 $$v_{mindist}$$를 추가한다.

그림 없이 글로만 대충 적었지만 알고리즘의 동작 방식을 이해하는 데에는 큰 문제가 없기를 바란다.
이제 위의 알고리즘에서 **3-b**와 **3-c**를 눈여겨보도록 하자.
3-b에서는 S의 이웃들에 대한 최단 경로들을 갱신해주고 있는데, 이것을 아주 멍청하게 구현하면 아래와 같은 구현이 가능할 것이다.

```python
for v in S:
    for w in adj(v):  # `adj(v)` is a list of adjacent vertices of `v`.
        if dist(v) + weight(v, w) < dist(w):  # `weight(v, w)` is an edge weight btw. `v` and `w`.
            dist(w) = dist(v) + weight(v, w)
```

{: .note }
> 사실 3-b에서 $$\underset{\in V \backslash S}{neighbor(S)}$$는 $$V \backslash S$$내에 있어야 한다는 조건이 있기 때문에, 위의 `dist(v) + weight(v, w) < dist(w)`는 `w not in S and dist(v) + weight(v, w) < dist(w)` 따위로 수정되어야 한다고 여길지 모르겠다.
> 하지만, Dijkstra 알고리즘의 증명을 살펴보면 (특히 3-d, 여기서 다루지는 않을 것임), `dist(v) + weight(v, w) < dist(w)`가 만족하였는데 `w is in S`인 것이 불가능하다.
> 따라서, 위와 같이 코드를 작성하여도 아무 문제가 없다.
> 굳이 증명을 살펴보지 않더라도 조금만 생각하면 알 수 있는데, $$S$$는 이미 최단거리가 구해진 정점들의 집합으로 다루고 있지 않은가? 그런데, $$S$$에 포함된 정점의 최단거리가 갱신되는 상황이 발생한다면 이것은 모순일 것이다.

3-c는 아주 단순하게 아래와 같이 구현할 수 있을 것이다.

```python
v_mindist = None
for v in neighbor(S):
    if v_mindist is None or dist(v) < min_dist
        v_mindist = v
        min_dist = dist(v)
```

위에 기술한 알고리즘은 정확히 동작한다.
하지만, 이 알고리즘은 조금 더 개선할 여지가 있고, 필자는 그 중 priority queue를 사용한 개선을 다음 섹션에 기술해보려고 한다.

## Dijkstra using priority queue

이전 섹션의 내용을 복기해보자.
3-b에서 $$S$$ 내의 모든 정점에 대해 이웃 정점의 최단거리를 갱신하고, 3-c에서 $$\underset{\in V \backslash S}{neighbor(S)}$$ 중 가장 짧은 최단거리를 갖는 정점을 찾아내는 과정을 개선할 방법은 없을까?

우선, 3-b에서는 굳이 $$S$$ 내의 모든 정점 $$v$$들을 순회할 필요가 없을 것이다.
직전에 $$S$$에 추가된 정점을 $$v_{prev}$$라고 한다면 $$v_{prev}$$만을 확인해주면되지 않겠는가?
조금 더 정확히 설명하면, $$v_{prev}$$의 이웃들의 최단거리가 $$v_{prev}$$를 거쳐감으로서 더 짧아질 수 있는지만을 보자는 이야기이다.

둘째로, 3-c에서 단지 가장 짧은 최단거리를 찾아내기 위해 $$\underset{\in V \backslash S}{neighbor(S)}$$를 모두 순회할 필요도 없다.
Binary tree나 heap 등 순서를 보장하는 컨테이너에 최단거리를 저장해두면 `O(lg|V|)` 따위의 복잡도로 이것을 얻어낼 수 있지 않겠는가?
이것은 생각보다 조금 까다로울 수 있는데, $$\underset{\in V \backslash S}{neighbor(S)}$$에 속하는 정점의 최단거리가 갱신되는 경우도 있기 때문이다.
조금 더 공들여 설명해보겠다.
예를 들어:
- `i`-th iteration에서 $$v \in \underset{\in V \backslash S}{neighbor(S)}$$의 최단거리 `dist(v)`가 10으로 갱신되었다고 하자.
- 그런데, `i`-th iteration에서 $$dist(v)$$보다 더 짧은 최단 거리를 갖는 $$w \in \underset{\in V \backslash S}{neighbor(S)}$$가 있어, $$v$$는 $$S$$에 추가되지 못하였다.
- `i+1`-th iteration에서 $$v \in \underset{\in V \backslash S}{neighbor(S)}$$의 최단거리 `dist(v)`가 다시 5로 갱신되었다. - **(1)**
(1)과 같이 binary tree나 heap에 담긴 item을 `갱신`해주는 것은 `삭제`->`삽입`으로 구현되므로 오버헤드가 적지 않을 것이다.
그래서, item을 직접 갱신하기보다는 이미 갱신된 아이템인지를 표시해두고, 이미 갱신된 아이템이라면 무시하는 방법이 주로 사용된다.

위에 기술한 내용이 사실 priority queue를 통한 Dijkstra 알고리즘 개선의 전부이다.
이를 pseudocode로 나타내면 아래와 같다.

```python
dist[v_start] = 0
pq.push((dist[v_start], v_start))  # Min-heap.
while not pq.empty():
    dist_so_far, here = pq.pop()
    if dist[here] < dist_so_far:  # This item has already been renewed.
        continue
    dist[here] = dist_so_far  # `dist[here]` is determined.
    for there in adj(here):
        cost_to_go = dist_so_far + weight(here, there)
        if cost_to_go < dist[there]:
            dist[there] = cost_to_go  # Mark `dist[there]` is renewed.
            pq.push((cost_to_go, there))
```

## A-star

A-star 하나 설명해보자고 참 먼길을 돌아왔다.
결론만 이야기하자면, A-star 알고리즘은 Dijkstra 알고리즘에서 priority queue의 key로 사용되던 distance 대신에 아래 $$f(v) = g(v) + h(v)$$을 사용한다는 점만이 다르다.

- $$g(v)$$: Cost so far, $$v_{start}$$에서 $$v$$에 도달하기까지의 비용
- $$h(v)$$: Cost to go, $$v$$에서 $$v_{goal}$$에 도달하기까지의 비용 (overestimate하면 안됨)

Heuristic 함수인 $$h(v)$$가 admissible하고, monotonic하면 A-star는 임의의 그래프에 대해서 optimality가 증명되어 있다.
하지만, 이런 것을 증명하는 것은 이 포스팅의 범위를 벗어나므로 여기서는 아주 간단하게 전체 구현의 의사코드만을 보이도록 하겠다.

```python
def h(v):  # Assume that 2D Euclidean distance is used as heuristic.
    return math.hypot(v.x - v_goal.x, v.y - v_goal.y)

dist[v_start] = 0
pq.push((dist[v_start] + h(v_start), v_start))  # (1).
while not pq.empty():
    dist_so_far, here = pq.pop()
    if dist[here] < dist_so_far:
        continue
    dist[here] = dist_so_far
    for there in adj(here):
        cost_to_go = dist_so_far + weight(here, there)
        if cost_to_go < dist[there]:
            dist[there] = cost_to_go
            pq.push((cost_to_go + h(there), there))  # (2).
```

Priority queue를 사용한 Dijkstra 알고리즘의 구현에서 (1), (2)와 같이 단 두줄만 바꾸어주면 된다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
