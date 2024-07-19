---
title: Eigen Value Decomposition
layout: default
nav_order: 12
parent: Linear Algebra
permalink: /docs/linalg/11-eigen-value-decomposition
---

# Eigen Value Decomposition

**Textbook:** pp.252 - 281

**Keywords:** `eigen value decomposition`{: .label }

이 책은 참 후반부로 갈수록 "이 새끼 책쓰라고 누가 총들고 협박했나?" 싶은 생각이 든다.
대체 이 따위로 쓸거면 왜 썻나 하는 생각이 든다.
이 책을 팔아먹을 때 "복잡한 증명과 수식 없이 직관적으로 배우는" 이라는 말이 적혀 있는데, 어쩌면 수학이라는 분야는 엄밀한 접근 없이는 이해하기가 필연적으로 어렵지 않나 싶기도 하다.
하지만, 이미 거의 다 읽었기 때문에 (1) 매몰 비용이 커서, (2) 프로그래밍 연습 문제가 쓸만해서 참는다.
뭐 못 참아도 뭘 어쪄겠는가?
못배운 놈이 벌벌 기어야지.

하여간, 이번 챕터의 제목은 `Eigen value decomposition` (너무 기니까 후술에서는 그냥 국문으로 고윳값 분해라고 부르겠음) 이다.
참고로 고윳값 분해는 그냥 주어진 행렬의 고윳값/고유벡터를 구하는 것을 의미한다.
사실 학부 때는 "주어진 행렬의 고윳값/고유벡터를 구해라"라고 표현했지, 고윳값 분해라고 표현하지는 않았는데.
역시, 사람은 배울수록 현학적이 된다.

## I. 고윳값, 고유벡터를 직관적으로 이해하는 방법

너무 자명해서 비트 낭비인가 싶지만, 여튼 임의의 정방행렬 $$\mathbf{A}$$ 에 대해서 고유벡터 $$\mathbf{v}\ (\neq \mathbf{0})$$ 와 고윳값 $$\lambda$$ 는 아래의 식을 만족한다.

$$
\begin{align*}
\mathbf{A} \mathbf{v} & = \lambda \mathbf{v} \\
(\mathbf{A} - \lambda \mathbf{I}) \mathbf{v} & = \mathbf{0} \\
\end{align*}
$$

우선, 첫번째 식에서 고윳값/고유벡터가 갖는 기하학적 의미를 헤아려보자.
"기하학적 의미" 이니 상상하기 쉽게 $$\mathbf{v}$$ 가 2차원이었다고 해보자.
$$\mathbf{v}$$ 에 $$\mathbf{A}$$ 를 곱하는 행위는 결국 $$\mathbf{v}$$ 를 회전하거나, 찌그러뜨리거나 하는 일을 한다.
그런데, $$\mathbf{A} \mathbf{v} = \lambda \mathbf{v}$$ 라는 것은 $$\mathbf{v}$$ 에 $$\mathbf{A}$$ 변환을 가해봤자 그냥 $$\mathbf{v}$$ 를 scale 한 결과가 나온다는 뜻이다.
즉, 고유벡터는 $$\mathbf{A}$$ 에 의해서 방향이 바뀌지 않는 벡터이다.

이제 두번째 식을 살펴보고 고윳값/고유벡터의 대수적 의미를 살펴보자.
(자명하게 모두가 알고 있듯이) 정의상 고유벡터는 영벡터가 아니므로, 두번째 식을 만족하는 $$\mathbf{v}$$ 가 존재한다는 이야기는 결국 $$\mathbf{v}$$ 가 $$\mathbf{A} - \lambda \mathbf{I}$$ 의 영공간에 있다는 뜻이다.
그런데, $$\mathbf{A} - \lambda \mathbf{I}$$ 는 고윳값 만큼 $$\mathbf{A}$$ 를 [이동](/docs/linalg/03-matrices-part1)하는 것이지 않은가?
따라서, $$\mathbf{A}$$ 를 고윳값만큼 이동시킨 행렬의 영공간에 대응되는 고유벡터가 존재하는 것을 알 수 있다.

## II. 고윳값 분해를 이용한 정방행렬의 대각화

고윳값/고유벡터는 식을 가지고 열심히 장난을 치다보면 행렬을 대각화 할 수 있다.
아래와 같이 N x N 정방행렬 $$\mathbf{A}$$ 에 대해서 N 개의 고윳값, 고유벡터가 주어졌다고 해보자.

$$
\begin{align*}
\mathbf{A} \mathbf{v}_1 & = \lambda_1 \mathbf{v}_1 \\
\mathbf{A} \mathbf{v}_2 & = \lambda_2 \mathbf{v}_2 \\
... & = ... \\
\mathbf{A} \mathbf{v}_N & = \lambda_N \mathbf{v}_N \\
\end{align*}
$$

그런데, 이것은 식을 조금만 조작해보면 아래와 같이 적어줄 수도 있다.
뭐 생각보다는 별 것 아니니까, 식을 차근차근 뜯어보길 바란다.
굉장히 자명하다.

$$
\begin{align*}
\mathbf{A} \left[
    {
        \begin{array}{cccc}
            {v}_{11} & {v}_{21} & ... & {v}_{N1} \\
            {v}_{12} & {v}_{22} & ... & {v}_{N2} \\
            ... & ... & ... & ... \\
            {v}_{1N} & {v}_{2N} & ... & {v}_{NN} \\
        \end{array}
    }
\right] & = \left[
    {
        \begin{array}{cccc}
            {v}_{11} & {v}_{21} & ... & {v}_{N1} \\
            {v}_{12} & {v}_{22} & ... & {v}_{N2} \\
            ... & ... & ... & ... \\
            {v}_{1N} & {v}_{2N} & ... & {v}_{NN} \\
        \end{array}
    }
\right] \left[
    {
        \begin{array}{cccc}
            \lambda_1 & 0 & 0 & 0 \\
            0 & \lambda_2 & 0 & 0 \\
            ... & ... & ... & ... \\
            0 & 0 & 0 & \lambda_N \\
        \end{array}
    }
\right] \\
\mathbf{A} \mathbf{V} & = \mathbf{V} \mathbf{\Lambda} \\
\end{align*}
$$

마지막 결과식을 요리조리 한 번 더 조작해보면, $$\mathbf{\Lambda} = \mathbf{V}^{-1} \mathbf{A} \mathbf{V}$$ 를 얻는다. 그런데, $$\mathbf{\Lambda}$$ 는 무엇인가? 바로 대각행렬이지 않은가? 따라서, 당신은 방금 고윳값/소유벡터 식을 이리저리 조작하여 행렬을 대각화하였다.

## III. 대칭행렬에 대한 Fun Facts!

대칭행렬의 고윳값/고유벡터에는 몇가지 신기한 성질이 있다.
그 성질들을 증명하는 것도 (크게 어렵지 않고) 재미있겠지만, 이 포스팅에는 그냥 개조식으로 적어 보도록 하겠다.

{: .highlight }
> - 대칭행렬의 고유벡터는 쌍마다 모두 직교한다.
> - 조금 더 우아하게 적으면, **정규화 된** 각 고유벡터를 열로 하는 행렬을 $$\mathbf{V}$$ 라 할 때, $$\mathbf{V} \mathbf{V}^T = \mathbf{I}$$ 이다.
> - 대칭행렬의 고윳값은 항상 실수이다 (i.e. characteristic equation이 허근을 갖지 않음).

## IV. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/linalg/11-eigen-value-decomposition/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
