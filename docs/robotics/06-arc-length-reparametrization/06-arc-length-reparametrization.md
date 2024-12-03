---
title: Arc Length Reparametrization
layout: default
parent: Robotics
permalink: /docs/robotics/06-arc-length-reparametrization
---

# Arc Length Reparametrization

**Keywords:** `Arc Length Reparametrization`{: .label }, `호장재매개화`{: .label }

최근에 differential geometry에서 다루는 내용 중 일부를 살펴볼 일이 있었다.
다른 수식들은 이해하는데 큰 문제가 없었지만 의외로 curve reparametrization 수식을 이해하는데 애를 먹었다.
Skimming 중에는 너무 당연해보여서 크게 신경쓰지 않았는데 역시 Life is not easy.
반성하는 마음으로 정리해둔다.

## Reparametrization of curve

Arc length reparametrization은 curve reparametrization만 이해하면 거져 이해할 수 있는 개념이다.
아래 그림과 같이 임의의 regular curve가 주어져있다고 생각해보자 — 별 다른 설명이 없다면 이 포스팅에서 curve는 항상 regular curve를 의미한다.
너무나도 당연한 내용들이지만 그래도 그림에 보이는 것들을 차근차근 적어보면:

1. 주어진 curve $$\alpha$$는 $$t \in [a, b]$$에서 정의된 $$t$$의 함수이다. 즉, $$t$$로 **parametrization된 curve이다.**
2. $$t$$가 $$a$$부터 $$b$$까지 등속도로 이동할 때 $$\alpha(t)$$는 아래와 같이 움직였을 것이다.
   1. 주어진 curve는 regular curve였으므로 $$\alpha^{\prime}(t) \neq 0$$이다. 따라서, $$\alpha(a)$$에서 $$\alpha(b)$$를 향해 (trace를 따라) 움직였거나, 그 반대 방향으로 움직였을 것이다. 즉, 중간에 진행 방향을 바꾸지 않았을 것이다.
   2. 주어진 curve의 trace는 아래 그림과 같이 롤러코스터 모양이었을 것이고, trace의 양끝점이 (순서는 모르지만) $$\alpha(a)$$, $$\alpha(b)$$였을 것이다.
   3. 사실 2.a, 2.b 정도가 $$t$$의 변화에 따라 $$\alpha(t)$$가 어떻게 움직였는지에 대해 파악할 수 있는 전부이다. $$\alpha(t)$$가 어떻게 정의되었는지를 모르는 상태에서는 당신은 $$\alpha(t)$$의 움직임에 대해 아무런 가정을 할 수 없다.

![fig01](/docs/robotics/06-arc-length-reparametrization/images/fig01.png)

이제 아래의 그림을 다시 살펴보자.
$$\alpha(t)$$가 모종의 방법으로 잘 정의되어서 롤러코스터의 고리 부분을 지날 때 속력이 더 높았다고 해보자.
달리 표현하면, $$t$$가 $$a$$부터 $$b$$까지 등속도로 이동할 때 $$\alpha(t)$$는 고리 부분에서 더 빠르게 이동한다는 의미이다.
그림에서는 $$t_0$$, $$t_1$$, $$t_2$$, $$t_3$$는 등간격을 이루고 있는 반면 $$\alpha(t_0)$$, $$\alpha(t_1)$$, $$\alpha(t_2)$$, $$\alpha(t_3)$$은 점점 간격이 벌어지는 것을 통해 이를 확인할 수 있다.

![fig02](/docs/robotics/06-arc-length-reparametrization/images/fig02.png)

어느 날 자고 일어났더니 당신은 이 상황이 마음에 들지 않았다 — 왜 마음에 들지 않았는지는 다음 섹션에서 후술할테니 우선 "그런가보다" 하고 받아들이시라.
당신은 갑자기 아래와 같이 곡선을 parametrization하고 싶어졌다.

1. $$t$$ 대신에 $$s$$라는 변수를 정의하고, interval $$(c, d)$$에서 정의되도록 curve를 parametrization하고 싶다.
2. $$s$$가 interval $$(c, d)$$를 등속도로 움직일 때, $$\alpha(s)$$도 등속도로 움직이게 하고 싶다.

당신이 하고 싶은 일을 그림으로 표현해보면 아래와 같으리라.
필자의 그림 실력이 부족하여 잘못된 방향으로 이해할까 노파심에 적자면, 필자는 아래 그림에서 $$\alpha(s_0)$$, $$\alpha(s_1)$$, $$\alpha(s_2)$$, 그리고 $$\alpha(s_3)$$이 curve 내에서 등간격을 이루고 있음을 강조하고 싶었다.

![fig03](/docs/robotics/06-arc-length-reparametrization/images/fig03.png)

당신이 하고 싶은 일은 의외로 몹시 간단하게 처리할 수 있는데, 단지 $$h:\ s \rightarrow t$$ 함수를 하나 준비해주기만 하면된다.
아래 그림에서는 적색 화살표로 $$t = h(s)$$를 표시해두었다.
설명이 필요 없을 정도도 간단하지 않은가?
$$s0$$에 해당하는 curve 위의 위치를 알고 싶을 때, (1) $$h(s_0)$$를 구하고 (2) 이를 $$\alpha$$에 넣어서 $$\alpha(h(s_0))$$를 봐주면 되는 것이다.
결과적으로 당신은 새로운 curve $$\beta(s) = \alpha(h(s))$$를 만들게 되는 것이다.

![fig04](/docs/robotics/06-arc-length-reparametrization/images/fig04.png)

이와 같이 새롭게 사용할 parameter $$s$$로 부터 기존의 파라미터 $$t$$로 가는 함수 $$h:\ s \rightarrow t$$를 사용해서 curve를 입맛에 맞게 parametrization하는 과정이 바로 reparametrization이다.

## Arc Length Function

Curve의 arc length function이란 무엇일까?
Arc라는 단어가 원을 떠올리게 만들지만, arc length는 단순히 curve의 길이를 나타낸다.
보다 엄밀히 이야기하면, $$t \in [a, b]$$로 parametrization되는 curve의 arc length function은 아래와 같이 정의한다.
어감이 몹시 어색하지만 이를 국문으로는 호장함수(...)라고 부른다고 한다.

$$
s(t) = \int_{a}^{t} ||\alpha^{\prime}(u)||\,du
$$

## Arc Length Reparametrization

이적 섹션에서 이야기한 arc length function $$s(t)$$를 열심히 째려보도록 하자.
우리는 regular curve에 대해서만 이야기하고 있으므로 $$\alpha^{\prime}(u) \neq 0\, \forall u \in \mathbb{R}$$이고, 따라서 $$||\alpha^{\prime}(u)|| \gt 0\, \forall u \in \mathbb{R}$$이다.
이것은 곧 $$s(t)$$가 순증가함수이고, 따라서 bijective function이며, 역함수를 갖는다는 이야기이다.
$$s$$는 $$t$$에서 $$s$$로의 함수였으니 $$s^{-1}$$은 $$s$$에서 $$t$$로의 함수가 될테다.
$$s$$에서 $$t$$로의 함수가 있으면 우리는 첫번째 섹션에서 보았듯이 reparametrization을 할 수 있다 — $$h = s^{-1}:\ s \rightarrow t$$로 두고 reparametrization을 한다는 이야기이다.
이렇듯 arc length function을 사용해서 — 보다 정확히는 그 역함수를 사용해서 — reparametrization을 하는 과정이 바로 arc length reparametrization이다.
예제로 $$\alpha(t) = (acos(t), asin(t), bt),\, t \in (0, 2\pi)$$와 같이 주어진 curve를 arc length reparametrization해보자.

$$
\begin{align*}
s(t) & = \int_{0}^{t} ||\alpha^{\prime}(u)||\,du \\
& = \int_{0}^{t} \sqrt{a^2sin(u) + a^2cos(t) + b^2}\,du \\
& = \sqrt{a^2 + b^2}t \\
s^{-1}(s) & = \frac{s}{\sqrt{a^2 + b^2}} \\
\therefore \beta(s) & = \alpha(s^{-1}(s)) \\
& = (acos(\frac{s}{\sqrt{a^2 + b^2}}), asin(\frac{s}{\sqrt{a^2 + b^2}}), b\frac{s}{\sqrt{a^2 + b^2}})
\end{align*}
$$

## Why Arc Length Reparametrization?

이전 섹션들을 통해서 그럭저럭 arc length reparametrization이 무엇인지는 설명했다.
그럼 대체 이짓을 왜하는 것일까?
결론부터 이야기하면, arc length $$s$$로 parametrization된 curve $$\beta(s)$$는 $$||\beta^{\prime}(s)|| = 1$$이라는 좋은 성질을 갖기 때문이다.
직관적으로 생각하면 속력이 1이라는것이니 s가 1만큼 움직이면 curve에서도 그 image가 1만큼 움직이는 것이다.
달리 말해 $$\beta(3)$$, $$\beta(5)$$ 따위를 찾아가면 진짜 curve의 시작점으로부터의 이동거리가 3, 5가 되는 지점이 나온다는 이야기이다.
딱 보아도 분석이 몹시 쉬울 것 같지 않은가?

이제 마지막으로 왜 $$ \lVert \beta^{\prime}(s) \rVert = 1 $$ 이 되는지만 정리하도록 하겠다.

1. $$s(t) = \int_{a}^{t} \lVert \alpha^{\prime}(u) \rVert \,du$$의 양변을 $$t$$에 대해서 미분하면 $$\frac{ds}{dt} = \lVert \alpha^{\prime}(t) \rVert$$를 얻는다.
2. 1의 역수를 취하여 $$\frac{dt}{ds} = \frac{1}{\lVert \alpha^{\prime}(t) \rVert}$$을 얻는다.
3. $$\beta(s) = \alpha(s^{-1}(s))$$를 $$s$$에 대해 미분하면 $$\frac{d\beta}{ds} = \frac{d}{ds}\alpha(s^{-1}(s)) = \frac{d\alpha}{dt}\frac{dt}{ds}$$
4. $$\frac{d\alpha}{dt} = \alpha^{\prime}(t)$$이므로 (by definition), $$\frac{d\beta}{ds} = \frac{d\alpha}{dt}\frac{dt}{ds} = \alpha^{\prime}(t) \frac{1}{\lVert \alpha^{\prime}(t) \rVert} = \pm 1$$

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
