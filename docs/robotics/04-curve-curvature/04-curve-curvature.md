---
title: Curve Curvature
layout: default
parent: Robotics
permalink: /docs/robotics/04-curve-curvature
---

# Curve Curvature

**Keywords:** `Curvature`{: .label }

필자는 최근에 읽고 있던 [survey paper](https://arxiv.org/abs/1604.07446)에서 임의의 curve $$\mathbf{x}$$의 곡률 $$\kappa$$를 구하는 아래의 식을 발견하였다.

$$
\kappa = \frac{|\mathbf{x}^{\prime} \times \mathbf{x}^{\prime\prime}|}{|\mathbf{x^{\prime}}|^3}
$$

Paper에는 Frenet-Serret 공식으로부터 이것이 유도된다고 써있는데, 필자는 이것을 고등학교 때 배운 삼각형의 넓이 공식으로부터 유도해보려고 한다.
이 공식에 이름이 있는지 궁금했으나 이름을 찾지는 못했다.
어찌되었건 사용할 공식은 $$R = \frac{abc}{4S}$$이다 ([link](https://web.archive.org/web/20130620011530/http://www.artofproblemsolving.com/Wiki/index.php/Circumradius)).

## What is the curvature of a curve?

기초적인 내용이지만 curve의 curvature란 무엇인지에 대해서부터 이야기해보도록 하겠다.
당신이 임의의 curve 위를 등속도로 운동하고 있다고 가정해보자.
당신이 curve 위의 한 점에 위치한 순간 당신의 운동을 원운동으로 가정할 수 있다.

예를들어, 아래의 롤러코스터 그림과 같이 당신이 롤러코스터 트랙의 한 점에 위치해있다고 가정하자.
그 위치를 기준으로 당신의 운동은 청색 점선과 같이 원운동으로 가정할 수 있다.

![fig01](/docs/robotics/04-curve-curvature/images/fig01.png)

Curve 위의 특정 위치 $$\mathbf{x}(s)$$에서 위에서 언급한 원을 찾았고 그 원의 반지름이 $$R(\mathbf{x}(s))$$이었다고 해보자.
Curve의 특정 위치 $$\mathbf{x}(s)$$에서의 curvature $$\kappa(\mathbf{x})$$는 단순히 $$R(\mathbf{x}(s))$$의 역수로 아래와 같이 정의된다.

$$
\kappa(\mathbf{x}(s)) = \frac{1}{R(\mathbf{x}(s))}
$$

## Curve curvature formula

이전 섹션의 내용을 머릿속에 잘 새겨두고, 이제 극한을 이용해서 curvature를 정의해보자.
주어진 curve를 무진장 확대하니 아래 그림과 같이 보였다고 생각해보자.

![fig02](/docs/robotics/04-curve-curvature/images/fig02.png)

이전 섹션에서 밝힌 $$\kappa(\mathbf{x}(s))$$의 정의와 (i.e., R의 역수), 모두에 이야기한 고등학교 때 배운 삼각형 외접원 공식 (i.e., $$R = \frac{abc}{4S}$$)을 사용하면 아래의 식을 얻어낼 수 있다.

$$
\begin{align*}
\kappa(\mathbf{x}(s)) & = \frac{1}{R(\mathbf{x}(s))} \\
& = \frac{4 \Delta abc}{abc} \\
& = \lim_{h\to0} \frac{4 \cdot \frac{1}{2} |(\mathbf{x}(s+h) - \mathbf{x}(s)) \times (\mathbf{x}(s-h) - \mathbf{x}(s))|}{|\mathbf{x}(s-h) - \mathbf{x}(s)| \cdot |\mathbf{x}(s+h) - \mathbf{x}(s)| \cdot |\mathbf{x}(s+h) - \mathbf{x}(s-h)|} \\
& = \lim_{h\to0} \frac{\frac{4 \cdot \frac{1}{2} |(\mathbf{x}(s+h) - \mathbf{x}(s)) \times (\mathbf{x}(s-h) - \mathbf{x}(s))|}{2h^3}}{\frac{|\mathbf{x}(s-h) - \mathbf{x}(s)| \cdot |\mathbf{x}(s+h) - \mathbf{x}(s)| \cdot |\mathbf{x}(s+h) - \mathbf{x}(s-h)|}{2h^3}} \\
& = \lim_{h\to0} \frac{\frac{1}{h}|\frac{\mathbf{x}(s+h) - \mathbf{x}(s)}{h} \times \frac{\mathbf{x}(s-h) - \mathbf{x}(s)}{h}|}{|\frac{\mathbf{x}(s-h) - \mathbf{x}(s)}{h}| \cdot |\frac{\mathbf{x}(s+h) - \mathbf{x}(s)}{h}| \cdot |\frac{\mathbf{x}(s+h) - \mathbf{x}(s-h)}{2h}|} \\
& = \lim_{h\to0} \frac{\frac{1}{h}|\frac{\mathbf{x}(s+h) - \mathbf{x}(s)}{h} \times (\frac{\mathbf{x}(s+h) - \mathbf{x}(s)}{h} + \frac{\mathbf{x}(s-h) - \mathbf{x}(s)}{h})|}{|\frac{\mathbf{x}(s-h) - \mathbf{x}(s)}{h}| \cdot |\frac{\mathbf{x}(s+h) - \mathbf{x}(s)}{h}| \cdot |\frac{\mathbf{x}(s+h) - \mathbf{x}(s-h)}{2h}|} \quad - \because \overrightarrow{u} \times \overrightarrow{v} = \overrightarrow{u} \times (\overrightarrow{u} + \overrightarrow{v}) \\
& = \lim_{h\to0} \frac{|\frac{\mathbf{x}(s+h) - \mathbf{x}(s)}{h} \times \frac{\mathbf{x}(s+h) - 2\mathbf{x}(s) + \mathbf{x}(s-h)}{h^2}|}{|\frac{\mathbf{x}(s-h) - \mathbf{x}(s)}{h}| \cdot |\frac{\mathbf{x}(s+h) - \mathbf{x}(s)}{h}| \cdot |\frac{\mathbf{x}(s+h) - \mathbf{x}(s-h)}{2h}|} \\
& = \frac{|\mathbf{x}^{\prime} \times \mathbf{x}^{\prime\prime}|}{|\mathbf{x^{\prime}}|^3}
\end{align*}
$$

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
