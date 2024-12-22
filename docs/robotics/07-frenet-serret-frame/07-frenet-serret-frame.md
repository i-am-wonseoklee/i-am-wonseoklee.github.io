---
title: Frenet Serret Frame
layout: default
parent: Robotics
permalink: /docs/robotics/07-frenet-serret-frame
---

# Frenet Serret Frame

**Keywords:** `Frenet Serret Frame`{: .label }, `TNB Frame`{: .label }, `Frenet Serret Theorem`{: .label }

It's been a long time!
필자는 최근에 이직을 하게되었다.
귀엽게도 아직 수습기간이라 재택 없이 출퇴근을 해야하는데, 출퇴근 중에 버스에서 버리는 시간을 어떻게 슬기롭게 사용할까 고민하다가 [이 유튜브 강의](https://www.youtube.com/watch?v=uVlADD2xWSA&list=PL-M-dt8G0wq3SjwSs_ca6Qd0_lFXwvFr4)를 발견했다.
하고 있는 업무에 미분기하학에서 다루는 내용이 은근히 자주 등장하는데, 미분기하학을 제대로 배워본 적이 없는 나로서는 반가운 소식이었다.
강의가 꽤나 고퀄이라 업로더에게 감사할 따름이다.
다뤄볼 수 있는 여러 내용이 있을테지만, 이 포스팅에서는 Frenet Serret frame (보통 TNB frame이라 불리는) 에 대해서 알아보도록 하겠다.

## Intuitive understanding of TNB frame

늘 강조하지만 뭔가를 새로 배울 때는 엄밀한 정의고 나발이고 일단 배우려는 대상을 직관적으로 이해하는 것이 우선이다.
TNB 프레임은 아래의 움짤에 매우 직관적으로 설명되어 있다.
스크롤을 내려 설명을 더 읽기 전에 T, N, B 벡터 각각이 무엇을 의미하는지 한번 스스로 생각해보시라.

![](/docs/robotics/07-frenet-serret-frame/images/fig01.gif)

위의 그림에서 발견할 수 있는 사실은 아래와 같다.

- TNB frame은 서로 직교하는 $$\mathbf{T}$$, $$\mathbf{N}$$, 그리고 $$\mathbf{B}$$ 벡터로 이루어진다.
- TNB frame은 곡선 $$\alpha$$ 위의 한 점 $$\alpha(s)$$에서 $$\mathbf{T}(s)$$, $$\mathbf{N}(s)$$, $$\mathbf{B}(s)$$와 같이 정의된다.
- 직관적으로 이해해보면,
  - $$\mathbf{T}(s)$$는 $$\alpha(s)$$에서 접선의 방향을 가리킨다.
  - $$\mathbf{N}(s)$$는 $$\alpha(s)$$에서 회전 구심력이 작용하는 방향을 가리킨다.
  - $$\mathbf{B}(s)$$는 $$\mathbf{T}(s)$$와 $$\mathbf{B}(s)$$의 외적 벡터 방향을 가리킨다.

직관적인 의미만 놓고보면 위에서 설명한 것이 전부인데, 이제 각각에 대해서 조금 더 엄밀하게 살펴보도록 하자.

{: .note }
> 이후의 기술에서 별 다른 언급이 없는 경우 주어진 곡선 $$\alpha(s)$$는 단위속력곡선이다.
> 그냥 편하게 arc-length reparameterized curve라고 생각하면 무리가 없을 것이다.

## Unit tangent vector field (T)

우선, $$\mathbf{T}(s)$$ 부터 살펴보도록하자.
Unit tangent vector라는 이름이 보이듯 $$\mathbf{T}(s)$$는 곡선 $$\alpha(s)$$의 접선방향을 향하는 단위 벡터이다.
우리가 가정하고 있는 곡선 $$\alpha(s)$$는 단위속력곡선이므로 $$||\alpha(s)|| = 1$$이다.
따라서, $$\mathbf{T}(s)$$ 는 간단하게 아래와 같이 표현할 수 있다.

$$
\mathbf{T}(s) = \alpha^{\prime}(s)
$$

## Curvature

Unit tangent vector를 이야기할 때 하나 더 빠질 수 없는 것이 있다.
바로 곡선의 curvature $$\kappa(s)$$인데, 이것은 아래와 같이 정의된다.

$$
\kappa(s) = ||\mathbf{T}^{\prime}(s)||
$$

위에서 밝힌 curvature는 "정의"이기 때문에 그냥 받아들이는 것이 상책이겠으나, 그래도 의미하는 것이 무엇일지 조금은 생각해보도록 하자.
우선, $$\mathbf{T}^{\prime}(s)$$라는 벡터는 과연 무엇일지 생각해보자.
$$\mathbf{T}^{\prime}(s)$$는 $$\mathbf{T}$$에 직교하는 방향을 가리키는 벡터이고, $$||\mathbf{T}(s)|| = 1$$이라는 사실로부터 아래와 같이 매우 쉽게 유도될 수 있다.

$$
\begin{align*}
            & ||\mathbf{T}(s)|| = 1 \\
\Rightarrow & \mathbf{T}(s) \cdot \mathbf{T}(s) = 1 \\
\Rightarrow & \mathbf{T}^{\prime}(s) \cdot \mathbf{T}(s) + \mathbf{T}(s) \cdot \mathbf{T}^{\prime}(s) = 0 \quad - \text{양변 미분함} \\
\Rightarrow & \mathbf{T}^{\prime}(s) \cdot \mathbf{T}(s) = 0 \\
\Rightarrow & \mathbf{T}(s) \perp \mathbf{T}^{\prime}(s) \\
\end{align*}
$$

{: .highlight }
> 너무 당연한 이야기라서 지면을 할애하기가 조금은 부끄럽다.
> 하지만, 뒤에서 별다른 설명 없이 인용할 것이므로 밝혀둔다.
> 크기가 늘 상수인 벡터 $$\mathbf{X}(s)$$는 위와 같은 과정을 따라 그 미분 벡터 $$\mathbf{X}^{\prime}(s)$$와 늘 수직이다.

그래서, 결국 곡선의 curvature $$\kappa(s)$$란 $$\mathbf{T}(s)$$에 직교하는 방향으로 향하는 벡터의 크기를 의미한다.
직관적으로 구심력의 크기 정도로 이해해두면 편하지 않겠는가?
Curvature의 크기를 구심력의 크기로 이해하는 직관이 마음에 들지 않거나 조금 더 강력한 직관이 필요하다면 curve curvature에 대한 [이 포스팅](/docs/robotics/04-curve-curvature/)을 한번 참고해보셔라.

## Unit princicpal normal vector field (N)

$$\mathbf{N}(s)$$는 앞선 챕터에서 curvature를 배우고 왔다면 거저 먹는 개념인데, 단지 구심력 방향의 벡터를 normalize한 것으로 아래와 같이 정의된다.

$$
\mathbf{N}(s) = \frac{\mathbf{T}^{\prime}(s)}{||\mathbf{T}^{\prime}(s)||} = \frac{\mathbf{T}^{\prime}(s)}{\kappa(s)}
$$

(앞선 내용과 중복되는 설명이겠으나) 기하학적으로 $$\mathbf{N}(s)$$는 curve $$\alpha(s)$$의 접션 벡터 $$\mathbf{T}(s)$$에 수직인 단위벡터로 이해하면 된다.

## Unit binormal vector field (B)

$$\mathbf{T}(s)$$, $$\mathbf{N}(s)$$을 알고 있으면 $$\mathbf{B}(s)$$도 거저로 이해하는 것인데, 아래와 같이 정의된다.

$$
\mathbf{B}(s) = \mathbf{T}(s) \times \mathbf{N}(s)
$$

기하학적으로는 $$\mathbf{T}(s)$$, $$\mathbf{N}(s)$$이 이루는 평면의 법선 백터로 이해하면 된다.

## Torsion

TNB frame, curvature 등을 이야기하면 함께 빠지지 않고 등장하는 것이 바로 torsion (열률) $$\tau$$인데 아래와 같이 정의된다.

$$
\tau(s) = - \mathbf{B}^{\prime}(s) \cdot \mathbf{N}(s)
$$

정의는 무척이나 간단하지만 이것의 기하학적 의미를 고찰해보는 것은 은근히 어렵다.
그래도 차근차근 살펴보도록하자.
우선, $$\mathbf{B}^{\prime}(s)$$이 의미하는 것이 무엇인지 살펴보자.

$$
\begin{align*}
& \mathbf{B}(s) = \mathbf{T}(s) \times \mathbf{N}(s) \\
\Rightarrow \mathbf{B}(s)^{\prime} & = \mathbf{T}^{\prime}(s) \times \mathbf{N}(s) + \mathbf{T}(s) \times \mathbf{N}^{\prime}(s) \\
& = \kappa(s) \mathbf{N}(s) \times \mathbf{N}(s) + \mathbf{T}(s) \times \mathbf{N}^{\prime}(s) \\
& = \mathbf{T}(s) \times \mathbf{N}^{\prime}(s) \\
& = \mathbf{T}(s) \times (u(s) \mathbf{T}(s) + v(s) \mathbf{B}(s)), \, u(s), v(s) \in \mathbb{R} \quad - (1) \\
& = v(s) \mathbf{T}(s) \times \mathbf{B}(s) \\
& = - v(s) \mathbf{N}(s) \quad - (2) \\
\end{align*}
$$

(1)에서는 $$\mathbf{N}(s) \perp \mathbf{N}^{\prime}(s)$$ 이기 떄문에 $$\mathbf{N}^{\prime}(s)$$를 $$\mathbf{T}(s)$$와 $$\mathbf{B}(s)$$를 기저로 사용해서 표현할 수 있는 성질을 사용한 것이다.
(2)에서도 비슷한 성질이 사용되었는데 (사실 크게 비슷하지는 않은 것 같다...), 하여간 이 그림을 그려놓고 생각하면 편하다.

![](/docs/robotics/07-frenet-serret-frame/images/fig02.png)

이제 $$\tau(s)$$의 정의로 마저 돌아와서 식을 정리하면 아래를 얻을 수 있다.

$$
\begin{align*}
\tau(s) & = - \mathbf{B}^{\prime}(s) \cdot \mathbf{N}(s) \\
& = v(s) \mathbf{N}(s) \cdot \mathbf{N}(s) \\
& = v(s) \\
\end{align*}
$$

뭐 결국 식을 지지고 볶았더니 $$\tau(s) = v(s)$$가 나왔다는 이야기인데, $$v(s)$$가 의미하는 것이 무엇이었는가?
(1)을 살펴보면 우리는 $$\mathbf{B}(s)$$를 법 벡터로 하는 평면 (i.e., TN 평면) 을 튀어나오려는 만큼의 양을 scalar $$v(s)$$로 표시했다.
그래서 결국, 곡선의 torsion이란 곡선이 TN 평면을 튀어 나오려는 양 정도로 이해해두면 편하다.

## Frenet Serret theorem

앞에서 정의한 $$\mathbf{T}(s)$$, $$\mathbf{T}(s)$$, $$\mathbf{T}(s)$$, $$\kappa(s)$$, 그리고 $$\mathbf{\tau}(s)$$ 사이에는 아래와 같이 아름다운 관계가 성립한다.

$$
\left[
\begin{array}{c}
\mathbf{T}^{\prime}(s) \\
\mathbf{N}^{\prime}(s) \\
\mathbf{B}^{\prime}(s) \\
\end{array}
\right]
=
\left[
\begin{array}{ccc}
0          & \kappa(s) & 0       \\
-\kappa(s) & 0         & \tau(s) \\
0          & -\tau(s)  & 0       \\
\end{array}
\right]
\left[
\begin{array}{c}
\mathbf{T}(s) \\
\mathbf{N}(s) \\
\mathbf{B}(s) \\
\end{array}
\right]
$$

첫 행의 관계식은 그냥 정의를 대입하면 끝나는 것이니 따로 적지 않도록하겠다. 마지막 행의 관계식 $$\mathbf{B}^{\prime}(s) = -\tau(s) \mathbf{N}(s)$$부터 증명해보도록하자.

$$
\begin{align*}
\mathbf{B}^{\prime}(s) & = 
        (\mathbf{B}^{\prime}(s) \cdot \mathbf{T}(s)) \mathbf{T}(s) +
        (\mathbf{B}^{\prime}(s) \cdot \mathbf{N}(s)) \mathbf{N}(s) +
        (\mathbf{B}^{\prime}(s) \cdot \mathbf{B}(s)) \mathbf{B}(s) \quad - (1)  \\
& = 0 \mathbf{T}(s) - \tau(s) \mathbf{N}(s) + 0 \mathbf{B}(s) \quad - (2)       \\
\end{align*}
$$

(1)에서는 TNB가 frame임을 이용해서 $$\mathbf{B}^{\prime}(s)$$을 각 기저를 사용해서 표현한 것이다.
(2)에서는 $$\mathbf{B}^{\prime}(s) \perp \mathbf{T}(s)$$, $$\mathbf{B}^{\prime}(s) \perp \mathbf{B}(s)$$ 임이 사용되었다.
증명은 어렵지 않으니 (사실 위에 비슷한 증명을 많이했음) 스스로 해보기를 바란다.

두번째 행의 관계식도 역시 비슷하게 증명할 수 있는데, 그 증명은 아래와 같다.

$$
\begin{align*}
\mathbf{N}^{\prime}(s) & = 
        (\mathbf{N}^{\prime}(s) \cdot \mathbf{T}(s)) \mathbf{T}(s) +
        (\mathbf{N}^{\prime}(s) \cdot \mathbf{N}(s)) \mathbf{N}(s) +
        (\mathbf{N}^{\prime}(s) \cdot \mathbf{B}(s)) \mathbf{B}(s) \quad - (1) \\
& = -\kappa(s) \mathbf{T}(s) + 0 \mathbf{N}(s) + \tau(s) \mathbf{B}(s) \quad - (2) \\
\end{align*}
$$

(2)에서 $$\mathbf{N}^{\prime}(s) \cdot \mathbf{T}(s) = -\kappa(s)$$가 되는 부분이 조금 어려울 수 있는데, 이것의 증명은 아래에 적어둔다.

$$
\begin{align*}
\mathbf{N}(s) & \perp \mathbf{T}(s) \\
& \Rightarrow \mathbf{N}(s) \cdot \mathbf{T}(s) = 0 \\
& \Rightarrow \mathbf{N}^{\prime}(s) \cdot \mathbf{T}(s) + \mathbf{N}(s) \cdot \mathbf{T}^{\prime}(s) = 0 \\
& \Rightarrow \mathbf{N}^{\prime}(s) \cdot \mathbf{T}(s) = - \mathbf{N}(s) \cdot \kappa(s) \mathbf{N}(s) \\
& \Rightarrow \mathbf{N}^{\prime}(s) \cdot \mathbf{T}(s) = - \kappa(s) \\
\end{align*}
$$

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
