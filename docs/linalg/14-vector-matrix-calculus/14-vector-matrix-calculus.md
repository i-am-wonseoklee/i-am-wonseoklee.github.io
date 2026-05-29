---
title: Vector and Matrix Calculus
layout: default
nav_order: 15
parent: Linear Algebra
permalink: /docs/linalg/14-vector-matrix-calculus
---

# Vector and Matrix Calculus

필자는 학부에서 벡터나 행렬을 대상으로 하는 calculus를 배우지 않았다.
대학원에서는 시스템을 전공했으니 말할 필요도 없고.
최근 딥러닝, 로보틱스 등의 분야가 인기를 얻으면서 벡터 및 행렬을 대상으로 하는 calculus가 문헌에 자주 등장하는 것 같다.
혁펜하임 같은 유튜버들이 “이거 학부에서 가르쳐야 한다”고 아직도 부르짖는 것을 보면, 여전히 학교에서는 잘 가르치지 않는 모양이다.
하여간 이런 이유로, 이 포스팅에서는 필자와 같은 화석들이 쉽고 빠르게 벡터 및 행렬 calculus에 입문할 수 있도록 introduction을 작성해 보고자 한다.
우리가 벡터와 행렬로 어려운 문제를 직접 풀 것은 아니지 않은가?
이 포스팅은 단지 문헌에 등장하는 벡터 및 행렬 calculus 식을 부담 없이 받아들이기 위한 가이드일 뿐이다.
몹시 정확하고 깔끔한, 그래서 솔직히 범부에게는 잘 와닿지도 않는, 정의나 정리를 원한다면 이 페이지를 끄셔라.

## Identify what you don't know

본격적으로 설명하기에 앞서, 당신이 과연 무엇을 모르는지부터 식별해 보자.
아래 표는 딥러닝 또는 로보틱스 문헌에서 자주 등장하는 함수의 형태와, 그 미분을 보통 무엇이라 부르는지를 나타낸다.
구차하게 표에 모두 적지는 않았지만, 여기서 말하는 모든 미분은 정의역 변수에 대한 미분임을 잊지 말자.
하여간 당신이 정상적인 고등학교 생활을 했다면 (a)를, 술에 절어 있지 않은 대학교 1학년 생활을 했다면 (b)를 들어보았어야 한다.
(c)와 (d)는 사람마다 조금 차이가 있겠으나, 안 배운 사람이 꽤 있으리라 생각한다.
이 포스팅에서는 (a)는 생략하고, (b)-(d)를 설명하겠다.

| 함수                                                  | 미분을 부르는 명칭 | 비고 |
|-------------------------------------------------------|--------------------|------|
| $$F: \mathbb{R} \rightarrow \mathbb{R}$$              | Derivative         | a    |
| $$F: \mathbb{R}^{n} \rightarrow \mathbb{R}$$          | Gradient           | b    |
| $$F: \mathbb{R}^{n} \rightarrow \mathbb{R}^{m}$$      | Jacobian           | c    |
| $$F: \mathbb{R}^{n \times m} \rightarrow \mathbb{R}$$ | Matrix gradient    | d    |

## Gradient

솔직히 다변수 함수 $$f(x_{1}, x_{2}) = x_{1}^{2} + x_{2}^{2}$$ 따위를 주고 gradient를 구해 보라고 하면, 대부분의 사람들은 $$2x_{1}$$, $$2x_{2}$$까지는 잘 대답한다.
문제는 당최 인간들이 이걸 정말 식으로 적을 때 행벡터로 적어야 할지, 열벡터로 적어야 할지 얼을 탄다는 점이다.
다분히 약속에 관한 문제지만, 대부분의 문헌에서 쓰는 관례를 여기서도 따라가자.
Gradient는 다변수 스칼라 함수, 즉 $$F: \mathbb{R}^{n} \rightarrow \mathbb{R}$$ 꼴의 함수를 미분한 것이다.
대부분의 문헌에서는 입력 벡터와 gradient를 모두 열벡터로 둔다.

$$
F(
\begin{bmatrix}
x_{1} \\
x_{2}
\end{bmatrix}
) = x_{1}^{2} + x_{2}^{2}

\quad,\quad

\nabla_{\mathbf{x}} F =
\begin{bmatrix}
    2x_{1} \\
    2x_{2}
\end{bmatrix}
$$

결국 벡터가 들어가서 스칼라가 나오는 함수를 미분하면, 입력 벡터와 같은 크기의 벡터가 나온다.

## Jacobian

Jacobian은 다변수 벡터 함수, 즉 $$F: \mathbb{R}^{n} \rightarrow \mathbb{R}^{m}$$ 꼴의 함수를 미분한 것이다.
입력도 벡터, 출력도 벡터인 경우다.
이때 Jacobian은 각 출력 성분의 gradient 전치를 행으로 쌓은 행렬이다.
예를 들어, 아래와 같은 단순한 선형 시스템을 생각해 보자.

$$
\begin{aligned}
    \mathbf{y} &= \mathbf{A}\mathbf{x} \\
    \begin{bmatrix}
        y_{1} \\
        y_{2} \\
    \end{bmatrix}
    & =
    \begin{bmatrix}
        1 & 2 \\
        3 & 4 \\
    \end{bmatrix}
    \begin{bmatrix}
        x_{1} \\
        x_{2} \\
    \end{bmatrix}
\end{aligned}
$$

이 경우에는

$$
\mathbf{J}_{\mathbf{y}}(\mathbf{x}) =
\frac{\partial \mathbf{y}}{\partial \mathbf{x}} =
\begin{bmatrix}
    \left(\nabla_{\mathbf{x}} y_{1}\right)^{T} \\
    \left(\nabla_{\mathbf{x}} y_{2}\right)^{T}
\end{bmatrix}
=
\begin{bmatrix}
    \frac{\partial y_{1}}{\partial x_{1}} & \frac{\partial y_{1}}{\partial x_{2}} \\
    \frac{\partial y_{2}}{\partial x_{1}} & \frac{\partial y_{2}}{\partial x_{2}}
\end{bmatrix}
=
\begin{bmatrix}
    1 & 2 \\
    3 & 4
\end{bmatrix}
= \mathbf{A}
$$

이다.
결국 기억할 것은 하나다.
벡터가 들어가서 벡터가 나오는 함수를 미분하면, 출력 차원 $$m$$과 입력 차원 $$n$$이 각각 행과 열이 되는 $$m \times n$$ 행렬이 나온다.

## Matrix gradient

Matrix gradient는 행렬을 입력으로 받고 스칼라를 출력하는 함수, 즉 $$F: \mathbb{R}^{n \times m} \rightarrow \mathbb{R}$$ 꼴의 함수를 미분한 것이다.
Gradient와 거의 똑같은데, 입력이 벡터가 아니라 행렬이라는 점만 다르다.
따라서 결과도 입력 행렬과 같은 크기의 행렬이 된다.
예를 들어, $$F(\mathbf{X}) = \|\mathbf{X}\|_{F}^{2}$$을 생각해 보자.

$$
\mathbf{X} =
\begin{bmatrix}
    x_{11} & x_{12} \\
    x_{21} & x_{22}
\end{bmatrix}
$$

라면

$$
F(\mathbf{X}) =
x_{11}^{2} + x_{12}^{2} + x_{21}^{2} + x_{22}^{2}
$$

이고, 이때의 matrix gradient는 다음과 같이 계산된다.

$$
\nabla_{\mathbf{X}} F =
\frac{\partial F}{\partial \mathbf{X}} =
\begin{bmatrix}
    \frac{\partial F}{\partial x_{11}} & \frac{\partial F}{\partial x_{12}} \\
    \frac{\partial F}{\partial x_{21}} & \frac{\partial F}{\partial x_{22}}
\end{bmatrix}
=
\begin{bmatrix}
    2x_{11} & 2x_{12} \\
    2x_{21} & 2x_{22}
\end{bmatrix}
= 2\mathbf{X}
$$

이다.
결국 기억할 것은 하나다.
행렬이 들어가서 스칼라가 나오는 함수를 미분하면, 입력 행렬과 같은 크기의 행렬이 나온다.

## Frequently used formulas

잘 생각해 보자.
당신은 아마도 고등학교 미적분학 시험을 치르기 위해 도함수표를 외웠을 것이다.
$$\frac{d}{dx}x^{n} = nx^{n-1}$$을 외운 것처럼 말이다.
아래 표는 문헌에 자주 등장하는 식들을 도함수표처럼 정리해 둔 것이다.
솔직히 “왜 그래요?”라고 물어보면 “직접 써 보세요”라는 말밖에는 해 줄 말이 없다.

| 함수 | 미분 | 비고 |
|------|------|------|
| $$f(\mathbf{x}) = \mathbf{a}^{T}\mathbf{x}$$ | $$\nabla_{\mathbf{x}} f = \mathbf{a}$$ | 선형 함수 |
| $$f(\mathbf{x}) = \mathbf{x}^{T}\mathbf{a}$$ | $$\nabla_{\mathbf{x}} f = \mathbf{a}$$ | 위와 같은 스칼라 |
| $$\mathbf{y} = \mathbf{A}\mathbf{x}$$ | $$\mathbf{J}_{\mathbf{y}} = \mathbf{A}$$ | 선형 시스템 |
| $$f(\mathbf{x}) = \mathbf{x}^{T}\mathbf{A}\mathbf{x}$$ | $$\nabla_{\mathbf{x}} f = \left(\mathbf{A} + \mathbf{A}^{T}\right)\mathbf{x}$$ | quadratic form |
| $$f(\mathbf{x}) = \lVert \mathbf{A}\mathbf{x} - \mathbf{b} \rVert_{2}^{2}$$ | $$\nabla_{\mathbf{x}} f = 2\mathbf{A}^{T}\left(\mathbf{A}\mathbf{x} - \mathbf{b}\right)$$ | least squares |
| $$F(\mathbf{A}) = \mathbf{x}^{T}\mathbf{A}\mathbf{x}$$ | $$\nabla_{\mathbf{A}} F = \mathbf{x}\mathbf{x}^{T}$$ | 행렬 $$\mathbf{A}$$에 대한 미분 |

그래도 “직접 써 보세요”라고 말만 하고 포스팅을 마무리하기에는 조금 미안한 감이 있으니, $$f(\mathbf{x}) = \lVert \mathbf{A}\mathbf{x} - \mathbf{b} \rVert_{2}^{2}$$에 대한 미분만 예시로 유도해 보겠다.
이 식은 그 자체로 least squares 등에서 자주 쓰일 뿐 아니라 유도 과정에 chain rule도 함께 등장하므로 꽤 유용하다.
우선 $$\mathbf{r} := \mathbf{A}\mathbf{x} - \mathbf{b}$$라고 두면 원래 함수는 $$f(\mathbf{x}) = \lVert \mathbf{r} \rVert_{2}^{2} = \mathbf{r}^{T}\mathbf{r}$$와 같이 쓸 수 있다.
앞에서 본 것처럼 $$\nabla_{\mathbf{r}} f = 2\mathbf{r}$$이고, $$\mathbf{r} = \mathbf{A}\mathbf{x} - \mathbf{b}$$의 Jacobian은 $$\mathbf{J}_{\mathbf{r}} = \frac{\partial \mathbf{r}}{\partial \mathbf{x}} = \mathbf{A}$$이다.
스칼라 함수에서 chain rule을 적용하면 대충 이런 모양이었다.

$$
\frac{df}{dx} =
\frac{df}{dr}
\frac{dr}{dx}
$$

벡터에서도 감각은 똑같다.
다만 $$\frac{\partial f}{\partial \mathbf{x}}$$를 그대로 쓰면 행벡터가 된다.

$$
\begin{aligned}
\frac{\partial f}{\partial \mathbf{x}}
&=
\frac{\partial f}{\partial \mathbf{r}}
\frac{\partial \mathbf{r}}{\partial \mathbf{x}} \\
&=
\left(\nabla_{\mathbf{r}} f\right)^{T}
\mathbf{J}_{\mathbf{r}} \\
&=
\left(2\mathbf{r}\right)^{T}\mathbf{A}
\end{aligned}
$$

그런데 이 포스팅에서는 대부분의 문헌을 따라 gradient를 열벡터로 두기로 했으므로, 마지막에 전치를 취해 주면 된다.

$$
\begin{aligned}
\nabla_{\mathbf{x}} f
&=
\left(
\frac{\partial f}{\partial \mathbf{x}}
\right)^{T} \\
&=
\mathbf{A}^{T}2\mathbf{r} \\
&=
2\mathbf{A}^{T}\left(\mathbf{A}\mathbf{x} - \mathbf{b}\right)
\end{aligned}
$$

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
