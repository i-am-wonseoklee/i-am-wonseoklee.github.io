---
title: Matrices Applications
layout: default
nav_order: 6
parent: Linear Algebra
permalink: /docs/linalg/05-matrices-applications
---

# Matrices Applications

**Textbook:** pp.141 - 158

**Keywords:** `Correlattion coefficient matrix`{: .label }, `Covariance matrix`{: .label }

이 챕터에서는 orrelation coefficient matrix에 대한 이야기 찔끔, 회전 행렬에 대한 이야기 찔끔, 이미지 필터링에 대한 이야기 찔끔, 죄다 찔끔 질끔 이야기해준다.
그래서, 특별히 정리해둘만한 내용은 없다.
다만, 필자의 경우 기존에 covariance matrix와 correlation coefficient matrix가 서로 다른 것인지 모르고 있었기에 이 개념을 정리해두려고 한다.

## I. Correlattion coefficient matrix & Covariance matrix

[지난 챕터](/docs/linalg/02-vector-applications)에서 feature $$\mathbf{F}_1$$ 와 feature $$\mathbf{F}_2$$ 사이의 Pearson correlation coefficient를 계산하는 방법을 배웠다.
Correlattion coefficient matrix (이하 상관 행렬) 은 여러 개의 feature $$\mathbf{F}_1, \mathbf{F}_2, \mathbf{F}_N$$ 에 대해서 한 방에 $$\mathbf{F}_i$$ 와 $$\mathbf{F}_j$$ 사이의 상관관계를 한방에 보여주는 행렬이다.
쓸데 없이 설명이 길었는데, 상관 행렬 $$\mathbf{M}$$ 의 i 행 j 열 원소는 $$\mathbf{F}_i$$ 와 $$\mathbf{F}_j$$ 사이의 Pearson 상관계수를 $$K - 1$$ (단, $$K$$ 은 feature의 데이터 수) 로 나눈 값이 들어가 있다. 주절주절 말이 길었다. 식으로 요약해보도록 하겠다.

$$\mathbf{M}$$ 의 각 열에 **평균중심화** 된 feature 들이 아래와 같이 저장되어 있다고 하자.

$$
\mathbf{M}
=
\left[
  {
    \begin{array}{cccc}
    \bar{\mathbf{F}_1} & \bar{\mathbf{F}_2} & ... & \bar{\mathbf{F}_N}
    \end{array} 
  }
\right]
=
\left[
  {
    \begin{array}{cccc}
    \bar{\mathbf{F}_{11}} & \bar{\mathbf{F}_{21}} & ... & \bar{\mathbf{F}_{N1}} \\
    \bar{\mathbf{F}_{11}} & \bar{\mathbf{F}_{21}} & ... & \bar{\mathbf{F}_{N1}} \\
    ... & ... & ... & ... \\
    \bar{\mathbf{F}_{1K}} & \bar{\mathbf{F}_{2K}} & ... & \bar{\mathbf{F}_{NK}} \\
    \end{array} 
  }
\right]
$$

$$\mathbf{M}$$ 을 가지고 우선 아래와 같이 $$\mathbf{C}$$ 를 정의한다. $$\mathbf{C}$$ 는 covariance matrix (이하 공분산 행렬) 이라고 부른다.

$$
\mathbf{C} = \frac{M^T \cdot M}{K-1}
$$

상관 행렬에 관한 이야기를 이어나가기 전에 공분산 헹렬에 대해서 살펴보자.
분자에 대해 잘 생각해보면, $$\mathbf{C}_{ij}$$ 에는 $$\bar{\mathbf{F}_i}$$ 와 $$\bar{\mathbf{F}_j}$$ 사이의 내적을 $$K - 1$$ (단, $$K$$ 는 feature의 길이) 로 나눈 값이 들어있다.
그리고 이 값은 (1) $$K - 1$$ 로 나누었다는 사실과 (2) $$|\bar{\mathbf{F}_{i}}| \cdot |\bar{\mathbf{F}_{j}}|$$ 로 나누지 않았다는 사실만 제외하면 $$\mathbf{C}_{ij}$$ 는 그냥 $$F_i$$ 와 $$F_j$$ 의 Pearson 상관 계수와 같다.

공분산 행렬에서 $$|\bar{\mathbf{F}_{i}}| \cdot |\bar{\mathbf{F}_{j}}|$$ 로 나누지 않았던 것만 원래대로 나누어주면 곧 그것이 상관 행렬이다.
여전히 $$K - 1$$ 로는 나누어주는 것을 주의하자.
식으로 살펴보면 아래와 같이 상관 행렬 $$\mathbf{R}$$ 을 얻을 수 있다.
Feature의 갯수가 N개 였으므로 $$\mathbf{C}$$ 는 당연히 N x N matrix 임에 주의하자.

$$
\mathbf{R}
=
\left[
  {
    \begin{array}{cccc}
      \frac{C_{11}}{|\bar{\mathbf{F}_{1}}| \cdot |\bar{\mathbf{F}_{1}}|} & \frac{C_{12}}{|\bar{\mathbf{F}_{1}}| \cdot |\bar{\mathbf{F}_{2}}|} & ... & \frac{C_{1N}}{|\bar{\mathbf{F}_{1}}| \cdot |\bar{\mathbf{F}_{N}}|}  \\
      \frac{C_{21}}{|\bar{\mathbf{F}_{2}}| \cdot |\bar{\mathbf{F}_{1}}|} & \frac{C_{22}}{|\bar{\mathbf{F}_{2}}| \cdot |\bar{\mathbf{F}_{2}}|} & ... & \frac{C_{2N}}{|\bar{\mathbf{F}_{2}}| \cdot |\bar{\mathbf{F}_{N}}|}  \\
      ...    & ...    & ... & ...     \\
      \frac{C_{N1}}{|\bar{\mathbf{F}_{N}}| \cdot |\bar{\mathbf{F}_{1}}|} & \frac{C_{N2}}{|\bar{\mathbf{F}_{N}}| \cdot |\bar{\mathbf{F}_{2}}|} & ... & \frac{C_{NN}}{|\bar{\mathbf{F}_{N}}| \cdot |\bar{\mathbf{F}_{N}}|}  \\
    \end{array}
  }
\right]
=
\mathbf{S}\mathbf{C}\mathbf{S}
\quad
where
\quad
\mathbf{S}
=
\left[
  {
    \begin{array}{cccc}
      \frac{1}{|\bar{\mathbf{F}_{1}}|} & 0 & ... & 0 \\
      0 & \frac{1}{|\bar{\mathbf{F}_{2}}|} & ... & 0 \\
      0 & 0 & ... & 0 \\
      0 & 0 & ... & \frac{1}{|\bar{\mathbf{F}_{N}}|} \\
    \end{array}
  }
\right]
$$

## II. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/linalg/05-matrices-applications/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
