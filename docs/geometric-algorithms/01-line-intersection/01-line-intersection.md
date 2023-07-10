---
title: Line Intersection
layout: default
parent: Geometric Algorithms
permalink: /docs/geometric-algorithms/01-line-intersection
---

# Line Intersection

**Keywords:** `Line Intersection`{: .label }, `Line Segment Intersection`{: .label }

이 포스팅에서는 2D line(직선) 또는 2D line segment(선분)의 교차점을 구하는 방법에 대해서 정리해볼 것이다.
다룰 대상이 모두 2D이므로 각각을 그냥 line, segment라고 부르도록 하고, line-line intersection, segment-segmnet intersection에 대해서만 기술할 것이다.

초등수학 수준에도 못 미쳐보이는 내용을 왜 포스팅까지 할애해가며 적냐고 묻는다면, 직접 한 번 코드를 짜보고 온라인 저지를 통과시켜보기를 권한다.
자신있게 "해보고 말해"라고 할만큼 한번에 예외 없이 깔끔한 코드를 만들기는 어렵다.

{: .note }
> 어디까지나 재미(?)를 위한 내용이며 `boost::geometry`나 `Eigen` 등의 라이브러리 도움을 받으면 쉽게 풀 수 있는 문제이다.
> 또한, production code에서는 human error를 막기 위해 직접 개발하지 않는 것이 정답이기도하다.

## Line-line intersection

두 line이 아래와 같이 `시점 + 파라미터 * 방향벡터` 형태로 주어져 있다고 가정해보자.
- $$\mathbf{S}_{a} + {P}_{a} \mathbf{D}_{a}$$ &nbsp;
- $$\mathbf{S}_{b} + {P}_{b} \mathbf{D}_{b}$$ &nbsp;

$$\mathbf{S}_{a} + {P}_{a}  \mathbf{D}_{a} = \mathbf{S}_{b} + {P}_{b}  \mathbf{D}_{b}$$로 연립하여 이를 x, y좌표 각각에 대해 풀어쓰면 아래의 연립방정식을 얻을 수 있다.

$$
\begin{align*}
  {S}_{a}^{x} + {P}_{a}  {D}_{a}^{x} & = {S}_{b}^{x} + {P}_{b}  {D}_{b}^{x} \\
  {S}_{a}^{y} + {P}_{a}  {D}_{a}^{y} & = {S}_{b}^{y} + {P}_{b}  {D}_{b}^{y}
\end{align*}
$$

위의 연립방정식을 $${P}_{a}$$에 대해서 풀 것인데, 일단 $${P}_{b}$$가 몹시 거슬리므로 양변에 각각 양변에 $${D}_{b}^{y}$$, $${D}_{b}^{x}$$를 곱해보자.

$$
\begin{align*}
  {S}_{a}^{x}  {D}_{b}^{y} + {P}_{a}  {D}_{a}^{x}  {D}_{b}^{y} & = {S}_{b}^{x}  {D}_{b}^{y} + {P}_{b}  {D}_{b}^{x}  {D}_{b}^{y} \\
  {S}_{a}^{y}  {D}_{b}^{x} + {P}_{a}  {D}_{a}^{y}  {D}_{b}^{x} & = {S}_{b}^{y}  {D}_{b}^{x} + {P}_{b}  {D}_{b}^{y}  {D}_{b}^{x}
\end{align*}
$$

두 식을 서로 빼준 뒤 정리하면 아래와 같다.

$$
\begin{align*}
  (\mathbf{S}_{a} \times \mathbf{D}_{b}) + {P}_{a} (\mathbf{D}_{a} \times \mathbf{D}_{b}) & = (\mathbf{S}_{b} \times \mathbf{D}_{b}) \\
  {P}_{a} (\mathbf{D}_{a} \times \mathbf{D}_{b}) & = (\mathbf{S}_{b} \times \mathbf{D}_{b}) - (\mathbf{S}_{a} \times \mathbf{D}_{b})\\  
  {P}_{a} & = \frac{(\mathbf{S}_{b} - \mathbf{S}_{a}) \times \mathbf{D}_{b}}{\mathbf{D}_{a} \times \mathbf{D}_{b}}
\end{align*}
$$

구해 놓은 $${P}_{a}$$를 가지고 원 식에 대입하면 이제 쉽게 intersection의 좌표를 구할 수 있다.

{: .note }
> 한 가지 주의할 점으로 $$\mathbf{D}_{a} \times \mathbf{D}_{b} = 0$$인 경우가 있을 수 있는데, 이 경우는 그림과 같이 두 직선이 교점을 하나도 갖지 않거나, 무수히 많은 교점을 갖는 경우이다.
> 사실 수학적으로 이야기하면 아래의 두 경우는 교점을 정의할 수 없고, 따라서 구분할 필요가 없는 경우이기는 하지만 구현하는 기능에 따라 구분이 필요한 경우가 있을 수도 있다.
> 이럴 때는 각 line의 y절편을 구하고 구한 두 y절편이 일치하는 경우 무수히 많은 교점을 갖는 것으로, 아니라면 교점이 하나도 없는 경우로 처리해 줄 수 있다.

![1](/docs/geometric-algorithms/01-line-intersection/colinear-cases.png)

## Segment-segment intersection

Line-line intersection을 자연스럽게 확장하되, 몇 가지의 예외만 잘 처리해주면 된다.

{: .highlight }
> 기술의 편의를 위해서 몇 가지의 약속만 하고 넘어가도록 하자.
> - 두 점 $$\mathbf{a}$$와 $$\mathbf{b}$$에 대해서 대소 관계를 정의할 수 있고, 이 대소 관계는 x, y좌표의 사전순이라고 가정하자. 예를 들어, $$(1, 2) < (2, 0)$$이고, $$(1, 2) < (1, 3)$$이다.
> - 두 segment의 각 끝점이 $$\mathbf{a}_{first}$$, $$\mathbf{a}_{second}$$(단, $$\mathbf{a}_{first} < \mathbf{a}_{second}$$), $$\mathbf{b}_{first}$$, $$\mathbf{b}_{second}$$(단, $$\mathbf{b}_{first} < \mathbf{b}_{second}$$)와 같이 주어져 있다고 하자. 

일단, line-line intersection에서 설명한 방법을 통헤 $${P}_{a}$$를 잘 구했다고 가정해보자(즉, $${D}_{a} \times {D}_{b} \neq 0$$).
이 때는, $$\mathbf{X} = \mathbf{S}_{a} + {P}_{a} \mathbf{D}_{a}$$가 두 segment 위에 존재하는 점이 맞는지만 추가적으로 체크를해주면 된다.
$${P}_{a}$$를 구하는 과정에서 일단 $$\mathbf{X}$$가 두 line 위에 있는 점인 것은 확정이 되었으므로 아래 조건만 확인주면 큰 어려움 없이 $$\mathbf{X}$$가 두 segment 위에 있는지를 헤아릴 수 있다.
식으로 풀어 적어놓으니 쓸 데 없이 복잡해보이는 경향이 있는데, 조금만 생각해보면 단지 $$\mathbf{X}$$가 각 segment의 양 끝점이 만들어내는 bounding box 안에 위치하는지를 체크하고 있는 것 뿐이다.

$$
\begin{align*}
  \mathbf{a}_{first} < \mathbf{X} < \mathbf{a}_{second} \wedge \mathbf{b}_{first} < \mathbf{X} < \mathbf{b}_{second}
\end{align*}
$$

다음으로, $${P}_{a}$$를 구할 수 없었던 경우, 죽, $${D}_{a} \times {D}_{b} = 0$$인 경우를 살펴보자.
이는 아래 그림과 같이 다시 3가지 경우로 나눌 수 있다.

![2](/docs/geometric-algorithms/01-line-intersection/segment-cases.png)

이 중 첫번째 경우는, line-line intersection에서 언급한 바와 같이 y절편을 살핌으로서 구분해낼 수 있다.

{: .note }
> 물론 y절편을 살펴서 한 직선 위에 있지 않은 경우를 검츨하는 것도 좋은 선택지이지만, segment-segmemt인 경우에는 조금 더 간단한 방법도 사용이 가능하다.
> segment는 특성상 그 끝점이 입력으로 주어질 수 밖에 없으므로 그 끝점들을 활용하는 것이다.
> 예를 들어, y절편을 살펴 두 선분이 한 직선 위에 있는지를 체크했던 행위는 $$(\mathbf{a}_{second} - \mathbf{a}_{first}) \times (\mathbf{b}_{first} - \mathbf{a}_{second}) = 0$$이 만족하는지를 통해서도 동일하게 해낼 수 있다.
> 이 식은 $$\mathbf{a}_{first}$$, $$\mathbf{a}_{second}$$, $$\mathbf{b}_{first}$$가 한 직선 위에 있는지를 체크한다.

두번째와 세번째 경우는 간단하게 아래와 같이 대소비교를 해주는 것을 통해서 해결할 수 있다. 아래 식이 만족하는 경우 두 segment는 교점을 갖지 않는다.
역시 식을 찬찬히 뜯어보면 단지 두 segment가 만드는 bouding box가 겹치는지를 보고 있는 것 뿐임을 알 수 있다.

$$
\begin{align*}
  \mathbf{a}_{second} < \mathbf{b}_{first} \vee \mathbf{b}_{second} < \mathbf{a}_{first}
\end{align*}
$$

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>