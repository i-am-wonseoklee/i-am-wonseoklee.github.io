---
title: SVD
layout: default
nav_order: 13
parent: Linear Algebra
permalink: /docs/linalg/12-svd
---

# SVD

**Textbook:** pp.282 - 297

**Keywords:** `singular value decomposition`{: .label }

적어도 필자 (책의 저자말고, 이 포스팅을 적고 있는 나) 가 기억하기로는 `Singular Value Decomposition` (이하 `특이값 분해` 또는 `SVD`라고 부르겠음) 는 응용되는 곳이 많아 굉장히 중요한 분해이다.
그런데, 안타깝게도 이 책의 설명은 끔찍하게 난해하다.
개인적으로 생각하기에 저자는 필요한 말 빼고는 다 적어놓았다. ㅋㅋㅋ.
그래서, 이 포스팅에서는 그냥 책의 내용과 전개는 깡그리 무시하고 내 마음대로 정리해보려 한다.

## I. What is SVD?

그냥 심플하게 SVD의 정의를 읊어보겠다.
SVD는 임의의 행렬 $$\mathbf{A}_{mxn}$$ 이 주어졌을 때, 이를 아래와 같이 세 행렬들의 곱으로 나타내는 행위를 말한다.

$$
\mathbf{A}_{m \times n} = \mathbf{U}_{m \times m} \mathbf{\Sigma}_{m \times n} \mathbf{V}_{n \times n}^{T}
$$

단, $$\mathbf{U}_{m \times m}$$, $$\mathbf{V}_{n \times n}$$ 는 [orthogonal matrix](/docs/linalg/07-qr-decomposition) 여야하고, $$\mathbf{\Sigma}_{m \times n}$$ 는 diagonal matrix 여야한다.
아마도 당신이 황당할만한 것으로는 "$$\mathbf{\Sigma}_{m \times n}$$ 는 정방행렬이 아닌데, 어떻게 대각행렬일 수 있지?" 정도가 있을 것이다.
비정방 대각행렬은 그냥 상식적으로 생각하면 되는데, 대각선 자리를 제외한 곳은 모두 0인 행렬로, 높고 넓은 행렬에 대해서는 그 자투리 (정방행렬 밖) 위치에 그냥 0이 더 들어가 있는 것이다.

자, 이것이 "literally" SVD의 정의이다.
하지만, 이 정의만 아는 것은 우리 삶에 아무런 도움을 주지 못한다.
이 분해가 의미하는 것이 무엇인지, 또 어떻게 구할 수 있는지 이어지는 섹션에서 차근차근 알아보도록 하자.

## II. What does SVD mean?

SVD의 정의로부터 우리는 아래의 관계식을 얻을 수 있다.

$$
\begin{align*}
\mathbf{A}_{m \times n} & = \mathbf{U}_{m \times m} \mathbf{\Sigma}_{m \times n} \mathbf{V}_{n \times n}^{T} \\
\mathbf{A}_{m \times n} \mathbf{V}_{n \times n} & = \mathbf{U}_{m \times m} \mathbf{\Sigma}_{m \times n} \\
\end{align*}
$$

두번째 식을 뚫어져라 째려보자.
일단 문자 그대로보면, $$\mathbf{V}$$ 의 각 열 벡터 $$\mathbf{v}_{i}$$ 에 $$\mathbf{A}$$ 로 표현되는 선형변환을 태웠더니, $$\mathbf{U}$$ 의 열 벡터 $$\mathbf{u}_{i}$$ 의 scalar 배가 나온다는 이야기이다.

그 다음 $$\mathbf{V}$$ 와 $$\mathbf{U}$$ 에 대한 가정을 한 개씩 꺼내어 복기해보자.
이들은 각 열 벡터가 pair-wise 직교하는 orthogonal 행렬들이다.
그러니, 이는 선형변환 $$\mathbf{A}$$ 를 태우기 **전**에 직교하고 있던 열 벡터들 ($$\mathbf{V}$$) 가 변환을 통과한 **후**에도 여전히 직교하고 있다는 이야기이다 ($$\mathbf{U} \mathbf{\Sigma}$$).

{: .note }
> 특이값 분해가 갖는 의미는 행렬 $$\mathbf{A}$$ 가 표현하는 선형변환에 대해서, 선형변환 전후에 동일하게 직교하고 있는 벡터들을 찾는 것 이다.
> 선형변환 전의 직교벡터들은 $$\mathbf{V}$$ 가 되고, 선형변환 후의 직교벡터들은 $$\mathbf{U} \mathbf{\Sigma}$$ 이 된다.

## III. How to get SVD?

이제 SVD가 갖는 의미를 헤아려보았으니, 진짜 구하는 방법을 알아보도록 하자.
이를 구하는 방법은 의외로(?) 쉬운데, 대칭행렬의 [EVD](/docs/linalg/11-evd) 를 응용하기 때문이다.
**대칭행렬**에만 적용되는 EVD의 성질을 활용하므로, 잘 모른다면 링크의 이전 챕터를 확인하도록 하자.

우선, 대칭행렬 $$\mathbf{A} \mathbf{A}^T$$ 의 EVD 를 생각해보자.
그럼 아래를 얻을 수 있다.

$$
\begin{align*}
\mathbf{A} \mathbf{A}^T \mathbf{V}_{EVD} & = \mathbf{V}_{EVD} \mathbf{\Lambda}_{EVD} \\
\mathbf{A} \mathbf{A}^T & = \mathbf{V}_{EVD} \mathbf{\Lambda}_{EVD} \mathbf{V}_{EVD}^{T} \\
\end{align*}
$$

이제 $$\mathbf{A} = \mathbf{U}_{SVD} \mathbf{\Sigma}_{SVD} \mathbf{V}_{SVD}^{T}$$ 라고 **가정**하고 $$\mathbf{A} \mathbf{A}^{T}$$ 를 구해보자.
그럼, 아래를 얻을 수 있다.

$$
\begin{align*}
\mathbf{A} \mathbf{A}^T & = (\mathbf{U}_{SVD} \mathbf{\Sigma}_{SVD} \mathbf{V}_{SVD}^{T})(\mathbf{U}_{SVD} \mathbf{\Sigma}_{SVD} \mathbf{V}_{SVD}^{T})^{T} \\
\mathbf{A} \mathbf{A}^T & = \mathbf{U}_{SVD} \mathbf{\Sigma}_{SVD} \mathbf{V}_{SVD}^{T} \mathbf{V}_{SVD} \mathbf{\Sigma}_{SVD}^{T} \mathbf{U}_{SVD}^{T} \\
\mathbf{A} \mathbf{A}^T & = \mathbf{U}_{SVD} \mathbf{\Sigma}_{SVD} \mathbf{\Sigma}_{SVD}^{T} \mathbf{U}_{SVD}^{T} \\
\end{align*}
$$

이제 두 식을 연립하면 아래를 얻을 수 있다.

$$
\mathbf{V}_{EVD} \mathbf{\Lambda}_{EVD} \mathbf{V}_{EVD}^{T} = \mathbf{U}_{SVD} \mathbf{\Sigma}_{SVD} \mathbf{\Sigma}_{SVD}^{T} \mathbf{U}_{SVD}^{T}
$$

결국, $$\mathbf{U}_{SVD}$$ 는 $$\mathbf{A} \mathbf{A}^{T}$$ 의 EVD 결과인 $$\mathbf{V}_{EVD}$$ 와 같고, $$\mathbf{\Sigma}_{SVD}$$ 는 $$\mathbf{\Lambda}_{EVD}$$ 의 제곱근으로 이루어진 diagonal matrix 라는 이야기이다.

{: .note }
> - 참고로, 전통적인(?) 이유로 늘 양의 제곱근을 취한다고 하니 주의하도록 하자.
> - 또한, 역시 전통적인 이유로 $$\mathbf{\Sigma}_{SVD}$$ 의 원소 $$\sigma_i$$ 들은 크기가 큰 것을 위에 행에 배치한다.

비슷한 방법으로 대칭행렬 $$\mathbf{A}^{T} \mathbf{A}$$ 에 대해서 위의 과정을 반복하면, $$\mathbf{V}_{SVD}$$ 는 $$\mathbf{A}^{T} \mathbf{A}$$ 의 EVD 결과와 같음을 알 수 있다. 자, 이제 당신은 주어진 $$\mathbf{A}$$ 에 대해서 $$\mathbf{U}_{SVD}$$, $$\mathbf{\Sigma}_{SVD}$$, $$\mathbf{V}_{SVD}^{T}$$ 를 모두 구했다. 이것이 바로 SVD를 구하는 방법이지 않겠는가!

## IV. Another view on SVD!

SVD 를 바라보는 또 다른 관점은 이 연산을 주어진 행렬 $$\mathbf{A}$$ 를 여러 층 (layer) 로 분해하는데에 사용이 될 수 있다는 점이다.
그런데, 이를 설명하기 위한 전개과정에서는 벡터의 [outer product](/docs/linalg/00-vectors-part1) 가 사용되기 때문에 이해가 처음에는 어려울 수 있다.
하지만, 행렬 몇 개 예제로 적어놓고 손으로 계산해보면 맞는 말이니 (1) 해보시거나, (2) 받아들이셔라.
필자는 당연히 후자를 선택하는 게으른 인간이다!

넓은 행렬을 예로 들어 이 관점 (높으나 넓으나 그게 그거지만) 을 설명해보도록 하겠다. 
$$\mathbf{A} = \mathbf{U}_{SVD} \mathbf{\Sigma}_{SVD} \mathbf{V}_{SVD}^{T}$$ 은 아래와 같이 다시 쓸 수 있다.

$$
\begin{align*}
\mathbf{A} & = \mathbf{U}_{SVD} \mathbf{\Sigma}_{SVD} \mathbf{V}_{SVD}^{T} \\
& = 
\left[
{
    \begin{array}{cccc}
    \vert & \vert & \vert & \vert \\
    u_{1} & u_{2} & ... & u_{m} \\
    \vert & \vert & \vert & \vert \\
    \end{array}
}
\right]
\left[
{
    \begin{array}{ccccccc}
    \sigma_1 & 0 & ... & 0 & 0 & ... & 0 \\
    0 & \sigma_2 & ... & 0 & 0 & ... & 0 \\
    0 & 0 & ... & 0 & 0 & ... & 0 \\
    0 & 0 & ... & \sigma_m & 0 & ... & 0 \\
    \end{array}
}
\right]
\left[
{
    \begin{array}{ccc}
    - & v_{1}^{T} & - \\
    - & v_{2}^{T} & - \\
    - & ... & - \\
    - & v_{n}^{T} & - \\
    \end{array}
}
\right] \\
& = \sigma_{1} u_{1} v_{1}^{T} + \sigma_{2} u_{2} v_{2}^{T} + ... + \sigma_{m} u_{m} v_{m}^{T} \\
\end{align*}
$$

맨 마지막 식에서 $$\sigma_{i} u_{i} v_{i}^{T}$$ 는 각각 외적의 scalar 배 이므로 $$m \times n$$ 행렬이다.
또한, $$\sigma_{i}$$ 는 크기가 큰 순서로 정렬되어 있으므로 앞에서 부터 전체 행렬에 미치는 영향이 크다고 할 수 있다.
따라서, 이는 행렬의 각 계층이 영향도가 큰 것부터 정렬되어 분해된 것으로 받아들이면 된다.

## V. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/linalg/12-svd/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
