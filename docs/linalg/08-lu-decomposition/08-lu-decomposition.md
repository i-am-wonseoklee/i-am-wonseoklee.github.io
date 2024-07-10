---
title: LU Decomposition
layout: default
nav_order: 9
parent: Linear Algebra
permalink: /docs/linalg/08-lu-decomposition
---

# LU Decomposition

**Textbook:** pp.193 - 210

**Keywords:** `lu decomposition`{: .label }, `reduced row echelon form`{: .label }

한 3-4개 챕터 앞부터이던가?
이 책이 왜 이렇게 설명을 X신 같이 하고 있는지 궁금해지고 있다.
이번 챕터 역시도 그 기대에 부응하듯 참 X 같이 기술된 챕터이다.
대부분의 내용은 "뭐라는 거야?" 로 치부하며 넘겼고, 그냥 대학생 때 수업 노트 찾아서 내용을 채워 넣었다.
이 책은 그래도 연습문제는 아주 나쁘지 않으니까, 희망을 가져보도록 하자.

## I. LU Decomposition

### I.1. What is it?

첫째로 `LU decomposition` 이 대체 뭔지부터 알아보자.
`LU decomposition` 은 임의의 행렬 $$\mathbf{A}$$ 를 lower triangular matrix $$\mathbf{L}$$ 과 upper triangular matrix $$\mathbf{U}$$ 의 곱으로 나타내는 것이다.
리캡하면, $$\mathbf{A}$$ 를 던져주면, $$\mathbf{A} = \mathbf{L} \mathbf{U}$$ 이 되는 $$\mathbf{L}$$, $$\mathbf{U}$$ 를 찾는 것이 곧 `LU decomposition` 이다.

### I.2. Why should I use it?

둘째로, 이걸 대체 왜 하는지 생각해보자.
행렬 하나를 상삼각, 하삼각 행렬의 곱으로 나타내면 대체 어떤 변태가 행복한 것일까?
사실 꼭 변태가 아니여도 연립방정식을 풀어줄 때 이 분해는 우리를 꽤 행복하게 만들어준다.
어떤 일련의 방정식들이 $$\mathbf{A} \mathbf{x} = \mathbf{b}$$ 와 같이 행렬 형태로 표현되었다고 가정해보자.
그런데, 아주 운이 좋게도 $$\mathbf{A}$$가 삼각 행렬의 형태를 가졌다고 가정해보자.
- 만약, $$\mathbf{A}$$ 가 상삼각 행렬이었다면, 맨 아래 행부터 back substitution 을 진행하면 연립방정식의 해를 쉽게 구해줄 수 있다.
- 만약, $$\mathbf{A}$$ 가 하삼각 행렬이었다면, 맨 아래 행부터 forward substitution 을 진행하면 연립방정식의 해를 쉽게 구해줄 수 있다.

{: .note }
> 갑자기 뜬금 없이 `back/forward substitution` 따위를 이야기해서 조금 미안한데, 멋있는 척 하려고 만든 말이다 (내가 만든 것은 아니지만).
> 그냥 맨 아래 행부터 위에 행으로 대입 (`back`) 하거나 맨 위에 행부터 아래 행으로 대입 (`forward`) 해 나가는 소거법의 일종이다.

자 이제 다시 본론으로 돌아와서, 우리가 어찌저찌 열심히 노력해서 $$\mathbf{A} = \mathbf{L} \mahtbf{U}$$ 로 LU decomposition 을 했다고 해보자.
이때, 우리는 주어진 방정식 $$mathbf{A} mathbf{x} = \mathbf{b}$$ 을 다음과 같이 변형하여 풀어줄 수 있다.
달리 말하면, 두번째 식에서 $$\mathbf{U} \mathbf{x}$$ 을 forward substitution으로 구해주고, 곧바로 이어서 back substitution으로 $$\mathbf{x}$$ 를 구해줄 수 있다는 이야기이다.

$$
\begin{align*}
\mathbf{A} \mathbf{x}               & = \mathbf{b} \\
\mathbf{L} \mathbf{U} \mathbf{x}    & = \mathbf{b} 
\end{align*}
$$

### How do I get it?

셋째로, 그래서 실제로 이것 (`LU decompostion`) 을 어떻게 구하는지 이해해보도록 하겠다.
이것을 구하는 방법은 사실 가우스 소거법 (가우스-조단이 아님에 주의하자) 에서 곧바로 유도된다.
가우스 소거법에 등장하는 기본행 연산은 아래와 같이 총 3종류이고, 각각은 모두 원본행렬에 행렬을 곱하는 형태로 표현이 가능하다.

#### 기본행 연산 1: 두 행을 서로 맞바꾸기

예를 들어, 원본 행렬에서 1행과 3행을 서로 맞바꾸는 기본행 연산을 생각해보자.
이 기본행 연산은 아래왁 같이 표현할 수 있다.

$$
\left[
{
    \begin{array}{ccc}
    0 & 0 & 1 \\
    0 & 1 & 0 \\
    1 & 0 & 0 \\
    \end{array}
}
\right]
\left[
{
    \begin{array}{ccc}
    a_{11} & a_{12} & a_{13} \\
    a_{21} & a_{22} & a_{23} \\
    a_{31} & a_{32} & a_{33} \\
    \end{array}
}
\right]
=
\left[
{
    \begin{array}{ccc}
    a_{31} & a_{32} & a_{33} \\
    a_{21} & a_{22} & a_{23} \\
    a_{11} & a_{12} & a_{13} \\
    \end{array}
}
\right]
$$

#### 기본행 연산 2: 한 행에 상수배하여 아래에 위치한 행에 더하기

예를 들어, 원본 행렬에서 1행에 3배 하여 3행에 더하는 기본행 연산을 생각해보자.
이 기본행 연산은 아래와 같은 행렬을 곱하는 것으로 표현이 가능하다.

$$
\left[
{
    \begin{array}{ccc}
    1 & 0 & 0 \\
    0 & 1 & 0 \\
    3 & 0 & 1 \\
    \end{array}
}
\right]
\left[
{
    \begin{array}{ccc}
    a_{11} & a_{12} & a_{13} \\
    a_{21} & a_{22} & a_{23} \\
    a_{31} & a_{32} & a_{33} \\
    \end{array}
}
\right]
=
\left[
{
    \begin{array}{ccc}
    a_{11}           & a_{12}           & a_{13}            \\
    a_{21}           & a_{22}           & a_{23}            \\
    3a_{11} + a_{31} & 3a_{12} + a_{32} & 3a_{13} + a_{33}  \\
    \end{array}
}
\right]
$$

#### 기본행 연산 3: 한 행에 상수배하기

예를 들어, 원본 행렬에서 1행에 3배하는 기본행 연산을 생각해보자.
이 기본행 연산은 아래와 같은 행렬을 곱하는 것으로 표현이 가능하다.

$$
\left[
{
    \begin{array}{ccc}
    3 & 0 & 0 \\
    0 & 1 & 0 \\
    0 & 0 & 1 \\
    \end{array}
}
\right]
\left[
{
    \begin{array}{ccc}
    a_{11} & a_{12} & a_{13} \\
    a_{21} & a_{22} & a_{23} \\
    a_{31} & a_{32} & a_{33} \\
    \end{array}
}
\right]
=
\left[
{
    \begin{array}{ccc}
    3a_{11} & 3a_{12} & 3a_{13} \\
    a_{21}  & a_{22}  & a_{23}  \\
    a_{31}  & a_{32}  & a_{33}  \\
    \end{array}
}
\right]
$$

본론으로 돌아가기 전에 몇 가지 성질들만 정리헤놓도록 하자.
아래에 정리하는 성질들은 모두 임의의 행렬을 `LU decomposition` 하는 과정을 이해하는데에 큰 도움을 준다.

{: .highlight }
> - 모든 기본행렬 (i.e. 기본행 연산의 행렬 표현) 들은 가역이다 (심지어 의미를 생각해보면 쉽게 구할 수도 있다!)
> - 기본 행 연산 2, 3의 기본행렬은 모두 하삼각 행렬 형태이다.
> - 하삼각 행렬의 역행렬은 하삼각 행렬이다.
> - 하삼각 행렬과 하삼각 행렬의 곱은 역시 하삼각 행렬이다.

이제 본론으로 돌아오자.
당신이 어떤 행렬 $$\mathbf{A}$$ 에 대해서 기본 행 연산 2, 3만을 사용해서 임의의 행 사다리꼴 행렬 $$\mathbf{U}$$ 에 도달했다고 하자.
식으로 표현하면 대략 아래와 같을 것이다.

$$
\mathbf{E}_1 \mathbf{E}_2 \mathbf{A} = \mathbf{U}
$$

이 식을 그대로 정리하면 아래를 얻을 수 있다.

$$
\begin{align*}
\mathbf{E}_1 \mathbf{E}_2 \mathbf{A} & = \mathbf{U} \\
\mathbf{A} & = \mathbf{E}_2^{-1} \mathbf{E}_1^{-1} \mathbf{U} \\
\end{align*}
$$

이제 여기서 위에서 언급한 정리들을 잘 생각해보자.
- $$\mathbf{E}_1$$, $$\mathbf{E}_2$$ 는 하삼각 행렬이다.
- 따라서, $$\mathbf{E}_1^{-1}$$, $$\mathbf{E}_2^{-1}$$ 도 하삼각 행렬이고, 이들의 곲도 하삼각 행렬이다.
- $$\mathbf{U}$$ 는 가우스 소거법의 결과이니 당연히 상삼각행렬이다.

따라서, $$\mathbf{L} = \mathbf{E}_2^{-1} \mathbf{E}_1^{-1}$$ 로 놓으면 위 식의 결과가 곧 LU 분해임을 알 수 있다.

## III. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/linalg/08-lu-decomposition/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
