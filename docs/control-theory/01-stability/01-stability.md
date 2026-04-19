---
title: Stability
layout: default
nav_order: 2
parent: Control Theory
permalink: /docs/control-theory/01-stability
---

# Stability

**Keywords:** `Stability`{: .label }, `Eigen Values`{: .label }

## I. 선형 시스템의 안정성

안정성(stability)은 한마디로, "초기 오차가 시간이 지나서 줄어드는지"를 보는 개념이다.

예를 들어 진자를 수직 아래 평형점에서 아주 조금만 밀어보거나, 드론 자세각에 몇 도 안 되는 작은 오차를 일부러 넣었다고 해보자.
이런 작은 오차를 줬을 때 시간이 지나며 다시 평형점으로 돌아오면 안정하다고 보면 된다.

즉, $$\dot{\mathbf{X}} = \mathbf{A}\mathbf{X}$$ 와 같이 주어진 시스템이 $$t \to \infty \; \Rightarrow \; \mathbf{X}(t) \to \mathbf{0}$$ 를 만족하는 경우 안정, 아닌 경우 불안정하다고 할 수 있다.

{: .note }
> 여기서 "오차"라는 말이 갑자기 나온 것처럼 보일 수 있는데, 바로 [앞 글](/docs/control-theory/00-linear-system/)의 선형화 과정과 이어진다.
> 앞 글에서는 비선형 시스템을 평형점 $$\mathbf{X}^{*}$$ 근방에서 선형화해서 $$\dot{\tilde{\mathbf{X}}} = \mathbf{A}\tilde{\mathbf{X}}$$ 를 얻었다.
> 이때 $$\tilde{\mathbf{X}} = \mathbf{X} - \mathbf{X}^{*}$$ 가 평형점으로부터의 오차 (편차) 다.
> 이 글에서는 표기를 단순하게 하려고 $$\tilde{\mathbf{X}}$$ 대신 $$\mathbf{X}$$ 로 쓸 뿐이고, 의미는 동일하게 "오차 상태"다.

## II. 선형 시스템의 안정성을 판정하는 방법

우리는 이전에 연속시간 선형 시스템이

$$
\dot{\mathbf{X}} = \mathbf{A}\mathbf{X}
$$

로 표현되고, 이산시간 형태는

$$
\mathbf{X}_{k+1} = \mathbf{A}_d\mathbf{X}_{k}, \qquad \mathbf{A}_d = e^{\mathbf{A}\Delta t}
$$

로 나타낼 수 있다는 것을 봤다.
결론부터 이야기하면, 안정성 판정은 "고유값이 어디에 있느냐"를 보면 된다.

### II.1. 연속 선형 시스템의 안정성 판정법

$$\mathbf{A}$$ 의 모든 고유값의 실수부가 음수이면 시스템은 점근 안정이다.
반대로 $$\mathbf{A}$$ 의 고유값 중 실수부가 양수인 값이 하나라도 있으면 시스템은 불안정하다.
즉, 연속시간에서는 고유값이 복소평면의 왼쪽 반평면(left half-plane)에 모두 있어야 한다.

참고로 실수부가 0인 고유값이 있는 경계 케이스는 추가 분석이 필요하고 이 포스팅에서는 다루지 않을 것이다.

### II.2. 이산 선형 시스템의 안정성 판정법

$$\mathbf{A}_d$$ 의 모든 고유값이 복소평면의 단위원(unit circle) 안에 있으면 시스템은 점근 안정이다.
반대로 $$\mathbf{A}_d$$ 의 고유값 중 하나라도 단위원 밖에 있으면 시스템은 불안정하다.

참고로 정확히 단위원 위에 있는 경계 케이스는 역시 추가 분석이 필요하고 이 포스팅에서는 다루지 않을 것이다.

{: .note }
> 위 II.1, II.2 절의 판정법은 고유벡터 분해(eigenvector decomposition) 관점에서 보면 더 직관적으로 이해된다.
> 다음 섹션에서 이 아이디어를 이어서 살펴보자.

## III. 연속 선형 시스템의 고유값 분해

연속 선형 시스템 $$\dot{\mathbf{X}} = \mathbf{A}\mathbf{X}$$ 에서 시스템 행렬 $$\mathbf{A}$$ 를 고유벡터로 분해하면 $$\mathbf{A}\mathbf{V} = \mathbf{V}\mathbf{\Lambda}$$ 를 얻는다 (고유벡터 분해는 필자의 [다른 글](/docs/linalg/11-evd/)을 참고).

이를 통해 $$\mathbf{A} = \mathbf{V}\mathbf{\Lambda}\mathbf{V}^{-1}$$ 로 쓸 수 있고, 시스템의 해는 아래와 같이 다시 표현된다:

$$
\begin{align}
\mathbf{X}(t) & = e^{\mathbf{A}t} \mathbf{X}(0)                     \\
& = e^{\mathbf{V}\mathbf{\Lambda}\mathbf{V}^{-1} t} \mathbf{X}(0)   \\
& = \left( \mathbf{I} + \mathbf{V}\mathbf{\Lambda}\mathbf{V}^{-1}t + \frac{\mathbf{V}\mathbf{\Lambda}^{2}\mathbf{V}^{-1}}{2!}t^2  + \cdots \right) \mathbf{X}(0) \\
& = \mathbf{V} \left( \mathbf{I} + \mathbf{\Lambda}t + \frac{\mathbf{\Lambda}^2}{2!}t^2 + \cdots \right) \mathbf{V}^{-1} \mathbf{X}(0) \\
& = \mathbf{V} e^{\mathbf{\Lambda} t} \mathbf{V}^{-1} \mathbf{X}(0)
\end{align}
$$

대각행렬의 matrix exponential은 단순히 각 대각 성분에 지수를 취한 것이므로, 결국 $$t \to \infty$$ 일 때 오차가 0으로 가는지는 각 $$e^{\lambda_i \infty}$$ 이 0으로 가는지에 달려있다.

고유값이 $$\lambda = \sigma + i\omega$$ 라고 해보자.

$$
e^{\lambda t} = e^{\sigma t} e^{i\omega t} = e^{\sigma t}(\cos(\omega t) + i\sin(\omega t))
$$

크기 (magnitude) 를 구하면 $$|e^{\lambda t}| = e^{\sigma t}$$ 임을 알 수 있고, 허수부 $$\omega$$ 는 진동만 만들 뿐, 크기는 실수부 $$\sigma$$ 에만 의존하는 것을 알 수 있다.
따라서 오차가 시간에 따라 어떻게 되는지는 $$e^{\sigma t}$$ 에만 달려있으며 $$\sigma < 0$$ 이면 진동하면서 0으로 수렴하고, $$\sigma > 0$$ 이면 진동하면서 발산한다.

정리하면, 모든 고유값의 실수부가 음수인 경우 시스템은 안정하고, 아닌 경우 불안정하다.
이것이 바로 II.1절 판정법의 이론적 근거이다.

## IV. 이산 선형 시스템의 고유값 분해

비슷하게 이산 선형 시스템 $$\mathbf{X}_{k+1} = \mathbf{A}_d\mathbf{X}_{k}$$ 에서 시스템 행렬 $$\mathbf{A}_d$$ 를 고유벡터 분해하여 $$\mathbf{A}_d\mathbf{V}_d = \mathbf{V}_d\mathbf{\Lambda}_d$$ 를 얻는다.

$$\mathbf{X}_{\infty}$$ 은 아래와 같이 정의될 수 있다:

$$
\begin{align}
\mathbf{X}_{1} & = \mathbf{A}_d \mathbf{X}_{0} = \mathbf{V}_d \mathbf{\Lambda}_d \mathbf{V}_d^{-1} \mathbf{X}_{0} \\
\mathbf{X}_{2} & = \mathbf{A}_d \mathbf{X}_{1} = \mathbf{V}_d \mathbf{\Lambda}_d^{2} \mathbf{V}_d^{-1} \mathbf{X}_{0} \\
\mathbf{X}_{3} & = \mathbf{A}_d \mathbf{X}_{2} = \mathbf{V}_d \mathbf{\Lambda}_d^{3} \mathbf{V}_d^{-1} \mathbf{X}_{0} \\
\cdots \\
\mathbf{X}_{\infty} & = \mathbf{A}_d \mathbf{X}_{\infty-1} = \mathbf{V}_d \mathbf{\Lambda}_d^{\infty} \mathbf{V}_d^{-1} \mathbf{X}_{0} \\
\end{align}
$$

따라서, $$\mathbf{X}_{\infty}$$ 의 값은 $$\mathbf{\Lambda}_d^{\infty}$$ 에 의해 결정되고, 연속시간과 마찬가지로 대각 성분의 크기를 살펴보면 된다.

대각행렬의 k제곱은 $$\mathbf{\Lambda}_d^k = \text{diag}(\lambda_1^k, \lambda_2^k, \ldots, \lambda_n^k)$$ 이므로, $$k \to \infty$$ 일 때 오차가 0으로 가는지는 각 고유값의 절댓값이 1보다 작은지에만 달려있다.

- $$\text{abs}(\lambda_i) < 1$$ 이면: $$\lambda_i^k \to 0$$ (감소)
- $$\text{abs}(\lambda_i) > 1$$ 이면: $$\text{abs}(\lambda_i^k) \to \infty$$ (발산)

따라서 모든 고유값의 절댓값이 1보다 작아야 시스템이 점근 안정이다. 이것이 II.2절 판정법의 이론적 근거다.


<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
