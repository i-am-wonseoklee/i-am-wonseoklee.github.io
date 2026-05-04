---
title: Controllability
layout: default
nav_order: 3
parent: Control Theory
permalink: /docs/control-theory/02-controllability
---

# Controllability

**Keywords:** `Controllability`{: .label }, `Pole Placement`{: .label }, `Kalman Rank Condition`{: .label }

## I. Control을 포함한 선형 시스템

이어서 선형 시스템에 대해 이야기해보자.
선형 시스템에 선형 입력을 가하는 경우 (즉, 컨트롤을 인가하는 경우) 아래와 같이 시스템을 표현할 수 있다.

$$
\dot{\mathbf{x}} = \mathbf{Ax} + \mathbf{Bu}
$$

여기서 $$\mathbf{u}$$ 가 시스템에 인가되는 컨트롤 입력이고, $$\mathbf{B}$$ 는 사용하는 액추에이터에 의해서 결정되는 입력 행렬이다.

조금 더 시스템을 풀어 써보도록 하자.
선형 시스템이기 때문에 컨트롤 입력도 결국에는 상태 벡터의 선형 결합으로 $$\mathbf{u} = -\mathbf{Kx}$$ 와 같이 표현한다.
이를 반영하면 시스템을 아래와 같이 다시 쓸 수 있다.

$$
\begin{align}
\dot{\mathbf{x}} & = \mathbf{Ax} + \mathbf{Bu} \\
& = \mathbf{Ax} - \mathbf{BKx} \\
& = (\mathbf{A} - \mathbf{BK}) \mathbf{x}
\end{align}
$$

이제 $$\mathbf{A} - \mathbf{BK}$$ 를 $$\mathbf{D}$$ 로 정의하면, $$\dot{\mathbf{x}} = \mathbf{Dx}$$ 를 얻는다.

참고로 덧붙이면 (지금 이 챕터의 내용과 크게 상관은 없지만), 이 시스템의 해는 아래와 같다.
유도 과정은 향후 다른 챕터에서 다룰 예정이므로, 여기서는 결과를 먼저 받아들이고 넘어가자.

$$
\mathbf{x}(t) = e^{\mathbf{A}t}\mathbf{x}(0)
        + \int_{0}^{t} e^{\mathbf{A}(t - \tau)}\mathbf{B}\mathbf{u}(\tau)\, d\tau
$$

## II. Controllability

어떤 시스템이 controllable하다는 것은 아래 두 가지와 동치이다.

- Arbitrary eigen value (pole) placement가 가능하다.
- Full reachability를 갖는다.

첫번째 bullet의 의미는 행렬 $$\mathbf{K}$$ 를 적절히 선정함으로써 $$\mathbf{D} = \mathbf{A} - \mathbf{BK}$$ 의 고유값을 원하는 곳 (어디든) 에 위치시킬 수 있다는 것이다.
우리는 [앞선 챕터](/docs/control-theory/01-stability/)에서 선형 시스템의 안정성은 전적으로 $$\mathbf{D}$$ 의 고유값에 달려있다는 것을 배웠다.
따라서, 고유값 (pole) 을 원하는 곳에 배치시킬 수 있다면 시스템의 안정성도 결정할 수 있다는 이야기가 된다.

두번째 bullet의 의미는 조금 생각이 필요하다.
우선 초기 상태가 $$x(0) = 0$$ 으로 고정되어 있다고 하자.
이 때, 시각 $$t$$ 에서 어떤 입력 $$u(\cdot)$$ 을 인가하느냐에 따라 $$x(t)$$ 가 달라질 것이다.
모든 가능한 입력에 대해 시각 $$t$$ 에 도달할 수 있는 상태들의 집합을 $$R_t$$ 라 정의하면 아래와 같다.

$$
R_{t} = \{\xi \in \mathbb{R}^{n} \mid \text{there is an input } u(\cdot) \text{ so that } x(t) = \xi\}
$$

직관적으로 보면, $$R_t$$ 는 "시각 $$t$$ 까지 조종할 수 있는 상태들의 범위"라고 볼 수 있다.
Full reachability란 바로 이 범위가 전체 상태 공간 $$\mathbb{R}^n$$ 을 커버하는 것, 즉 어떤 유한한 시각 $$T > 0$$ 에서

$$
R_T = \mathbb{R}^n
$$

이 성립하는 것이다.
쉽게 말해, 원하는 상태가 무엇이든 ($$\xi$$ 가 어디에 있든) 적절한 입력 $$u(\cdot)$$ 을 설계하면 $$T$$ 이내에 반드시 그 상태로 데려갈 수 있다는 뜻이다.

## III. Kalman Rank Condition

선형 시스템 $$(\mathbf{A}, \mathbf{B})$$ 가 controllable하기 위한 필요충분조건은, 아래와 같이 정의되는 **controllability matrix** $$\mathcal{C}$$ 의 rank가 $$n$$ 인 것이다.

$$
\mathcal{C} = \begin{bmatrix} \mathbf{B} & \mathbf{AB} & \mathbf{A}^2\mathbf{B} & \cdots & \mathbf{A}^{n-1}\mathbf{B} \end{bmatrix}, \quad \text{rank}(\mathcal{C}) = n
$$

이 조건이 바로 **Kalman Rank Condition**이다.
이 조건이 왜 성립하는지에 대해서는 Duhamel's principle, Caley-Hamilton 정리 등이 필요하다.
이러한 내용은 이어질 챕터에서 살펴보기로하고 여기서는 아주 간단히 직관적으로 왜 이럴지를 이해해보도록하자.

이 행렬은 임펄스 입력과 연관지어 이해해볼 수 있다.

임펄스 입력이란 아주 짧은 순간에 강한 힘을 가하는 입력으로, 직관적으로 "순간적으로 상태를 특정 방향으로 밀어주는 것"이라 생각하면 된다.

시각 $$t = 0$$ 에서 임펄스 입력을 가하면 시스템의 상태는 즉시 $$\mathbf{B}$$ 의 열(column) 방향으로 이동한다.
즉, **$$\mathbf{B}$$ 의 열벡터들이 "한 번의 입력으로 갈 수 있는 방향"** 을 나타낸다.

그렇다면 두 번의 입력은 어떨까?
아주 짧은 시간 $$\epsilon$$ 전에 임펄스를 가하고, 시스템이 잠깐 자연스럽게 진화한 뒤 다시 입력을 가하면, 추가로 도달할 수 있는 새로운 방향이 생긴다.
이 방향이 바로 $$\mathbf{AB}$$ 이다.
$$\mathbf{A}$$ 는 시스템의 자연 진화를 나타내므로, $$\mathbf{AB}$$ 는 "입력이 시스템 동역학을 통해 한 번 전파된 결과"라고 볼 수 있다.

같은 논리로 $$\mathbf{A}^2\mathbf{B},\ \mathbf{A}^3\mathbf{B},\ \ldots$$ 는 입력이 시스템을 두 번, 세 번 통과하며 전파된 방향들이다.

여기서 핵심은, Cayley-Hamilton 정리에 의해 $$\mathbf{A}^n$$ 은 $$\mathbf{I}, \mathbf{A}, \ldots, \mathbf{A}^{n-1}$$ 의 선형 결합으로 표현되므로, $$n$$ 번째 이후로는 새로운 방향이 추가되지 않는다는 점이다.
따라서 controllability matrix를 $$\mathbf{A}^{n-1}\mathbf{B}$$ 항까지만 구성하는 것으로 충분하다.

결론적으로, 시스템이 controllable하다는 것은 이 모든 방향들 — **입력 자체가 span하는 방향**, **입력이 시스템 동역학을 한 번, 두 번, ..., $$(n-1)$$ 번 통과한 방향** — 이 합쳐져 전체 상태 공간 $$\mathbb{R}^n$$ 을 채울 수 있다는 것과 동치이다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>