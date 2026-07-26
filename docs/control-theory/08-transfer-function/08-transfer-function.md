---
title: Transfer Function
layout: default
nav_order: 9
parent: Control Theory
permalink: /docs/control-theory/08-transfer-function
---

# Transfer Function

## TOC
{: .no_toc }

1. TOC
{:toc}

**Keywords:** `transfer function`{: .label }

## I. Three equivalent representation of LTI system

$$
\begin{aligned}
\dot{\mathbf{x}} & = \mathbf{Ax} + \mathbf{Bu} \\
\mathbf{y} & = \mathbf{Cx}
\end{aligned}
$$

필자는 앞선 챕터들에서 선형시스템을 위와 같이 표현하고 설명해왔다.
계속 위와 같은 표기만을 사용해왔기에 딱히 언급하지는 않았지만, 사실 위와 같은 표현을 state space representation이라고 부른다.
그리고 이 표현은 time domain, frequency domain에서 각각 동치인 다른 표현을 가진다.
이 섹션에는 이들에 대해 간략히 그 식과 모양을 개괄할 것이고, 이어지는 챕터에서 보다 자세히 설명할 것이다.

### I.1. Time domain representation

Time domain에서 시스템은 impulse response $$h(t)$$ 를 이용한 convolution으로 표현할 수 있다.
각 시점의 입력이 출력에 어떻게 누적되는지를 그대로 보여준다는 점에서 꽤 직관적이다.
참고로 time domain 관점은 이 포스팅에서 길게 파고들 생각은 없다.
이는 컨볼루션 식 자체가 "각 순간의 입력이 impulse response를 통해 출력에 누적된다"는 사실을 거의 그대로 보여주기 때문에, 직관을 잡는 데에는 이 정도면 충분하다고 보았기 때문이다.

$$
y(t) = (h * u)(t) = \int_0^t h(\tau)u(t-\tau)\,d\tau
$$

### I.2. Frequency domain representation

Frequency domain에서 선형시스템을 표현한다는 말은 곧 전달함수를 이야기하는 것이다.
달리 말하면 [Laplace transform](/docs/topic-dive/07-laplace-transform/)을 이용해 입력과 출력의 비를 표현하는 것이고, 초기조건이 0이라고 가정하면 결론은 아래 한 줄로 정리된다.

$$
G(s) = \frac{Y(s)}{U(s)} = \mathbf{C}(s\mathbf{I}-\mathbf{A})^{-1}\mathbf{B}
$$

## II. Transfer Function

이제 본격적으로 전달함수를 살펴보자.
식부터 주절주절 적으면 괴로우니 우선 근저에 있는 직관부터 설명해보도록 하겠다.
근저의 직관은 선형 시불변(LTI) 시스템에 사인파를 넣으면, 정상상태 출력도 같은 주파수의 사인파로 나온다는 사실이다.
다만 출력은 입력에 비해 진폭이 커지거나 작아지고, 위상은 앞서거나 뒤처질 수 있다.

$$
u(t)=\sin(\omega t)
\quad\Rightarrow\quad
y_{ss}(t)=|G(j\omega)|\sin\big(\omega t+\angle G(j\omega)\big)
$$

{: .note }
> **정상상태 출력(steady-state output)** 이란, 입력을 가한 직후 잠깐 나타나는 과도응답(transient response)이 충분히 사라진 뒤에 남는 출력 성분을 뜻한다.
> 즉 출력은 보통 $$y(t)=y_{tr}(t)+y_{ss}(t)$$ 로 볼 수 있고, 여기서 전달함수의 주파수 응답 $$G(j\omega)$$ 가 직접 알려주는 것은 $$y_{ss}(t)$$ 의 진폭비와 위상차다.
> 그래서 사인파 응답을 볼 때는 "처음 잠깐"이 아니라 "시간이 지난 뒤" 파형을 기준으로 해석한다.

즉 전달함수는 입력 신호의 주파수 $$\omega$$ 별로 시스템이 (1) 출력의 진폭을 얼마나 키우거나 줄이는지 ($$\|G(j\omega)\|$$) (2) 출력의 위상을 얼마나 앞당기거나 늦추는지 ($$\angle G(j\omega)$$)를 알려주는 지도라고 볼 수 있다.
실제 시스템 1차 저역통과 필터 예를 하나 살펴보자.
시간 도메인 입력-출력 식으로는 보통 아래처럼 쓴다.

$$
\dot{y}(t)+y(t)=u(t)
$$

이 식은 "출력이 입력을 따라가되, 순간적으로는 완전히 따라가지 못한다"는 의미를 담고 있다.
여기서 상태를 $$x=y$$ 로 두면 같은 시스템을 state space 형태로 나타낼 수 있다.

$$
\begin{aligned}
\dot{\mathbf{x}} &= [-1]\mathbf{x} + [1]\mathbf{u} \\
\mathbf{y} &= [1]\mathbf{x}
\end{aligned}
$$

여기서 $$\mathbf{A}=[-1],\quad \mathbf{B}=[1],\quad \mathbf{C}=[1]$$ 이다.

따라서, 이 시스템의 전달함수와 주파수 응답은 아래와 같이 구해짐을 알 수 있다.

$$
G(s)=\mathbf{C}(s\mathbf{I}-\mathbf{A})^{-1}\mathbf{B}
=1\cdot\frac{1}{s+1}\cdot1
=\frac{1}{s+1}
$$

$$
|G(j\omega)|=\frac{1}{\sqrt{1+\omega^2}},
\qquad
\angle G(j\omega)=-\tan^{-1}(\omega)
$$

예를 들어 $$\omega=0.5$$ 일 때는 $$|G(j\omega)|\approx0.894$$, $$\angle G(j\omega)\approx-0.464\,\text{rad}$$ 이고,
$$\omega=4.0$$ 일 때는 $$|G(j\omega)|\approx0.243$$, $$\angle G(j\omega)\approx-1.326\,\text{rad}$$ 다.
즉 같은 시스템이어도 주파수가 높아질수록 진폭은 더 줄고 위상 지연은 더 커진다.
아래 그림은 위 두 주파수에 대해 실제로 $$u(t)=\sin(\omega t)$$ 를 넣었을 때의 정상상태 출력을 그린 것이다.

![transfer function real example](/docs/control-theory/08-transfer-function/assets/transfer-function-real-example.png)

## III. Bode Plot

전달함수의 주파수 응답 $$G(j\omega)$$를 시각적으로 표현하는 가장 대표적인 방법이 바로 **Bode plot**이다.
Bode plot은 두 개의 그래프로 이루어지는데, 하나는 크기(magnitude) 응답이고 다른 하나는 위상(phase) 응답이다.
두 그래프 모두 횟축에 로그 스케일로 주파수 $$\omega$$를 표시한다.

### III.1. Magnitude Plot

Magnitude plot에서는 $$\|G(j\omega)\|$$ 를 **dB (decibel)** 단위로 표현한다.
dB 스케일을 사용하는 이유는 넓은 범위의 주파수 응답을 한 그래프에 나타낼 수 있기 때문이다.
선형 스케일에서는 큰 값들이 지배적이 되어 작은 값들을 구별하기 어려워진다.

$$
\text{Magnitude (dB)} = 20\log_{10}|G(j\omega)|
$$

위의 1차 저역통과 필터 예제에서는

$$
20\log_{10}|G(j\omega)| = 20\log_{10}\frac{1}{\sqrt{1+\omega^2}} = -10\log_{10}(1+\omega^2)
$$

가 되고, 아래는 위 1차 저역통과 필터 시스템의 magnitude 응답을 시각화한 것이다.
저주파에서는 거의 0 dB를 유지하다가 corner frequency인 $$\omega=1$$ 근처에서 -3 dB를 지나 고주파에서는 -20 dB/decade의 기울기로 떨어진다.

![Bode magnitude plot](/docs/control-theory/08-transfer-function/assets/bode-magnitude-plot.png)

### III.2. Phase Plot

Phase plot에서는 $$\angle G(j\omega)$$를 도(degree) 또는 라디안(radian) 단위로 표현한다.
위의 예제에서는

$$
\angle G(j\omega) = -\tan^{-1}(\omega)
$$

이고, 아래는 위 1차 저역통과 필터 시스템의 phase 응답을 시각화한 것이다.
저주파에서는 거의 0°이다가 corner frequency인 $$\omega=1$$ 근처에서 급격히 변하고, 고주파에서는 -90°로 수렴한다.

![Bode phase plot](/docs/control-theory/08-transfer-function/assets/bode-phase-plot.png)

## IV. Transfer Function from State Space Representation

이 섹션에서는 앞서 I.2에서 제시한 식

$$
G(s) = \frac{Y(s)}{U(s)} = \mathbf{C}(s\mathbf{I}-\mathbf{A})^{-1}\mathbf{B}
$$

가 state space representation으로부터 어떻게 유도되는지를 상세히 보이겠다.

### IV.1. Applying Laplace Transform

State space representation은 다음과 같다.

$$
\begin{aligned}
\dot{\mathbf{x}} &= \mathbf{A}\mathbf{x} + \mathbf{B}\mathbf{u} \\
\mathbf{y} &= \mathbf{C}\mathbf{x}
\end{aligned}
$$

양변에 Laplace transform을 적용하면 (초기조건이 0이라고 가정):

$$
s\mathbf{X}(s) = \mathbf{A}\mathbf{X}(s) + \mathbf{B}\mathbf{U}(s)
$$

출력의 Laplace transform은:

$$
\mathbf{Y}(s) = \mathbf{C}\mathbf{X}(s)
$$

### IV.2. Solving for $$\mathbf{X}(s)$$

첫 번째 식을 정리하면:

$$
s\mathbf{X}(s) - \mathbf{A}\mathbf{X}(s) = \mathbf{B}\mathbf{U}(s)
$$

$$
(s\mathbf{I} - \mathbf{A})\mathbf{X}(s) = \mathbf{B}\mathbf{U}(s)
$$

양변에 $$(s\mathbf{I} - \mathbf{A})^{-1}$$를 곱하면:

$$
\mathbf{X}(s) = (s\mathbf{I} - \mathbf{A})^{-1}\mathbf{B}\mathbf{U}(s)
$$

### IV.3. Deriving the Transfer Function

출력 식에 위에서 구한 $$\mathbf{X}(s)$$를 대입하면:

$$
\mathbf{Y}(s) = \mathbf{C}\mathbf{X}(s) = \mathbf{C}(s\mathbf{I} - \mathbf{A})^{-1}\mathbf{B}\mathbf{U}(s)
$$

따라서 전달함수는:

$$
G(s) = \frac{\mathbf{Y}(s)}{\mathbf{U}(s)} = \mathbf{C}(s\mathbf{I} - \mathbf{A})^{-1}\mathbf{B}
$$

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>

