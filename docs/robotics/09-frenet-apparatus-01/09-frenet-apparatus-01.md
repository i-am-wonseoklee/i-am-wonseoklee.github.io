---
title: Frenet Apparatus II
layout: default
parent: Robotics
permalink: /docs/robotics/09-frenet-apparatus-01
---

# Frenet Apparatus II

**Keywords:** `Frenet Serret Frame`{: .label }, `TNB Frame`{: .label }, `Frenet Serret Theorem`{: .label }, `Frenet Apparatus`{: .label }

이전 포스팅 ([Frenet Apparatus I](/docs/robotics/07-frenet-apparatus-00)) 에서는 주어진 curve가 unit speed curve임을 가정하고 Frenet apparatus를 유도하였다.
그런데, 현실 세계에서는 non-unit speed curve [^1] 가 훨씬 많거니와 [arc-length reparameterization](/docs/robotics/06-arc-length-reparameterization)을 하는 것도 어려울 수 있다.
그래서, 이 포스팅에서는 주어진 non-unit speed regular [^2] curve $$\alpha(t)$$로부터 곧바로 Frenet apparatus를 구하는 방법을 소개해보려고 한다.

{: .note }
> 이 포스팅에서 소개할 공식들의 유도를 위해서는 chain-rule이 자주 사용된다.
> 그런데, 이것이 적다보면 몹시 헷갈리므로 필자는 이 포스팅에서만큼은 집요하게 라이프니츠식 표현을 사용할 것이다.
> 예를 들어, 앞선 포스팅에서 $$\mathbf{T}^{\prime}(s)$$와 같이 뉴턴식 표기를 사용했던 것도 이 포스팅에서는 $$\frac{d}{ds}\mathbf{T}(s)$$와 같이 표기할 것이다.

## Goals

실제로는 구하기 어렵겠지만, 어떻게든 당신이 $$\alpha(t)$$의 arc-length function $$s(t)$$를 구해서 arc-length reparameterized curve $$\bar{\alpha}(s(t))$$를 구했다고하자.
앞으로의 표기에서 bar ($$\bar{\quad}$$) 는 arc length reparameterized curve에 대한 값들임을 나타내는데 사용할 것이다.
이제 우리의 목표는 실제로 $$s(t)$$를 구하지 않고, 아래와 같이 정의되는 5개의 Frenet apparatus를 구하는 공식을 찾는 것이다.

- Unit tangent vector field: $$\mathbf{T}(t) = \bar{\mathbf{T}}(s(t))$$
- Unit principal normal vector field: $$\mathbf{N}(t) = \bar{\mathbf{N}}(s(t))$$
- Unit binormal vector field: $$\mathbf{B}(t) = \bar{\mathbf{B}}(s(t))$$
- Curvature: $$\kappa(t) = \bar{\kappa}(s(t))$$
- Torsion: $$\tau(t) = \bar{\tau}(s(t))$$

## Frenet-Serret theorem

순서가 조금 파격적이지만, non-unit speed curve에 대한 Frenet-Serret theorem부터 이야기할 것이다.
이 순서로 이야기하는 편이 나머지 내용을 설명하는데 도움이 되기 때문이다.
Non-unit speed curve에 대한 Frenet-Serret theorem은 아래와 같다 (unit speed 버전에서 계수행렬에 $$v(t)$$가 곱해진 형태).

$$
\begin{align}
    \left[
        \begin{array}{c}
        \frac{d}{dt}\mathbf{T}(t) \\
        \frac{d}{dt}\mathbf{N}(t) \\
        \frac{d}{dt}\mathbf{B}(t) \\
        \end{array}
    \right]
    & =
    \left[
        \begin{array}{ccc}
        0               & \kappa(t) v(t)    & 0             \\
        -\kappa(t) v(t) & 0                 & \tau(t) v(t)  \\
        0               & -\tau(t) v(t)     & 0             \\
        \end{array}
    \right]
    \left[
        \begin{array}{c}
        \mathbf{T}(t) \\
        \mathbf{N}(t) \\
        \mathbf{B}(t) \\
        \end{array}
    \right]
    \\
    & \text{where }
    v(t) = ||\frac{d}{dt}\alpha(t)||
\end{align}
$$

첫 행의 관계식은 chain rule로부터 쉽게 유도될 수 있다.
(1)은 unit speed curve에 대한 Frenet-Serret theorem을 사용한 것이니 긴가민가 하다면 [이전 포스팅](/docs/robotics/07-frenet-apparatus-00)을 보고오셔라.

$$
\begin{align}
    & \mathbf{T}(t) = \bar{\mathbf{T}}(s(t)) \\
    \Rightarrow & \frac{d}{dt}\mathbf{T}(t) = \frac{d}{ds}\bar{\mathbf{T}}(s(t)) \frac{d}{dt}s(t) \\
    \Rightarrow & \frac{d}{dt}\mathbf{T}(t) = \frac{d}{ds}\bar{\mathbf{T}}(s(t)) v(t) \quad - \because \frac{d}{dt}s(t) = \frac{d}{dt} \int_{0}^{t} ||\frac{d}{du}\alpha(u)||\,du \\
    \Rightarrow & \frac{d}{dt}\mathbf{T}(t) = \bar{\kappa}(s(t)) \bar{\mathbf{N}}(s(t)) v(t) \quad - (1) \\
    \Rightarrow & \frac{d}{dt}\mathbf{T}(t) = \kappa(t) \mathbf{N}(t) v(t) \\
\end{align}
$$

두번째, 세번째 행의 관계식도 비슷하게 유도된다.
첫번째 행의 관계식 유도와 많이 유사하기 때문에 굳이 중복되는 과정을 풀어쓰지는 않았다.

$$
\begin{align}
    & \mathbf{N}(t) = \bar{\mathbf{N}}(s(t)) \\
    \Rightarrow & \frac{d}{dt}\mathbf{N}(t) = \frac{d}{ds}\bar{\mathbf{N}}(s(t)) \frac{d}{dt}s(t) \\
    \Rightarrow & \frac{d}{dt}\mathbf{B}(t) = (-\bar{\kappa}(s(t)) \bar{\mathbf{T}}(s(t)) + \bar{\tau}(s(t)) \bar{\mathbf{B}}(s(t)) ) v(t) \\
    \Rightarrow & \frac{d}{dt}\mathbf{B}(t) = (-\kappa(t) \mathbf{T}(t) + \tau(t) \mathbf{B}(t)) v(t) \\
\end{align}
$$

$$
\begin{align}
    & \mathbf{B}(t) = \bar{\mathbf{B}}(s(t)) \\
    \Rightarrow & \frac{d}{dt}\mathbf{B}(t) = \frac{d}{ds}\bar{\mathbf{B}}(s(t)) \frac{d}{dt}s(t) \\
    \Rightarrow & \frac{d}{dt}\mathbf{B}(t) = -\bar{\tau}(s(t)) \bar{\mathbf{N}}(s(t)) v(t) \\
    \Rightarrow & \frac{d}{dt}\mathbf{B}(t) = -\tau(t) \mathbf{N}(t) v(t) \\
\end{align}
$$

## Lemmas !

자꾸 변죽부터 울려대서 미안하지만, velocity ($$\frac{d}{dt}\alpha(t)$$) 와 acceleration ($$\frac{d^2}{dt^2}\alpha(t)$$) 에 대한 lemma 2개만 만들어 놓고가자.
뒤에 나올 수식이 원체 복잡스러워서 이러는 것이니 양해를 바란다.

### Lemma 1: velocity

$$
\frac{d}{dt} \alpha(t) = v(t) \mathbf{T}(t)
$$

이 lemma는 딱히 증명이 필요하지 않다.
우리는 $$v(t)$$를 $$v(t) = ||\frac{d}{dt}\alpha(t)||$$와 같이 정의했고, $$\mathbf{T}(t)$$는 접선방향의 단위벡터이다.
크기와 방향을 곱한 것 뿐이니 뭐 달리 증명할 것이 있겠는가?

### Lemma 2: acceleration

$$
\frac{d^2}{dt^2}\alpha(t) = \mathbf{T}(t) \frac{d}{dt}v(t) + \kappa(t) v(t)^2 \mathbf{N}(t)
$$

이 lemma는 lemma 1의 양변을 미분하여 증명할 수 있다.
(2)에서는 앞서 유도했던 Frenet-Serret theorem for non-unit curve가 사용되었음에 주의하자.

$$
\begin{align}
& \frac{d}{dt} \alpha(t) = v(t) \mathbf{T}(t) \\
\Rightarrow & \frac{d^2}{dt^2} \alpha(t) = \mathbf{T}(t) \frac{d}{dt}v(t) + v(t) \mathbf{T}^{\prime}(t) \\
\Rightarrow & \frac{d^2}{dt^2} \alpha(t) = \mathbf{T}(t) \frac{d}{dt}v(t) + v(t) \kappa(t) v(t) \mathbf{N}(t) - \quad (2) \\
\Rightarrow & \frac{d^2}{dt^2} \alpha(t) = \mathbf{T}(t) \frac{d}{dt}v(t) + v(t)^2 \kappa(t) \mathbf{N}(t) \\
\end{align}
$$

## Frenet-Serret apparatus for non-unit speed curve

이제 본격적으로 non-unit speed curve의 Frenet apparatus를 구해보도록하겠다.
공식이 조금 끔찍하지만 결론부터 이야기하면 Frenet apparatus 공식은 아래와 같다.

$$
\begin{align}
\underline{Thm 1:} \quad & \mathbf{T}(t) = \frac{\frac{d}{dt}\alpha(t)}{||\frac{d}{dt}\alpha(t)||} \\
\underline{Thm 2:} \quad & \mathbf{N}(t) = \mathbf{B}(t) \times \mathbf{T}(t) \\
\underline{Thm 3:} \quad & \mathbf{B}(t) = \frac
{
    \frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)
}
{
    ||\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)||
} \\
\underline{Thm 4:} \quad & \kappa(t) = \frac
{
    ||\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)||
}
{
    ||\frac{d}{dt}\alpha(t)||^3
} \\
\underline{Thm 5:} \quad & \tau(t) = \frac
{
    (\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)) \cdot \frac{d^3}{dt^3}\alpha(t)
}
{
    ||\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)||^2
} \\
\end{align}
$$

필자가 어떤 공식을보고 "참 X같이 생겼네" 싶은 것은 삼각함수 공식들 이후로 꽤나 오랜만인데, 그래도 하나하나 차분히 살펴보도록하자.
다행히도 Thm1은 lemma1 에서 바로 유도되기 때문에 별도로 증명할 필요는 없을 것 같다.
Thm2도, $$\mathbf{B}(t)$$와 $$\mathbf{T}(t)$$를 구했으면 당연한 것이니 따로 증명할 필요가 없을 것이다.
증명할 값어치가 있어보이는 것들 부터 증명해보자.
아래를 증명하는 과정에서 위에서 만든 lemma들이 적극 사용될 것이다.

### Proof of Thm3

우선 분자 분모에 들어가는 알맹이 $$\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)$$가 대체 무엇인지 살펴보자.

$$
\begin{align}
\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t) & = v(t)\mathbf{T}(t) \times (\mathbf{T}(t) \frac{d}{dt}v(t) + \kappa(t) v(t)^2 \mathbf{N}(t)) - \quad \text{by lemma 1, 2} \\
& = \kappa(t) v(t)^3 \mathbf{T}(t) \times \mathbf{N}(t) \\
& = \kappa(t) v(t)^3 \mathbf{B}(t) \\
\end{align}
$$

이 알맹이를 Thm3에 대입하면 곧바로 증명이 되는 것을 알 수 있다.

### Proof of Thm4

Thm3을 증명하는 과정에서 우리는 
$$ ||\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)|| = \kappa(t) v(t)^3 $$ 을 얻었다.
그리고, lemma 1으로부터 $$||\frac{d}{dt} \alpha(t)|| = v(t)$$ 임을 알고있다.
역시 그대로 대임만해주면 증명이 된다.

### Proof of Thm5

Thm5의 증명을 간단하게 (무식하게 식을 풀어쓰지 않고) 하기 위해서는 조금 짱구를 굴려야한다.
우선 분자를 살펴보자.
Thm3를 증명하면서 얻은 알맹이를 사용하면 아래와 같이 식을 다시 쓸 수 있다.

$$
(\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)) \cdot \frac{d^3}{dt^3}\alpha(t) = \kappa(t) v(t)^3 \mathbf{B}(t) \cdot \frac{d^3}{dt^3}\alpha(t)
$$

식의 마지막 부분인 $$\mathbf{B}(t) \cdot \frac{d^3}{dt^3}\alpha(t)$$을 잘 생각해보면 결국 $$\frac{d^3}{dt^3}\alpha(t)$$를 $$\mathbf{B}(t)$$에 사영 (i.e., projection) 하는 것임을 알 수 있다.
따라서, 진짜 우직하게 $$\frac{d^3}{dt^3}\alpha(t)$$를 다 구할 필요 없이 계산과정에서 $$\mathbf{B}(t)$$ 성분만 남기고 $$\mathbf{T}(t)$$, $$\mathbf{B}(t)$$ 성분들은 무시해주면 된다.
이제 lemma 2의 양변을 미분하여 $$\frac{d^3}{dt^3}\alpha(t)$$를 스마트하게 구해보도록하자.

$$
\begin{align}
\frac{d^3}{dt^3}\alpha(t) & = \frac{d}{dt} (\mathbf{T}(t) \frac{d}{dt}v(t) + \kappa(t) v(t)^2 \mathbf{N}(t)) \\
& = \frac{d}{dt} \mathbf{T}(t) + \mathbf{T}(t) \frac{d^2}{dt^2} v(t) + \frac{d}{dt}(\kappa(t) v(t)^2) \mathbf{N}(t) + \kappa(t) v(t)^2 \frac{d}{dt} \mathbf{N}(t) \\
& = \kappa(t) v(t) \mathbf{N}(t) + \mathbf{T}(t) \frac{d^2}{dt^2} v(t) + \frac{d}{dt}(\kappa(t) v(t)^2) \mathbf{N}(t) + \kappa(t) v(t)^2 \frac{d}{dt} \mathbf{N}(t) \\
& = \kappa(t) v(t) \mathbf{N}(t) + \mathbf{T}(t) \frac{d^2}{dt^2} v(t) + \frac{d}{dt}(\kappa(t) v(t)^2) \mathbf{N}(t) + \kappa(t) v(t)^2 (-\kappa(t) v(t) \mathbf{T}(t) + \tau(t) v(t) \mathbf{B}(t)) \\
\end{align}
$$

위의 식에서 $$\mathbf{B}(t)$$ 성분만 추려내주면 $$\kappa(t)\tau(t)v(t)^3\mathbf{B}(t)$$가 된다.
따라서, 아래를 얻을 수 있다.

$$
\begin{align}
(\frac{d}{dt}\alpha(t) \times \frac{d^2}{dt^2}\alpha(t)) \cdot \frac{d^3}{dt^3}\alpha(t) & = \kappa(t) v(t)^3 \mathbf{B}(t) \cdot \frac{d^3}{dt^3}\alpha(t) \\
& = \kappa(t)^2 \tau(t) v(t)^6
\end{align}
$$

Thm5의 분모는 Thm3의 증명과정에서 이미 구하였고, 이제 얻어진 식들을 대입만 해주면 증명이 완료됨을 알 수 있다.

[^1]: 문헌에 따라 arbitrary speed curve라고 부르는 경우도 있는 것 같다.
[^2]: 여전히 curve가 regular라는 조건은 있는 것을 잊지말자.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
