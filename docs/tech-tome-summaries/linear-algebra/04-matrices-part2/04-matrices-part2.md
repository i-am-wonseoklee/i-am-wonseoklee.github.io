---
title: Matrices (Part 2)
layout: default
nav_order: 5
parent: Linear Algebra
grand_parent: TechTome Summaries
permalink: /docs/tech-tome-summaries/linear-algebra/04-matrices-part2
---

# Matrices (Part 2)

**Textbook:** pp.107 - 140

**Keywords:** `Frobenius norm`{: .label }, `Row/Column/Null space`{: .label }, `Rank`{: .label }

대학교 교양과목 이상을 수강했다면, 특별히 눈여겨 볼 만한 내용이 소개되지는 않는 챕터였다.
다만, 이제 이 챕터부터 슬슬 하나의 개념이 갖는 여러가지 의미들이 섞이기 시작한다 (e.g. 최대계수행렬의 열은 선형독립을 이룬다던가...).
일단, 아주 간략하게 [Zettelkasten](https://ko.wikipedia.org/wiki/%EB%A9%94%EB%AA%A8_%EC%83%81%EC%9E%90) 형태로 등장한 개념들을 정리해둔다.

## I. Frobenius norm

대체 이게 뭐라고 이름까지 따로 붙어 있나 싶다. `Frobenius norm`은 행렬의 모든 원소 제곱합의 제곱근으로 아래와 같이 정의된다.

$$||A||_{F} = \sqrt{\sum_{i}\sum_{j}a_{ij}^2}$$

행렬 $$A$$의 대각합을 $$tr(A)$$ 라고 정의할 때, 아래와 같이 구할 수도 있다.

$$||A||_{F} = \sqrt{\sum_{i}\sum_{j}a_{ij}^2} = \sqrt{tr(AA^T)}$$

## II. Row/Column space

행렬 $$A$$의 row/column space는 $$R(A)$$/$$C(A)$$와 같이 표기한다.
각각이 갖는 의미는 자명하게 행/열이 span하는 공간을 의미한다.

## III. Null space

행렬 $$A$$의 null space는 $$N(A)$$로 표기한다.
$$N(A)$$는 $$Ax = 0$$의 해공간에서 영벡터를 제외한 것이다.

비록 책에는 나와 있지 않은 내용이지만, null space가 갖는 의미는 조금 더 탐구해보기 위해서 조금 더 설명을 보충했다.

### III.1. A가 역행렬을 가졌다면 어떻게 될까?

고등학교까지 배운 범위에서만 이야기하더라도 $$A$$가 역행렬을 가지면 곧장 $$N(A) = \{\}$$ (null space가 비어있음) 임을 알 수 있다.
$$Ax = 0 \Rightarrow A^{-1}Ax = A^{-1}0 \Rightarrow I{x} = 0 \Rightarrow x = 0$$ 이니 당연한 소리가 아닌가?
결국에 (너무 당연한 말을 한 것 같지만...) "$$A$$가 역행렬을 갖는다면 $$A$$의 null space는 비어있다" 라는 소정리 하나를 얻을 수 있다.

### III.2. 행렬에 벡터를 곱한다는 것은 어떤 의미를 가질까?

행렬에 벡터를 곱한다는 행위는 결국 행렬의 열들의 선형결합을 만들어 내는 행위로 볼 수 있다 (아래 예제와 같이).

$$
\left[
  {
    \begin{array}{ccc}
    c_{00} & c_{10} & c_{20} \\
    c_{01} & c_{11} & c_{21} \\
    c_{02} & c_{12} & c_{22} \\
    \end{array}
  }
\right]
\left[
  {
    \begin{array}{c}
    \lambda_{0} \\
    \lambda_{1} \\
    \lambda_{2} \\
    \end{array}
  }
\right]
=
\lambda_{0}
\left[
  {
    \begin{array}{c}
    c_{00} \\
    c_{01} \\
    c_{02} \\
    \end{array}
  }
\right]
+
\lambda_{1}
\left[
  {
    \begin{array}{c}
    c_{10} \\
    c_{11} \\
    c_{12} \\
    \end{array}
  }
\right]
+\lambda_{2}
\left[
  {
    \begin{array}{c}
    c_{20} \\
    c_{21} \\
    c_{22} \\
    \end{array}
  }
\right]
$$

이제 여기서 [Vectors (Part 2)](/docs/tech-tome-summaries/linear-algebra/01-vectors-part2) 에서 본 선형독립의 정의를 잘 떠올려보자.
$$Ax = 0$$ 에서 $$A$$의 열들이 선형독립이었다면, $$x = 0$$이어야 함을 알 수 있다.
따라서, "$$A$$의 열들이 선형독립이었다면 $$A$$의 null space는 비어있다"는 소정리를 또 얻을 수 있다.

## IV. Rank

rank는 사실 여러 가지 의미로 해석 (또는 정의) 할 수 있다.
이 곳에는 이 책에 소개된 것을 포함하여 필자가 그동안 주로 사용해오고 있는 해석들을 나열해보도록 하겠다.

행렬 $$A$$에 대해서 $$rank(A)$$는 아래와 같은 의미를 갖는다:

- [Gauss-Jordan Elimination](https://ko.wikipedia.org/wiki/%EA%B0%80%EC%9A%B0%EC%8A%A4_%EC%86%8C%EA%B1%B0%EB%B2%95)을 마친 뒤 남아있는 leading 1의 수
- $$C(A)$$ (또는 $$R(A)$$, 같은 값이지만)의 dimension
- 선형 독립 집합을 형성하는 최대 열(또는 행) 수 (바로 위에 불렛이랑 같은 말이다)

조금 문학적인 수사를 허용한다면, $$rank(A)$$는 $$A$$에 있는 의미 있는 행(또는 열)의 수를 의미한다.
여기서 "의미 있는" 행 또는 열은 선형독립인 (즉, 다른 행 또는 열의 조합으로 만들어 낼 수 없는) 행 또는 열을 의미한다.

사실 바로 직전에 언급한 "문학적인..." 설멍에서 어떤 벡터 $$v$$가 $$C(A)$$에 존재하는지를 확인하는 알고리즘이 탄생한다.
$$v$$를 $$A$$에 augment해서 다음과 같이 새로운 행렬 $$\tilde{A}$$를 만들자.

$$
\tilde{A} =
\left[
        {
                \begin{array}{cccc}
                        a_{11} & a_{12} & ... & a_{1m} \\
                        a_{21} & a_{22} & ... & a_{2m} \\
                        ... & ... & ... & ... \\
                        a_{n1} & a_{n2} & ... & a_{nm} \\
                \end{array}
        }
\right]
\cup
\left[
        {
                \begin{array}{c}
                        v_1 \\
                        v_2 \\
                        ... \\
                        v_n \\
                \end{array}
        }
\right]
= 
\left[
        {
                \begin{array}{cccc}
                        a_{11} & a_{12} & ... & a_{1m} & v_1 \\
                        a_{21} & a_{22} & ... & a_{2m} & v_2 \\
                        ... & ... & ... & ... & ... \\
                        a_{n1} & a_{n2} & ... & a_{nm} & v_n\\
                \end{array}
        }
\right]
$$

만약에 $$v \in C(A)$$ 였다고 가정해보자.
이 경우 $$\tilde{A}$$에는 선형종속인 열 하나가 의미 없이 추가된 것이고 결국 $$rank(A) = rank(\tilde{A})$$가 된다.
반대로, $$v \notin C(A)$$ 였다면 자명하게 $$rank(A) < rand(\tilde{A})$$가 되었을 것이다.

원 행렬 $$A$$와 augmented 행렬 $$\tilde{A}$$를 가지고 $$rank(A)$$, $$rank(\tilde{A})$$를 따지는 것은 대표적인 "어떤 벡터 $$v$$가 $$C(A)$$에 존재하는지를 확인하는 알고리즘" 중 하나이다.

## V. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/tech-tome-summaries/linear-algebra/04-matrices-part2/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
