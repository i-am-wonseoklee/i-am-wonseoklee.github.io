---
title: Controllability Test
layout: default
nav_order: 4
parent: Control Theory
permalink: /docs/control-theory/03-controllability-test
---

# Controllability Test

**Keywords:** `Controllability Test`{: .label }, `PBH Test`{: .label }

[앞선 챕터](/docs/control-theory/02-controllability/)에서 선형 시스템의 controllability를 살펴보았고, Kalman rank condition을 통해 시스템이 controllable한지 아닌지를 판별하는 방법을 소개했다.

이번 챕터에서는 시스템이 controllable한지 아닌지를 확인하는 몇 가지 방법을 추가로 소개하려고 한다.
여기서 소개하는 방법들이 Kalman rank condition보다 더 우월해서 소개하는 것은 아니다.
다만, 이 방법들을 이해하는 과정에서 얻을 수 있는 교훈이 꽤 많기 때문에 함께 다루고자 한다.

## I. Controllability Gramian Test

Controllability **Gramian**은 다음과 같이 정의되는 $$n \times n$$ 행렬이다.
솔직히 말해 끔찍하게 생겼음을 부정하지는 않겠다.

$$
\mathbf{W}(t) = \int_{0}^{t} e^{\mathbf{A}\tau}\, \mathbf{B}\mathbf{B}^T\, e^{\mathbf{A}^T\tau}\, d\tau
$$

결론만 추려서 이야기하면, $$\mathbf{W}(t)$$ 의 rank가 $$n$$ 이면 시스템은 controllable이고, rank-deficient이면 controllable하지 않다.

이뿐만 아니라 controllability Gramian은 추가적인 정보도 제공한다.
$$\mathbf{W}(t)$$ 가 다음과 같이 고유값 분해(EVD)되었다고 하자.

$$
\mathbf{W}(t) \mathbf{V} = \mathbf{V} \mathbf{\Lambda}
$$

이때 고유값이 큰 방향에 대응하는 고유벡터일수록 해당 방향은 더 쉽게 제어된다고 해석할 수 있다.
즉, 같은 양의 input energy를 투입했을 때 해당 방향으로 더 큰 제어 효과를 얻을 수 있다는 이야기이다.

또 한 가지 흥미로운 사실은, 언뜻 복잡해 보이는 Gramian $$\mathbf{W}(t)$$ 와 controllability matrix $$\mathbf{C}$$ 사이에 다음 관계가 성립한다는 점이다.

$$
\mathbf{W}(t) \approx \mathbf{C}\mathbf{C}^T
$$

그렇다면 controllability Gramian 기반 test는 결국 $$\mathbf{C}\mathbf{C}^T$$ 의 EVD를 통해 eigenvalue의 크기 순서대로 제어 방향을 살펴보는 것과 같다.

여기서 한 가지를 더 떠올릴 수 있다.
$$\mathbf{C}\mathbf{C}^T$$ 의 EVD는 본질적으로 $$\mathbf{C}$$ 의 [SVD](/docs/linalg/12-svd/)와 연결된다.
따라서 $$\mathbf{C} = \mathbf{U}\mathbf{\Sigma}\mathbf{V}^T$$ 라고 하면, $$\mathbf{U}$$ 의 각 열은 제어가 쉬운 방향부터 순서대로 정렬된 기저로 해석될 수 있다.

## II. PBH Test

PBH는 Popov-Belevitch-Hautus Test의 약자이다.
이 테스트의 핵심 정리는 다음과 같다.

$$
(\mathbf{A}, \mathbf{B}) \text{ is controllable if and only if }
\text{rank}[\mathbf{A}-\lambda\mathbf{I}\;\;\mathbf{B}] = n,
\quad \forall \lambda \in \mathbb{C}
$$

처음 보면 $$\forall \lambda \in \mathbb{C}$$ 가 부담스럽다.
하지만 실제로는 $$\mathbf{A}$$ 의 eigenvalue에 대해서만 확인하면 된다.
eigenvalue가 아닌 $$\lambda$$ 에서는 $$\mathbf{A}-\lambda\mathbf{I}$$ 가 이미 가역이므로, $$\mathbf{B}$$ 와 붙인 행렬의 rank는 자동으로 $$n$$ 이 보장되기 때문이다.

따라서 핵심 질문은 "각 eigenvalue에서 rank가 유지되는가"이다.
어떤 eigenvalue $$\lambda$$ 에서라도 $$[\mathbf{A}-\lambda\mathbf{I}\;\;\mathbf{B}]$$ 의 rank가 떨어지면 controllable하지 않다.

직관적으로는 이렇게 이해할 수 있다.
$$\mathbf{A}$$ 의 eigenvalue $$\lambda$$ 에 대응하는 eigenvector를 $$\mathbf{v}$$ 라 하면 $$\mathbf{A}\mathbf{v} = \lambda\mathbf{v}$$ 이므로 $$(\mathbf{A}-\lambda\mathbf{I})\mathbf{v} = \mathbf{0}$$ 이다.
다시 말해, $$\mathbf{A}-\lambda\mathbf{I}$$ 라는 행렬에 $$\mathbf{v}$$ 를 곱하면 결과가 영벡터가 된다.
$$\mathbf{v}$$ 방향의 정보가 완전히 사라지는 셈이다.

$$[\mathbf{A}-\lambda\mathbf{I}\;\;\mathbf{B}]$$ 는 두 행렬을 좌우로 붙인 $$n \times (n+m)$$ 행렬이다.
이 행렬의 rank는 두 행렬의 열 공간(column space)을 합쳤을 때 몇 차원을 커버하는지를 나타낸다.

$$\mathbf{A}-\lambda\mathbf{I}$$ 의 column space는 $$\mathbf{v}$$ 방향을 포함하지 못한다.
$$\mathbf{v}$$ 를 곱하면 영벡터가 나오므로, 어떤 열의 조합으로도 $$\mathbf{v}$$ 방향을 표현할 수 없기 때문이다.
따라서 전체 행렬 $$[\mathbf{A}-\lambda\mathbf{I}\;\;\mathbf{B}]$$ 의 rank가 $$n$$ 이 되려면,
$$\mathbf{B}$$ 의 열들이 그 빠진 $$\mathbf{v}$$ 방향을 반드시 채워줘야 한다.
만약 $$\mathbf{B}$$ 조차 $$\mathbf{v}$$ 방향 성분을 갖지 않는다면, 두 행렬을 합쳐도 $$\mathbf{v}$$ 방향은 커버되지 않고 rank는 $$n$$ 보다 작아진다.

정리하면 PBH Test는 한 문장이다.
"$$\mathbf{A}$$ 의 모든 eigenvalue에서, $$\mathbf{B}$$ 가 대응하는 eigenvector 방향을 빠짐없이 포함하는가?"

## III. Kalman Rank Condition의 보충 설명

[앞선 챕터](/docs/control-theory/02-controllability/)에서 소개한 Kalman rank condition을 조금 더 보충해서 설명하고자 한다.
설명에 앞서 Cayley-Hamilton 정리가 전달하는 두 가지 유용한 사실을 기억하자.

1. 행렬의 characteristic equation(특성방정식)에 행렬 자체를 대입해도 성립한다.
2. 결과적으로, 행렬의 $$n$$ 승 이상의 거듭제곱은 최대 $$n-1$$ 승까지의 거듭제곱의 선형 결합으로 표현할 수 있다.

위의 두 사실을 종합하면, matrix exponential $$e^{\mathbf{A}t}$$ 는 아래와 같이 finite sum으로 표현할 수 있다.

$$
\begin{aligned}
e^{\mathbf{A}t}
        & = \mathbf{I} + \mathbf{A}t + \mathbf{A}^2\frac{t^2}{2!} + \cdots                              \\
        & = \phi_{0}(t) \mathbf{I} + \phi_{1}(t) \mathbf{A} + \cdots + \phi_{n-1}(t) \mathbf{A}^{n-1}   \\
\end{aligned}
$$

갑자기 뜬금없이 Kalman rank condition을 이야기하다가 Cayley-Hamilton 정리로 방향을 튼 점이 어색하게 느껴질 수 있다.
하지만 이후 내용을 전개하기 위해 이 내용이 필요하다.

본론으로 돌아와서, 왜 controllability matrix가 rank $$n$$ 을 가지면 controllable한지 다시 생각해보자.
앞선 챕터에서 full reachability와 controllability가 동치이며, 입력이 포함된 선형 시스템의 해가 아래와 같이 표현된다는 사실을 확인했다.

$$
\mathbf{x}(t) = e^{\mathbf{A}t}\mathbf{x}(0)
        + \int_{0}^{t} e^{\mathbf{A}(t - \tau)}\mathbf{B}\mathbf{u}(\tau)\, d\tau
$$

편의상 $$\mathbf{x}(0) = \mathbf{0}$$ 라고 하자.
그러면 결국 $$\mathbf{x}(t) = \int_{0}^{t} e^{\mathbf{A}(t - \tau)}\mathbf{B}\mathbf{u}(\tau)\, d\tau$$ 가 될 것이다.
적절한 $$\mathbf{u}(t)$$ 를 구성해 $$\mathbf{x}(t)$$ 가 $$\mathbb{R}^n$$ 의 임의의 상태에 도달할 수 있음을 보이면, full reachability를 증명한 것이고 곧 controllability를 증명한 것이다.

Cayley-Hamilton 정리를 사용하여 위의 식을 조금 더 정리해보자.

$$
\begin{aligned}
\mathbf{x}(t)
&= \int_{0}^{t} e^{\mathbf{A}(t - \tau)}\mathbf{B}\mathbf{u}(\tau)\, d\tau \\
&= \int_{0}^{t} [\phi_{0}(t-\tau)\mathbf{I} + \phi_{1}(t-\tau) \mathbf{A} + \cdots + \phi_{n-1}(t-\tau) \mathbf{A}^{n-1}]\mathbf{B}\mathbf{u}(\tau)\, d\tau \\
&= \sum_{k=0}^{n-1} \mathbf{A}^{k}\mathbf{B} \int_{0}^{t} \phi_k(t-\tau)\mathbf{u}(\tau)\, d\tau
\end{aligned}
$$

이제

$$
\boldsymbol{\eta}_k(t) := \int_{0}^{t} \phi_k(t-\tau)\mathbf{u}(\tau)\, d\tau \in \mathbb{R}^{m}
$$

라고 두면,

$$
\mathbf{x}(t)
= [\mathbf{B}\;\;\mathbf{A}\mathbf{B}\;\;\cdots\;\;\mathbf{A}^{n-1}\mathbf{B}]
\begin{bmatrix}
\boldsymbol{\eta}_0(t) \\
\boldsymbol{\eta}_1(t) \\
\vdots \\
\boldsymbol{\eta}_{n-1}(t)
\end{bmatrix}
= \mathbf{C}\,\boldsymbol{\eta}(t)
$$

를 얻는다. 즉, 도달 가능한 모든 상태는 항상 $$\mathbf{C}$$ 의 column space 안에 있다.

따라서

- $$\mathrm{rank}(\mathbf{C}) < n$$ 이면, 도달 가능한 상태공간은 $$\mathbb{R}^n$$ 의 진부분공간에 갇히므로 full reachability가 불가능하다.
- 반대로 $$\mathrm{rank}(\mathbf{C}) = n$$ 이면, $$\mathbf{C}$$ 의 column들이 $$\mathbb{R}^n$$ 전체를 생성하므로 적절한 입력 $$\mathbf{u}(t)$$ 를 통해 임의의 목표 상태를 만들 수 있다.

결론적으로,

$$
(\mathbf{A},\mathbf{B})\ \text{is controllable}
\iff
\mathrm{rank}[\mathbf{B}\;\;\mathbf{A}\mathbf{B}\;\;\cdots\;\;\mathbf{A}^{n-1}\mathbf{B}] = n.
$$

이것이 Kalman rank condition의 핵심 논리다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>