---
title: Observability
layout: default
nav_order: 6
parent: Control Theory
permalink: /docs/control-theory/05-observability
---

# Observability

**Keywords:** `Observability`{: .label }, `Observability Matrix`{: .label }

## I. Motivation

앞선 챕터까지 우리는 컨트롤을 포함한 선형 시스템 $$\dot{\mathbf{x}} = \mathbf{Ax} + \mathbf{Bu}$$ 를 공부해왔다.
$$\mathbf{u} = -\mathbf{Kx}$$ 로 정의함으로써 $$\dot{\mathbf{x}} = (\mathbf{A} - \mathbf{BK})\mathbf{x}$$ 를 얻고, $$\mathbf{K}$$ 를 적절히 조절하여 행렬 $$\mathbf{A} - \mathbf{BK}$$ 의 고유값을 원하는 위치로 배치해왔다.

여기서 한 가지 간과되어 온 사실이 있다.
$$\mathbf{u} = -\mathbf{Kx}$$ 라는 식은, 마치 "너는 모든 상태 변수 $$\mathbf{x}$$ 를 언제든 알 수 있고, 이를 기반으로 커맨드를 만들 수 있어"라고 전제하는 것과 같다.

그런데 당연히도 실제 상황에서 이것은 사실이 아닌 경우가 많다.
[뒤집힌 진자 카트](/docs/control-theory/04-inverted-pendulum-cart/)를 예로 들어보자.
경우에 따라 $$\theta$$ 만 측정 가능하고 $$\omega$$ 는 관측할 수 없을 수도 있다.
"그럼 나보고 $$-\mathbf{Kx}$$ 를 어떻게 만들라는 거야?"라는 의문이 자연스럽게 생긴다.
Observability는 바로 그 의문에서 출발한다.

## II. Observability 정의

우리가 직접 잴 수 있는 양을 $$\mathbf{y} \in \mathbb{R}^p$$ 라 하면 아래처럼 쓸 수 있다.

$$
\mathbf{y} = \mathbf{Cx}
$$

여기서 $$\mathbf{C} \in \mathbb{R}^{p \times n}$$ 는 **출력 행렬(output matrix)**이다.
예를 들어 $$\mathbf{x} = [x,\, v,\, \theta,\, \omega]^T$$ 인 진자 카트 시스템에서 $$\theta$$ 만 측정 가능하다면, $$\mathbf{C} = \begin{bmatrix} 0 & 0 & 1 & 0 \end{bmatrix}$$ 이 된다.

블록 다이어그램으로 그림을 그려보면 더 와 닿는다.
앞선 챕터까지는 아래 그림의 좌측처럼 시스템 출력이 곧 전체 상태 벡터 $$\mathbf{x}$$ 라고 가정하고 피드백 제어기를 만들어왔다.

그런데 실제로는 우측 그림처럼 플랜트에서 나오는 건 $$\mathbf{y}$$ 뿐이고, $$\mathbf{x}$$ 전체는 알 수가 없다.
그래서 $$\mathbf{x}$$ 를 추정해서 컨트롤러에 넘겨주는 **상태 추정기(State Estimator)** 블록이 필요해진다.
그림에서 보듯, 상태 추정기는 $$\mathbf{y}$$ 와 $$\mathbf{u}$$ 를 받아서 추정 상태 $$\hat{\mathbf{x}}$$ 를 내보낸다.

$$\hat{\mathbf{x}}$$ 를 마치 $$\mathbf{x}$$ 인 양 컨트롤러에 꽂으면, 앞선 챕터의 피드백 제어 설계를 그대로 써먹을 수 있다.

![](/docs/control-theory/05-observability/figures/fig00.png)

결국 Observability의 핵심 질문은 $$\mathbf{y}$$ 와 $$\mathbf{u}$$ 만 가지고 $$\mathbf{x}$$ 를 복원할 수 있는가이고, 복원할 수 있다면 **observable**, 없다면 **not observable**이다.


## III. Observability 검사방법

아주 행복하게도 (?) observability는 controllability와 많은 것이 duality 관계에 있다.
그래서, 이 챕터에서는 observability에 대한 내용을 자세히 소개하며 지면을 할애하기 보다는 duality에 초점을 맞추어서 설명을 해보려고 한다.

## III.1. Observability Matrix

Observability matrix $$\mathcal{O}$$ 는 아래와 같이 정의된다.

$$
\mathcal{O} =
\begin{bmatrix}
\mathbf{C} \\
\mathbf{CA} \\
\mathbf{CA}^2 \\
\vdots \\
\mathbf{CA}^{n-1}
\end{bmatrix}
$$

Controllability matrix가 $$\mathbf{B}$$ 를 $$\mathbf{A}$$ 로 반복해서 **곱하여 열로 쌓는** 것이었다면, observability matrix는 $$\mathbf{C}$$ 를 $$\mathbf{A}$$ 로 반복해서 **곱하여 행으로 쌓는** 것이다.
전자가 입력이 시스템을 타고 퍼지는 방향을 모으는 거라면, 후자는 상태가 출력에 얼마나 드러나는지를 방향별로 모으는 거라 보면 된다.

시스템이 observable하기 위한 필요충분조건은 $$\text{rank}(\mathcal{O}) = n$$ 이다 (**Kalman Rank Condition**).
왜 이게 맞는지 직관적으로 생각해보자.
출력 $$\mathbf{y}(t) = \mathbf{C}\mathbf{x}(t)$$ 를 시간에 따라 미분하면 상태 $$\mathbf{x}(0)$$ 에 대한 정보를 조금씩 더 끌어낼 수 있다.

$$
\begin{aligned}
\mathbf{y}(0) &= \mathbf{C}\mathbf{x}(0) \\
\dot{\mathbf{y}}(0) &= \mathbf{C}\dot{\mathbf{x}}(0) = \mathbf{CA}\mathbf{x}(0) \\
\ddot{\mathbf{y}}(0) &= \mathbf{CA}^2\mathbf{x}(0) \\
&\vdots \\
\mathbf{y}^{(n-1)}(0) &= \mathbf{CA}^{n-1}\mathbf{x}(0)
\end{aligned}
$$

이를 하나의 방정식으로 묶으면,

$$
\underbrace{\begin{bmatrix} \mathbf{y}(0) \\ \dot{\mathbf{y}}(0) \\ \vdots \\ \mathbf{y}^{(n-1)}(0) \end{bmatrix}}_{\text{측정 가능}} = \mathcal{O}\, \mathbf{x}(0)
$$

좌변은 출력 $$\mathbf{y}$$ 를 보면서 직접 계산할 수 있는 값들이고, $$\mathbf{x}(0)$$ 이 우리가 구하고 싶은 미지수다.
$$\mathbf{x}(0)$$ 를 유일하게 풀려면 $$\mathcal{O}$$ 의 rank가 $$n$$ 이어야 한다.

{: .note }
> 그런데 왜 $$n-1$$ 번 미분까지만 쌓으면 되는 걸까?
> [앞선 챕터](/docs/control-theory/03-controllability-test/)에서 소개한 Cayley-Hamilton 정리를 떠올려보자.
> Cayley-Hamilton 정리에 따르면 $$\mathbf{A}^n$$ 이상의 거듭제곱은 $$\mathbf{I}, \mathbf{A}, \ldots, \mathbf{A}^{n-1}$$ 의 선형 결합으로 표현된다.
> 따라서 $$n$$ 번째 미분부터 등장하는 $$\mathbf{CA}^n, \mathbf{CA}^{n+1}, \ldots$$ 는 이미 $$\mathbf{C}, \mathbf{CA}, \ldots, \mathbf{CA}^{n-1}$$ 의 행들의 선형 결합이다.
> 아무리 미분을 더 해도 $$\mathcal{O}$$ 에 새로운 행이 독립적으로 추가되지 않으므로, $$n-1$$ 번까지만 확인하면 충분하다.

## III.2. Observability Gramian

[앞선 챕터](/docs/control-theory/03-controllability-test/)에서 controllability Gramian이 $$\mathcal{C}$$ 와 짝을 이뤘던 것처럼, observability에도 대응하는 Gramian이 있다.

$$
\mathbf{W}_o(t) = \int_0^t e^{\mathbf{A}^T\tau}\mathbf{C}^T\mathbf{C}\,e^{\mathbf{A}\tau}\,d\tau
$$

그리고 마찬가지로 $$\mathbf{W}_o(t) \approx \mathcal{O}^T\mathcal{O}$$ 가 성립한다.

여기서 한 발짝 더 나갈 수 있다.
$$\mathcal{O} = \mathbf{U}\mathbf{\Sigma}\mathbf{V}^T$$ 로 SVD를 하면 $$\mathcal{O}^T\mathcal{O} = \mathbf{V}\mathbf{\Sigma}^2\mathbf{V}^T$$ 이 되고, $$\mathbf{V}$$ 의 각 열이 고유벡터, $$\mathbf{\Sigma}^2$$ 의 각 성분이 고유값 역할을 한다.

{: .note }
> [앞선 챕터](/docs/control-theory/03-controllability-test/)에서 controllability Gramian을 분석할 때는 $$\mathcal{C}$$ 의 SVD에서 $$\mathbf{U}$$ 를 봤는데, 여기서는 왜 $$\mathbf{V}$$ 를 보는가?
> 이유는 행렬의 모양이 다르기 때문이다.
> $$\mathcal{C}$$ 는 $$n \times nm$$ 으로 **가로로 넓은** 행렬이다. 따라서 $$\mathcal{C}\mathcal{C}^T = \mathbf{U}\mathbf{\Sigma}^2\mathbf{U}^T$$ 가 $$n \times n$$ 이 되고, 상태 공간 $$\mathbb{R}^n$$ 위의 방향이 $$\mathbf{U}$$ 에 담긴다.
> 반면 $$\mathcal{O}$$ 는 $$np \times n$$ 으로 **세로로 긴** 행렬이다. 따라서 $$\mathcal{O}^T\mathcal{O} = \mathbf{V}\mathbf{\Sigma}^2\mathbf{V}^T$$ 가 $$n \times n$$ 이 되고, 상태 공간 위의 방향이 $$\mathbf{V}$$ 에 담긴다.
> 모양은 달라도 결국 "상태 공간에서 어떤 방향인가"를 보는 것이라는 점은 동일하다.

특이값 $$\sigma_i$$ 가 클수록 그 방향의 상태 변화가 출력에 잘 드러나는 거고, 반대로 특이값이 작으면 그 방향은 출력에 거의 안 보여서 추정하기 힘들다.

 controllability에서 "어떤 방향을 제어하기 쉬운가"를 $$\mathcal{C}$$ 의 SVD로 봤듯, observability에서는 "어떤 방향의 상태가 출력에 잘 보이는가"를 $$\mathcal{O}$$ 의 SVD로 확인하면 된다. 완전히 대칭적인 구조다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
