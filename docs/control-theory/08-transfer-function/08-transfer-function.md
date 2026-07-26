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

## I. 선형시스템의 세가지 표현 방법

필자는 앞선 챕터들에서 선형시스템을 아래와 같이 표현하고 설명해왔다.

$$
\begin{aligned}
\dot{\mathbf{x}} & = \mathbf{Ax} + \mathbf{Bu} \\
\mathbf{y} & = \mathbf{Cx}
\end{aligned}
$$

사실 위와 같은 표현을 state space representation이라고 부른다.
그리고 이 표현은 time domain, frequency domain에서 각각 동치인 다른 표현을 가진다.
우선 여기서는 식만 적고, 자세한 설명은 이어지는 챕터에서 다루도록 하겠다.

### I.1. Time domain representation

Time domain에서 시스템은 impulse response $$h(t)$$ 를 이용한 convolution으로 표현할 수 있다.
각 시점의 입력이 출력에 어떻게 누적되는지를 그대로 보여준다는 점에서 꽤 직관적이다.
참고로 time domain 관점은 이 포스팅에서 길게 파고들 생각은 없다.
컨볼루션 식 자체가 "각 순간의 입력이 impulse response를 통해 출력에 누적된다"는 사실을 거의 그대로 보여주기 때문에, 직관을 잡는 데에는 이 정도면 충분하다고 본다.

$$
y(t) = (h * u)(t) = \int_0^t h(\tau)u(t-\tau)\,d\tau
$$

### I.2. Frequency domain representation

말은 frequency domain이라고 했지만, 여기서 하고 싶은 이야기는 결국 전달함수다.
달리 말하면 [Laplace transform](/docs/topic-dive/07-laplace-transform/)을 이용해 입력과 출력의 비를 표현하는 것이고, 초기조건이 0이라고 가정하면 결론은 아래 한 줄로 정리된다.

$$
G(s) = \frac{Y(s)}{U(s)} = \mathbf{C}(s\mathbf{I}-\mathbf{A})^{-1}\mathbf{B}
$$

## II. 전달함수

이제 본격적으로 전달함수를 보자.
핵심 직관은 단순하다.
선형 시불변(LTI) 시스템에 사인파를 넣으면, 정상상태 출력도 같은 주파수의 사인파로 나온다.
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

즉 전달함수는 주파수 $$\omega$$ 별로

1. 진폭을 얼마나 키우거나 줄이는지 ($$\|G(j\omega)\|$$)
2. 위상을 얼마나 앞당기거나 늦추는지 ($$\angle G(j\omega)$$)

를 알려주는 지도라고 볼 수 있다.

실제 시스템 1차 저역통과 필터 예를 하나 살펴보자.
"1차 저역통과"라는 말이 낯설다면, 일단 아래처럼 이해하면 된다.

1. 입력이 천천히 변하면 출력이 비교적 잘 따라간다.
2. 입력이 빠르게 흔들리면 출력은 그 변화를 다 따라가지 못한다.

즉, 느린 변화(저주파)는 통과시키고 빠른 변화(고주파)는 깎아내리는 필터다.
시간 도메인 입력-출력 식으로는 보통 아래처럼 쓴다.

$$
\dot{y}(t)+y(t)=u(t)
$$

이 식은 "출력이 입력을 따라가되, 순간적으로는 완전히 따라가지 못한다"는 의미를 담고 있다.
여기서 상태를 $$x=y$$ 로 두면 같은 시스템을 state space로 바로 쓸 수 있다.

$$
\dot{x}=-x+u,
\qquad
y=x
$$

행렬 형태로 쓰면 아래와 같다.

$$
\mathbf{A}=[-1],\quad
\mathbf{B}=[1],\quad
\mathbf{C}=[1],\quad
\mathbf{D}=[0]
$$

따라서, 이 시스템의 전달함수는 아래와 같이 구해진다.

$$
G(s)=\mathbf{C}(s\mathbf{I}-\mathbf{A})^{-1}\mathbf{B}
=1\cdot\frac{1}{s+1}\cdot1
=\frac{1}{s+1}
$$

이제 이 전달함수의 주파수 응답을 보면

$$
|G(j\omega)|=\frac{1}{\sqrt{1+\omega^2}},
\qquad
\angle G(j\omega)=-\tan^{-1}(\omega)
$$

이 식이 왜 나오는지 한 줄씩 풀어보자.

먼저 전달함수

$$
G(s)=\frac{1}{s+1}
$$

에서 주파수 응답을 보려면 $$s=j\omega$$ 를 대입한다.

$$
G(j\omega)=\frac{1}{1+j\omega}
$$

이제 실수부/허수부를 분리하기 위해 분모의 켤레복소수 $$1-j\omega$$ 를 곱한다.

$$
G(j\omega)
=\frac{1}{1+j\omega}\cdot\frac{1-j\omega}{1-j\omega}
=\frac{1-j\omega}{(1+j\omega)(1-j\omega)}
=\frac{1-j\omega}{1+\omega^2}
$$

따라서

$$
G(j\omega)=\frac{1}{1+\omega^2}-j\frac{\omega}{1+\omega^2}
$$

이므로 실수부/허수부는 각각

$$
\Re\{G(j\omega)\}=\frac{1}{1+\omega^2},
\qquad
\Im\{G(j\omega)\}=-\frac{\omega}{1+\omega^2}
$$

가 된다.

복소수 $$a+jb$$ 의 크기와 위상은

$$
|a+jb|=\sqrt{a^2+b^2},
\qquad
\angle(a+jb)=\tan^{-1}\!\left(\frac{b}{a}\right)
$$

이므로,

$$
|G(j\omega)|
=\sqrt{\left(\frac{1}{1+\omega^2}\right)^2+\left(-\frac{\omega}{1+\omega^2}\right)^2}
=\sqrt{\frac{1+\omega^2}{(1+\omega^2)^2}}
=\frac{1}{\sqrt{1+\omega^2}}
$$

그리고 위상은

$$
\angle G(j\omega)
=\tan^{-1}\!\left(\frac{-\omega/(1+\omega^2)}{1/(1+\omega^2)}\right)
=\tan^{-1}(-\omega)
=-\tan^{-1}(\omega)
$$

를 얻는다.

즉,

$$
|G(j\omega)|=\frac{1}{\sqrt{1+\omega^2}},
\qquad
\angle G(j\omega)=-\tan^{-1}(\omega)
$$

가 정확히 위 계산에서 나온 결과다.

예를 들어 $$\omega=0.5$$ 일 때는 $$|G(j\omega)|\approx0.894$$, $$\angle G(j\omega)\approx-0.464\,\text{rad}$$ 이고,
$$\omega=4.0$$ 일 때는 $$|G(j\omega)|\approx0.243$$, $$\angle G(j\omega)\approx-1.326\,\text{rad}$$ 다.
즉 같은 시스템이어도 주파수가 높아질수록 진폭은 더 줄고 위상 지연은 더 커진다.
아래 그림은 위 두 주파수에 대해 실제로 $$u(t)=\sin(\omega t)$$ 를 넣었을 때의 정상상태 출력을 그린 것이다.

![transfer function real example](/docs/control-theory/08-transfer-function/assets/transfer-function-real-example.png)

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>

