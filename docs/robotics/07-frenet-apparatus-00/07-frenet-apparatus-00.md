---
title: Frenet Apparatus I
layout: default
parent: Robotics
permalink: /docs/robotics/07-frenet-apparatus-00
---

# Frenet Apparatus I

**Keywords:** `Frenet Serret Frame`{: .label }, `TNB Frame`{: .label }, `Frenet Serret Theorem`{: .label }, `Frenet Apparatus`{: .label }

It's been a long time!
TMI지만 필자는 최근에 이직을 하게되었다.
(귀엽게도) 아직 수습기간이라 재택근무가 불가능하고 출퇴근을 해야하는데, 출퇴근 중에 버스에서 버리는 시간을 어떻게 슬기롭게 사용할까 고민하다가 [이 유튜브 강의](https://www.youtube.com/watch?v=uVlADD2xWSA&list=PL-M-dt8G0wq3SjwSs_ca6Qd0_lFXwvFr4)를 발견했다.
업무를 하다보면 미분기하학에서 다루는 내용이 은근히 자주 등장하는데, 미분기하학을 제대로 배워본 적이 없는 나로서는 반가운 기회였다.

강의를 통해 습득한 내용들 중 이 포스팅에서는 Frenet apparatus에 대해서 알아보도록 하겠다.
국문으로는 "프레네 장치", "프레네 기구" 등으로 불리는 것 같다.
하지만, 필자에게는 아무래도 저 번역이 영 어색했고, "TNB frame", 혹은 그냥 "Frenet apparatus"라고 부르는 편이 더 자연스러웠다.

용어의 느낌에 대한 필자의 감상은 이쯤하고, Frenet apparatus가 무엇인지 알아보도록하자.
Frenet apparatus는 주어진 curve를 이해하는데 도움이되는 5개의 속성(?)들을 일컫는다.
달리 말하면, 이 5개의 속성을 알고 있으면 주어진 curve에 대해 어느정도 설명할 수 있다는 이야기이다.
이 5개의 속성은 아래와 같다.
각각 대해 상세히 후술할 것이므로 여기서는 간략히 이름만 소개하고 넘어가도록 하겠다.

1. Unit tangent vector field ($$\mathbf{T}$$)
2. Unit principal normal vector field ($$\mathbf{N}$$)
3. Unit binormal vector field ($$\mathbf{B}$$)
4. Curvature ($$\kappa$$)
5. Torsion ($$\tau$$)

## Intuitive understanding of TNB

스스로에게 늘 강조하지만 뭔가를 새로 배울 때는 엄밀한 정의고 ~~나발이고~~ 일단 배우려는 대상을 직관적으로 이해하는 것이 우선이다.
Frenet apparatus 중 $$\mathbf{T}$$, $$\mathbf{N}$$, $$\mathbf{B}$$는 아래의 움짤 (움짤은 웹에서 퍼온 것임) 에 매우 직관적으로 설명되어 있다.
스크롤을 내려 설명을 더 읽기 전에 각각이 무엇을 의미하는지 한번 스스로 생각해보시라.

![](/docs/robotics/07-frenet-apparatus-00/images/fig01.gif)

위의 그림에서 발견할 수 있는 사실은 아래와 같다.

- $$\mathbf{T}$$, $$\mathbf{N}$$, 그리고 $$\mathbf{B}$$는 curve 위의 특정 위치에서 정의되는 서로 직교하는 단위 벡터들이다.
- Curve 상의 각 위치에서 매번 다르게 정의되므로 curve $$\alpha(s)$$에 대해서 $$\mathbf{T}(s)$$, $$\mathbf{N}(s)$$, $$\mathbf{B}(s)$$와 vector field로 표기하는 것이 보다 정확할 것이다.
- $$\mathbf{T}(s)$$는 $$\alpha(s)$$에서 접선의 방향을 가리킨다.
- ~~솔직히 움짤에 잘 표현된 것 같지는 않지만~~, $$\mathbf{N}(s)$$는 $$\alpha(s)$$에서 (대략) 회전 구심력이 작용하는 방향을 가리킨다.
  - 즉, curve가 왼쪽으로 휘고 있으면 $$\mathbf{T}(s)$$에 수직이면서 $$\alpha(s)$$에서 왼쪽을 향하는 벡터가 $$\mathbf{N}(s)$$이 될 것이다.
  - 반대로, curve가 오른쪽으로 휘고 있으면 $$\mathbf{T}(s)$$에 수직이면서 $$\alpha(s)$$에서 오른쪽을 향하는 벡터가 $$\mathbf{N}(s)$$이 될 것이다.
- $$\mathbf{B}(s)$$는 $$\mathbf{T}(s)$$와 $$\mathbf{B}(s)$$에 모두 수직인 방향을 가리키는데, $$\mathbf{T}(s)$$와 $$\mathbf{B}(s)$$의 외적 방향이라고 생각하면 편하다.

이제 각각에 대해서 조금 더 엄밀하게 살펴보고, 움짤에서 누락된 curvature와 torsion의 이야기도 마저해보도록 하자.

{: .note }
> 이후의 기술에서 별 다른 언급이 없는 경우 주어진 curve $$\alpha(s)$$는 unit speed curve (i.e., 단위속력곡선) 이다.
> 그냥 편하게 [arc-length reparameterized curve](/docs/robotics/06-arc-length-reparameterization)라고 생각하면 무리가 없을 것이다.
> Non-unit speed curve (i.e., 임의속력곡선) 에 대한 Frenet apparatus 유도는 이 포스팅에서 다룰 내용보다 조금 더 복잡한데, 이 내용이 궁금하다면 [Frenet Appratus II](/docs/robotics/09-frenet-apparatus-01) 포스팅을 참고하시라.
> 다만, unit speed curve에 대한 Frenet apparatus 유도 과정을 알고 있어야 이해가 수월할 것임을 미리 언급해둔다.

## Unit tangent vector field (T)

우선, $$\mathbf{T}(s)$$ 부터 살펴보자.
Unit tangent vector라는 이름이 보이듯 $$\mathbf{T}(s)$$는 $$\alpha(s)$$에서의 접선방향을 향하는 단위 벡터이다.
우리가 가정하고 있는 curve는 unit speed curve이므로 $$||\alpha(s)|| = 1$$이다.
따라서, $$\mathbf{T}(s)$$ 는 간단하게 아래와 같이 표현할 수 있다.

$$
\mathbf{T}(s) = \alpha^{\prime}(s)
$$

Unit tangent vector field는 사실 크게 설명할 것이 없고, 상술한 정의가 전부이다.
다만, 이것이 다른 내용들을 설명하는데에 building block으로 사용되니 유념해두도록 하자.

## Curvature

일전에 [이 포스팅](/docs/robotics/04-curve-curvature/)에서 curve의 curvature에 대해 이야기한적이 있다.
여기서 말할 curvature도 그때 이야기했던 그 curvature가 **맞다.**
그때는 중학교 수준의 수학으로 공식을 이끌어내기 위해 조금은 어렵게 설명하였지만, 이제는 조금 더 우아하게 이끌어낼 수 있다.
$$\alpha(s)$$에서의 curvature $$\kappa(s)$$는 아래와 같이 구할 수 있다.

$$
\kappa(s) = ||\mathbf{T}^{\prime}(s)||
$$

"중학교 삼각형 공식으로 curvature 한번 구해보겠다고 그 뻘짓을 했는데, 이렇게 쉽게된다고?"라고 생각하는 독자들이 있으리라.
그러한 독자들을 위해서 조금의 설명을 보충해둔다.

우선, $$\mathbf{T}^{\prime}(s)$$라는 벡터는 과연 무엇일지 생각해보자.
$$\mathbf{T}^{\prime}(s)$$는 $$\mathbf{T}$$에 직교하는 방향을 가리키는 벡터이다.
이것은 $$||\mathbf{T}(s)|| = 1$$이라는 정의로부터 아래와 같이 유도될 수 있다.

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
> `Tip`: 크기가 상수인 벡터 $$\mathbf{X}(s)$$는 위와 같은 과정을 따라 그 미분 벡터 $$\mathbf{X}^{\prime}(s)$$와 늘 수직이다.

결국 곡선의 curvature $$\kappa(s)$$란 $$\mathbf{T}(s)$$에 직교하는 방향으로 향하는 벡터의 크기를 의미한다.
직관적으로 구심력의 크기 정도로 이해해두면 편하지 않겠는가?

## Unit princicpal normal vector field (N)

$$\mathbf{N}(s)$$는 curvature를 이해했다면 거저 먹는 개념인데, 단지 구심력 방향의 벡터 ($$\mathbf{T}^{\prime}(s)$$) 를 normalize한 것으로 아래와 같이 정의된다.

$$
\mathbf{N}(s) = \frac{\mathbf{T}^{\prime}(s)}{||\mathbf{T}^{\prime}(s)||} = \frac{\mathbf{T}^{\prime}(s)}{\kappa(s)}
$$

## Unit binormal vector field (B)

$$\mathbf{B}(s)$$도 $$\mathbf{T}(s)$$, $$\mathbf{N}(s)$$을 알고있으면 거저 이해하는 것인데, 아래와 같이 정의된다.
기하학적으로는 $$\mathbf{T}(s)$$, $$\mathbf{N}(s)$$이 이루는 평면의 법선 백터로 이해하면 된다.

$$
\mathbf{B}(s) = \mathbf{T}(s) \times \mathbf{N}(s)
$$

## Torsion

Curve의 torsion (열율) $$\tau(s)$$는 그 기하학적 의미를 바로 떠올리기에는 조금 어려움이 있다.
그러니, 우선 정의를 밝히고, 그 의미를 살펴보도록 하겠다.

$$
\tau(s) = - \mathbf{B}^{\prime}(s) \cdot \mathbf{N}(s)
$$

이제 위와 같이 정의되는 $$\tau(s)$$ 기하학적 의미를 고찰해볼 것이다.
우선, 식의 왼편에 등장하는 $$\mathbf{B}^{\prime}(s)$$부터 조금은 다른 형태로 기술해보도록 하겠다.

$$
\begin{align*}
& \mathbf{B}(s) = \mathbf{T}(s) \times \mathbf{N}(s) \\
\Rightarrow \mathbf{B}^{\prime}(s) & = \mathbf{T}^{\prime}(s) \times \mathbf{N}(s) + \mathbf{T}(s) \times \mathbf{N}^{\prime}(s) \\
& = \kappa(s) \mathbf{N}(s) \times \mathbf{N}(s) + \mathbf{T}(s) \times \mathbf{N}^{\prime}(s) \\
& = \mathbf{T}(s) \times \mathbf{N}^{\prime}(s) \\
& = \mathbf{T}(s) \times (u(s) \mathbf{T}(s) + v(s) \mathbf{B}(s)), \, u(s), v(s) \in \mathbb{R} \quad - (1) \\
& = v(s) \mathbf{T}(s) \times \mathbf{B}(s) \\
& = - v(s) \mathbf{N}(s) \quad - (2) \\
\end{align*}
$$

(1)의 과정이 조금 혼란스러울 수 있을텐데, 앞서 크기가 상수인 벡터의 미분 벡터는 늘 원래의 벡터와 수직이었다는 사실을 떠올려보자.
$$\mathbf{N}^{\prime}(s)$$는 $$\mathbf{N}(s)$$와 수직일 것이고, 따라서 $$\mathbf{T}(s)$$와 $$\mathbf{B}(s)$$를 기저로 사용하여 기술될 수 있다는 성질을 사용한 것이다 (머리 속에 아래의 그림을 가지고 있으면 이해가 수월하다),
비슷하게 (2)에서도 $$\mathbf{T}(s)$$와 $$\mathbf{B}(s)$$의 외적은 곧 $$-\mathbf{N}(s)$$이 되는 것이 사용되었다 (늘 오른손 법칙을 잊지 말자).

![](/docs/robotics/07-frenet-apparatus-00/images/fig02.png)

이제 $$\tau(s)$$의 정의로 마저 돌아와서 식을 정리하면 아래를 얻을 수 있다.
뭐 결국 식을 지지고 볶았더니 $$\tau(s) = v(s)$$가 나왔다는 이야기인데, $$v(s)$$가 의미하는 것이 무엇이었는가?
(1)을 살펴보면 우리는 $$\mathbf{B}(s)$$를 법 벡터로 하는 평면 (i.e., TN 평면) 을 튀어나오려는 만큼의 양을 scalar $$v(s)$$로 표시했다.
그래서 결국, curve의 torsion이란 curve가 TN 평면을 튀어 나오려는 양으로 이해할 수 있다.

$$
\begin{align*}
\tau(s) & = - \mathbf{B}^{\prime}(s) \cdot \mathbf{N}(s) \\
& = v(s) \mathbf{N}(s) \cdot \mathbf{N}(s) \\
& = v(s) \\
\end{align*}
$$

## Frenet-Serret theorem

앞에서 정의한 $$\mathbf{T}(s)$$, $$\mathbf{T}(s)$$, $$\mathbf{T}(s)$$, $$\kappa(s)$$, 그리고 $$\mathbf{\tau}(s)$$ 사이에는 아래와 같이 아름다운 관계가 성립한다.
그리고, 사실 이러한 관계가 있기 때문에 위 5개를 묶어서 Frenet apparatus라고 칭하는 것이기도 하다.

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

첫 행의 관계식은 $$\mathbf{N}(s)$$를 설명하면서 이미 한 이야기이니 따로 적지 않겠가.
두, 세번째 관계식은 설명이 필요한데, 편의상 세번째 관계식 $$\mathbf{B}^{\prime}(s) = -\tau(s) \mathbf{N}(s)$$부터 증명해보도록하자.

$$
\begin{align*}
\mathbf{B}^{\prime}(s) & = 
        (\mathbf{B}^{\prime}(s) \cdot \mathbf{T}(s)) \mathbf{T}(s) +
        (\mathbf{B}^{\prime}(s) \cdot \mathbf{N}(s)) \mathbf{N}(s) +
        (\mathbf{B}^{\prime}(s) \cdot \mathbf{B}(s)) \mathbf{B}(s) \quad - (3)  \\
& = 0 \mathbf{T}(s) - \tau(s) \mathbf{N}(s) + 0 \mathbf{B}(s) \quad - (4)       \\
\end{align*}
$$

(3)에서는 TNB가 frame임을 이용해서 $$\mathbf{B}^{\prime}(s)$$을 각 기저를 사용해서 표현한 것이다 ($$\mathbf{B}^{\prime}(s)$$을 각 축에 사영했음).
(4)에서는 $$\mathbf{B}^{\prime}(s) \perp \mathbf{T}(s)$$, $$\mathbf{B}^{\prime}(s) \perp \mathbf{B}(s)$$ 임이 사용되었다.
언급한 두 수직관계에 대한 증명은 위에서 언급한 내용들을 잘 살펴보면 발견할 수 있으리라.

두번째 행의 관계식도 역시 비슷하게 증명할 수 있는데, 그 증명은 아래와 같다.

$$
\begin{align*}
\mathbf{N}^{\prime}(s) & = 
        (\mathbf{N}^{\prime}(s) \cdot \mathbf{T}(s)) \mathbf{T}(s) +
        (\mathbf{N}^{\prime}(s) \cdot \mathbf{N}(s)) \mathbf{N}(s) +
        (\mathbf{N}^{\prime}(s) \cdot \mathbf{B}(s)) \mathbf{B}(s) \\
& = -\kappa(s) \mathbf{T}(s) + 0 \mathbf{N}(s) + \tau(s) \mathbf{B}(s) \quad - (5) \\
\end{align*}
$$

(5)에서 $$\mathbf{N}^{\prime}(s) \cdot \mathbf{T}(s) = -\kappa(s)$$가 되는 부분이 조금 어려울 수 있는데, 이것의 증명은 아래에 적어둔다.

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
