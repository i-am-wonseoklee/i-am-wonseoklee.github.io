---
title: Vectors (Part 1)
layout: default
nav_order: 1
parent: Linear Algebra
grand_parent: TechTome Summaries
permalink: /docs/tech-tome-summaries/linear-algebra/00-vectors-part1
---

# Vectors (Part 1)

**Textbook:** pp.25 - 52

**Keywords:** `Cross Product`{: .label }, `Outer Product`{: .label }, `Orthogonal Vector Decomposition`{: .label }

Chapter 1은 여느 선형대수학 책이 그러하듯 별 다른 내용은 없고, vector에 대한 기본적인 정의들을 소개하고 있다.
이런 기본적인 정의(혹은 성질)들을 블로그에 다시 적는 것은 정말 비트 낭비일 것 같으니, 이 포스트에서는 그래도 적어볼 가치가 있다고 판단한 것들을 정리해본다.

## I. Outer Product vs. Cross Product

조금 부끄럽지만, 필자는 비교적 최근까지도 `outer product`와 `cross product`를 둘 다 `외적`이라는 한국말로 번역하고 두개가 서로 같은 것 인줄 알고 있었다.
(굳이 변명해보자면) 아마도 고등학교 교과과정에서 `cross product`를 가르칠 때 내적 (`inner product`) 과 대비를 시켜주기 위해 `외적`이라는 단어를 사용했기 때문이리라.

long story short, 아래를 기억하도록 하자.

{: .highlight }
> - 한국에서 `외적`이라고 부르는 것은 문맥에 따라 `outer product` 또는 `cross product`가 될 수 있다.
> - 굳이 한국말을 사용해야 하는 상황인데, 혼란을 주고 싶지 않다면:
>   - `outer product`는 `텐서곱`으로
>   - `cross product`는 `가위곱`으로 부르도록하자.

### I.1. Outer Product

`Outer product` (`텐서곱`) 은 column vector 하나와 row vector 하나를 취하는 이항연산자로 (심지어 두 column, row vector의 차원이 달라도 됨) $$\mathbf{v}\mathbf{w}^T$$ 와 같이 표현한다.
그리고, 이 연산자의 출력은 `matrix` (`행렬`) 이 된다.

{: .note }
> 미리 밝혀두자면, 대부분의 선형대수학 교과서는 임의의 벡터 $$\mathbf{v}$$ 가 있을 때, 이는 column vector임을 가정한다.
> 당연히 필자도 이러한 convention을 따라서 내용을 기술할 것이고, 위에서 언급한 $$\mathbf{v}\mathbf{w}^T$$ 는 곧 column vector, row vector의 순서가 된다.

막 고등학교를 마친 상태에서는 `텐서곱`이 꽤나 생소할 수 있는데, 의외로 여러 분야에서 꽤 많이 쓰이는 연산이니 기억해두도록 하자.
아마 이어질 챕터에서 분명 쓸 일이 있을 것이다.

아래에 적당한 `텐서곱`의 예제를 하나 보인다 (numpy의 broadcasting 연산과 굉장히 유사한 것을 알 수 있다).

$$
\begin{align*}
\mathbf{v}              & = [a, b, c]^T  \\
\mathbf{w}              & = [d, e]^T     \\
\mathbf{v} \mathbf{w}^T & = 
\left[
  {
    \begin{array}{c}
    a \\
    b \\
    c \\
    \end{array}
  }
\right]
\left[
  {
    \begin{array}{cc}
    d & e \\
    \end{array}
  }
\right]
=
\left[
  {
    \begin{array}{cc}
    ad & ae \\
    bd & be \\
    cd & ce \\
    \end{array}
  }
\right]
\end{align*}
$$

### I.2. Cross Product

`Cross Product` (`가위곱`) 은 아마도 당신이 익숙할, 고등학교 때 배운 그 `외적`이다 (비록 이 네이밍이 큰 혼란을 야기하기는 하지만...). 보통 $$\times$$ 기호로 표현을 하고, 2개의 피연산자 벡터가 이루는 평면에 normal한 벡터를 출력한다. 물론, 이 때 두벡터의 차원은 서로 같아야 한다.

아래에 적당한 `가위곱`의 예제를 하나 보인다.

$$
\begin{align*}
\mathbf{v}                    & = [v_1, v_2, v_3]^T \\
\mathbf{w}                    & = [w_1, w_2, w_3]^T \\
\mathbf{v} \times \mathbf{w}  & = det(
\left[
  {
    \begin{array}{ccc}
    \hat{i} & \hat{j} & \hat{k} \\
    v_1     & v_2     & v_3     \\
    w_1     & w_2     & w_3     \\
    \end{array}
  }
\right]
)
=
det(
\left[
  {
    \begin{array}{cc}
    v_2 & v_3 \\
    w_2 & w_3 \\
    \end{array}
  }
\right]
) \hat{i}
+
det(
\left[
  {
    \begin{array}{cc}
    v_1 & v_3 \\
    w_1 & w_3 \\
    \end{array}
  }
\right]
) \hat{j}
+
det(
\left[
  {
    \begin{array}{cc}
    v_1 & v_2 \\
    w_1 & w_2 \\
    \end{array}
  }
\right]
) \hat{k}
\end{align*}
$$

## II. Orthogonal Vector Decomposition

`Orthogonal vector decomposition` (`벡터직교분해`, 영어로 쓰면 이따위로 길 줄 몰랐다...) 은 임의의 벡터 $$\mathbf{v}$$ 와 레퍼런스 벡터 $$\mathbf{r}$$ 이 주어졌을 때, $$\mathbf{v}$$를 (1) $$\mathbf{r}$$ 과 평행한 벡터 하나, (2) $$\mathbf{r}$$ 과 수직인 벡터 하나의 합으로 표현하는 방법을 찾는 과정이다. 글로 설명하니 뭔 개소리인가 싶을텐데, 아래의 그림을 보면 명확하게 이해할 수 있다.

![](/docs/tech-tome-summaries/linear-algebra/00-vectors-part1/ortho_decomp.png)

위의 그림에서는 임의의 벡터 $$\mathbf{v}$$ 와 주어진 레퍼런스 벡터 $$\mathbf{r}$$ 에 대해서 $$\mathbf{v} = \mathbf{v}_{\perp \mathbf{r}} + \mathbf{v}_{\parallel \mathbf{r}}$$ 이 만족하는 것을 알 수 있다. 결국 바꾸어 말하면, 임의의 벡터 $$\mathbf{v}$$ 와 레퍼런스 벡터 $$\mathbf{r}$$ 이 주어졌을 때, $$\mathbf{v} = \mathbf{v}_{\perp \mathbf{r}} + \mathbf{v}_{\parallel \mathbf{r}}$$ 이 만족하도록 $$\mathbf{v}_{\perp \mathbf{r}}$$ 과 $$\mathbf{v}_{\parallel \mathbf{r}}$$ 을 찾는 것이 곧 `직교분해`이다.

`직교분해`를 하는 것은 몹시 간단한데, 위의 그림을 보면 $$\mathbf{v}_{\parallel \mathbf{r}} = \alpha \mathbf{r} (\alpha \in \mathbb{R})$$ 임을 알 수 있다.
따라서, $$\mathbf{v} - \alpha \mathbf{r}$$ 과 $$\mathbf{r}$$ 은 서로 수직이며 $$(\mathbf{v} - \alpha \mathbf{r}) \cdot \mathbf{r} = 0$$ 이 될 것이다.
이를 식으로 만들어 술술술 풀어보면 다음과 같이 $$\alpha$$를 구할 수 있다.

$$
\begin{align*}
(\mathbf{v} - \alpha \mathbf{r}) \cdot \mathbf{r} & = 0 \\
(\mathbf{v} - \alpha \mathbf{r})^T \mathbf{r}     & = 0 \\
\alpha                                            & = \frac{\mathbf{v}^T \mathbf{r}}{\mathbf{r}^T \mathbf{r}} \\                        
\end{align*}
$$

따라서, 자명하게 $$\mathbf{v}_{\parallel \mathbf{r}} = \frac{\mathbf{v}^T \mathbf{r}}{\mathbf{r}^T \mathbf{r}} \mathbf{r}$$ 이며, $$\mathbf{v} = \mathbf{v}_{\perp \mathbf{r}} + \mathbf{v}_{\parallel \mathbf{r}}$$ 였으므로, $$\mathbf{v}_{\perp \mathbf{r}} = \mathbf{v} - \frac{\mathbf{v}^T \mathbf{r}}{\mathbf{r}^T \mathbf{r}} \mathbf{r}$$ 이다. 주절주절 말이 길었는데, 정리하면 아래와 같다.

{: .highlight }
> - $$\mathbf{v}_{\parallel \mathbf{r}} = \frac{\mathbf{v}^T \mathbf{r}}{\mathbf{r}^T \mathbf{r}} \mathbf{r}$$ 이다.
> - $$\mathbf{v}_{\perp \mathbf{r}} = \mathbf{v} - \frac{\mathbf{v}^T \mathbf{r}}{\mathbf{r}^T \mathbf{r}} \mathbf{r}$$ 이다.

## III. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/tech-tome-summaries/linear-algebra/00-vectors-part1/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>