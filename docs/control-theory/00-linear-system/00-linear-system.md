---
title: Linear System
layout: default
parent: Control Theory
permalink: /docs/control-theory/00-linear-system
---

# Linear System

**Keywords:** `Linear System`{: .label }

## I. 선형 시스템의 행렬 표현

앞으로 다룰 문제들은 모두 행렬 형태로 기술할 것이다.
우선 결론부터 말하면, 선형 시스템의 행렬 표현은 다음과 같다.

$$
\begin{align}
\dot{\mathbf{X}} & = \mathbf{A}\mathbf{X}
\end{align}
$$

왜 이 형태가 선형인지 궁금하다면 이어지는 서브섹션을 참고하고, 그렇지 않다면 다음 섹션으로 넘어가도 좋다.
시스템이 선형인지 판정하려면 **가산성 (additivity)** 과 **동차성 (homogeneity)** 을 만족하는지 확인하면 된다.
즉, 두 해를 더한 것도 해가 되는지, 또한 한 해에 임의의 상수를 곱한 것도 해가 되는지를 확인하는 것이다.

### I.1. 가산성 (Additivity)

- $$\mathbf{X}_{1}$$ 과 $$\mathbf{X}_{2}$$ 이 각각 $$\dot{\mathbf{X}} = \mathbf{A}\mathbf{X}$$ 의 해라고 가정하자.
- 그러면 $$\dot{\mathbf{X}_1} = \mathbf{A}\mathbf{X}_1$$ 이고 $$\dot{\mathbf{X}_2} = \mathbf{A}\mathbf{X}_2$$ 이다.
- 두 식을 더하면 $$\dot{\mathbf{X}_1} + \dot{\mathbf{X}_2} = \mathbf{A}\mathbf{X}_1 + \mathbf{A}\mathbf{X}_2$$ 를 얻는다.
- $$\mathbf{Z} = \mathbf{X}_1 + \mathbf{X}_2$$ 로 정의하면 $$\dot{\mathbf{Z}} = \mathbf{A}\mathbf{Z}$$ 를 얻을 수 있고, 두 해를 더한 것도 역시 해가 됨을 알 수 있다.

### I.2. 동차성 (Homogeneity)

- $$\mathbf{X}_{1}$$ 이 $$\dot{\mathbf{X}} = \mathbf{A}\mathbf{X}$$ 의 해라고 가정하자.
- 그러면 $$\dot{\mathbf{X}_1} = \mathbf{A}\mathbf{X}_1$$ 이다.
- 양변에 임의의 상수 $$k$$ 를 곱하면 $$k\dot{\mathbf{X}_1} = k \mathbf{A}\mathbf{X}_1$$ 를 얻는다.
- $$\mathbf{Z} = k \mathbf{X}_1$$ 로 정의하면 $$\dot{\mathbf{Z}} = \mathbf{A}\mathbf{Z}$$ 를 얻을 수 있고, 해에 상수를 곱한 것도 역시 해가 됨을 알 수 있다.

## II. 행렬로 표현된 선형 시스템의 해

역시 결론부터 말하면, $$\dot{\mathbf{X}} = \mathbf{A}\mathbf{X}$$ 의 해는 $$\mathbf{X}(t) = e^{\mathbf{A}t} \mathbf{X}(0)$$ 이다.
그리고 $$e^{\mathbf{A}t}$$ 는 행렬 지수함수(matrix exponential)라 하며, $$e^{\mathbf{A}t} = \mathbf{I} + \mathbf{A}t + \frac{(\mathbf{A}t)^2}{2!} + \frac{(\mathbf{A}t)^3}{3!} + \cdots$$ 와 같이 정의된다.
이건 예제 몇개를 가지고 직접 풀어보면 사뭇 자명한데, 필자는 귀찮아서 그냥 받아들였다.

## III. 이산 선형 시스템

연속시간 시스템 $$\dot{\mathbf{X}} = \mathbf{A} \mathbf{X}$$ 의 이산시간 형태는 아래와 같다.

$$
\begin{align}
\mathbf{X}_{k+1} = e^{\mathbf{A} \Delta t} \mathbf{X}_{k}
\end{align}
$$

유도는 아래와 같다:

- $$\dot{\mathbf{X}} = \mathbf{A} \mathbf{X}$$ 의 해는 $$\mathbf{X}(t) = e^{\mathbf{A}t} \mathbf{X}(0)$$ 이다.
- 따라서, $$\mathbf{X}(t + \Delta t) = e^{\mathbf{A}(t + \Delta t)}\mathbf{X}(0)$$ 이다.
- 지수법칙을 이용하면, $$\mathbf{X}(t + \Delta t) = e^{\mathbf{A}(t + \Delta t)}\mathbf{X}(0) = e^{\mathbf{A}\Delta t}e^{\mathbf{A}t}\mathbf{X}(0) = e^{\mathbf{A}\Delta t}\mathbf{X}(t)$$ 이다.
- $$t = k\Delta t$$ 로 두고 $$\mathbf{X}_k = \mathbf{X}(k\Delta t)$$ 로 정의하면, $$\mathbf{X}_{k+1} = e^{\mathbf{A}\Delta t}\mathbf{X}_k$$ 를 얻는다.


## IV. 행렬로 표현된 선형 시스템의 예시

고전적인 질량-스프링-댐퍼(mass-spring-damper) 시스템을 생각해보자.
질량-스프링-댐퍼 시스템은 $$m\ddot{x} + c\dot{x} + kx = 0$$ 으로 표현된다.
상태벡터를 $$\mathbf{X} = [x \; \dot{x}]^T$$ 로 정의하면, 이 시스템은 아래와 같이 표현할 수 있다.

$$
\begin{align}
\dot{\mathbf{X}} & = \mathbf{A} \mathbf{X} \\
\left[\begin{array}{c}
\dot{x}         \\
\ddot{x}        \\
\end{array}\right] & =
\left[\begin{array}{cc}
0               & 1             \\
-\frac{k}{m}    & -\frac{c}{m}  \\
\end{array}\right]
\left[\begin{array}{c}
x               \\
\dot{x}         \\
\end{array}\right]
\end{align}
$$

이 시스템의 해 역시 $$\mathbf{X}(t) = e^{\mathbf{A}t} \mathbf{X}(0)$$ 이다.
위에서 소개한 행렬 지수함수 정의에 따라 $$e^{\mathbf{A}t}$$ 를 전개해 보면, 공학수학에서 배운 해와 정확히 일치함을 확인할 수 있다.

## V. 비선형 시스템을 선형화하는 방법

마지막으로 비선형 시스템을 선형화하는 방법을 살펴보자.
대부분의 경우 풀어야 할 (제어해야 할) 시스템은 비선형으로 표현된다.
이때는 테일러 급수(Taylor series)를 이용해 주어진 비선형 시스템을 특정 평형점 근방에서 선형 시스템으로 근사할 수 있다.
행렬로 표현되는 시스템의 선형화에는 야코비안(Jacobian)이 등장하므로, 예제를 통해 단계별로 설명한다.

$$\ddot{\theta} = -\frac{g}{L}\sin{\theta} - \delta \dot{\theta}$$ 와 같이 표현되는 간단한 진자운동을 생각해보자.
$$\mathbf{X} = [\theta \; \dot{\theta}]^T$$ 라고 정의해보자.
이것을 $$\dot{\mathbf{X}} = \mathbf{A}\mathbf{X}$$ 의 꼴로 나타낼 수 있는가?
중간에 섞여있는 $$\sin{\theta}$$ 때문에 불가능하고, 이것은 대표적인 비선형 시스템이다.
이제 이것을 선형화를 통해 선형 시스템으로 근사해보자.

먼저 주어진 비선형 시스템을 $$\dot{\mathbf{X}} = \mathbf{f}(\mathbf{X})$$ 형태로 표현하면 다음과 같다.

$$
\begin{align}
\dot{\mathbf{X}} & =
\mathbf{f}(\mathbf{X}) =
\left[\begin{array}{c}
\dot{\theta}                                        \\
-\dfrac{g}{L}\sin{\theta} - \delta\dot{\theta}      \\
\end{array}\right]
\end{align}
$$

이제 평형점 $$\mathbf{X}^{*} = [\theta^{*} \; \dot{\theta}^{*}]^T$$ 근방에서 $$\mathbf{f}(\mathbf{X})$$ 를 1차 테일러 전개하면 다음과 같다 (즉, $$\mathbf{f}(\mathbf{X}^{*}) = \mathbf{0}$$ 인 $$\mathbf{X}^{*}$$ ).

$$
\begin{align}
\mathbf{f}(\mathbf{X}) \approx \mathbf{f}(\mathbf{X}^{*}) + \left.\frac{\partial \mathbf{f}}{\partial \mathbf{X}}\right|_{\mathbf{X}^{*}} (\mathbf{X} - \mathbf{X}^{*})
\end{align}
$$

$$\tilde{\mathbf{X}} = \mathbf{X} - \mathbf{X}^{*}$$ 로 정의하면, 평형점에서 $$\mathbf{f}(\mathbf{X}^{*}) = \mathbf{0}$$ 이므로 다음을 얻는다.

$$
\begin{align}
\dot{\tilde{\mathbf{X}}} \approx \underbrace{\left.\frac{\partial \mathbf{f}}{\partial \mathbf{X}}\right|_{\mathbf{X}^{*}}}_{\triangleq\, \mathbf{A}} \tilde{\mathbf{X}}
\end{align}
$$

시스템 행렬 $$\mathbf{A}$$ 는 야코비안으로 계산한다.

$$
\begin{align}
\mathbf{A} = \left.\frac{\partial \mathbf{f}}{\partial \mathbf{X}}\right|_{\mathbf{X}^{*}} =
\left[\begin{array}{cc}
\dfrac{\partial f_1}{\partial \theta} & \dfrac{\partial f_1}{\partial \dot{\theta}} \\[8pt]
\dfrac{\partial f_2}{\partial \theta} & \dfrac{\partial f_2}{\partial \dot{\theta}} \\
\end{array}\right]_{\mathbf{X}^{*}}
=
\left[\begin{array}{cc}
0                               & 1       \\
-\dfrac{g}{L}\cos{\theta^{*}}  & -\delta \\
\end{array}\right]
\end{align}
$$

진자의 정지 평형점 $$\mathbf{X}^{*} = [0 \; 0]^T$$ 를 대입하면 $$\cos(0) = 1$$ 이므로 시스템 행렬은 다음과 같다.

$$
\begin{align}
\mathbf{A} =
\left[\begin{array}{cc}
0              & 1       \\
-\dfrac{g}{L}  & -\delta \\
\end{array}\right]
\end{align}
$$

따라서, 진자 시스템은 $$\mathbf{X}^{*} = [0 \; 0]^T$$ 근방에서 아래의 선형 시스템으로 근사된다.

$$
\begin{align}
\dot{\tilde{\mathbf{X}}} = \mathbf{A}\tilde{\mathbf{X}}, \qquad
\mathbf{A} =
\left[\begin{array}{cc}
0              & 1       \\
-\dfrac{g}{L}  & -\delta \\
\end{array}\right]
\end{align}
$$

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
