---
title: Configuration Space (Part 1 of 2)
layout: default
parent: Modern Robotics
permalink: /docs/modern-robotics/00-configuration-space-00
---

# Configuration Space (Part 1 of 2)

**Textbook:** pp.11 - 23

**Lecture:** ~ Chapter 2: Configuration Space (Part 1 of 2)

## I. Configuration

Configuration은 robot을 이루는 모든 point들에 대한 **위치**를 나타내는 specification이다. 예를들어, 2D planar robot의 경우 $$(x, y, theta)$$, 3D spatial robot의 경우 $$(x, y, z, roll, pitch, yaw)$$가 될 수 있다.

## II. Degree of Freedom(DoF)

사실 그 동안 내가 보아온 robot들은 깊게 생각해보지 않아도 "아, 이거 X-자유도네!"같이 말할 수 있을 정도로 단순한 형태들이었다. 그래서, DoF라는 개념이 이렇게 심오하게 정의되는 것인지 처음 알게되었다. Textbook 및 lecture를 살펴보면 아래와 같이 여러가지 방법으로 정의해볼 수 있을 것 같다.

- Robot의 configuration을 나타내기 위해 필요한 최소한의 **실수** 갯수
- Configuration space의 dimension
- $$\sum freedom \, of \, bodies - \# \, of \, independent \, constraints$$ &nbsp;

{: .highlight }
> 세번째 정의를 잘 받아들이는 것이 중요하다. 굳이 "이해하는 것"이라는 표현보다 "받아들이는 것"이라는 표현을 쓴 데에는 textbook의 동전 예제에 대한 당위성(?)을 나조차도 아직 충분히 헤아리지 못했기 때문이다. 일단 받아들임으로서 아래 III절의 typical robot joints를 보다 순조롭게 이해할 수 있다.

## III. Robot Joints

살피고 있는 textbook, lecture에서 등장하는 robot들은 N개의 body와 link들을 연결하는 joint들로 이루어져 있다고 한다. 그리고, 아래는 robot에서 자주 사용되는 joint들을 정리해놓은 것이다.

{: .note }
> - Robotics에서는 body를 link라고 부르고, 통상 지면도 link로 친다고 한다.
> - 일단 당분간은 1개의 joint는 항상 2개의 link를 연결하는 것으로 가정한다.

![joints](/docs/modern-robotics/00-configuration-space-00/joints.png) 

일단, 바보가 아니라면 위의 그림에 예시된 joint들의 dof는 쉽게 생각해낼 수 있다. 따라서, 아래 표의 dof 열은 쉽게 채워넣을 수 있을 것이다. `# of constraints` 열들이 조금 생소할 수 있는데, II절에서 dof를 $$\sum freedom \, of \, bodies - \# \, of \, independent \, constraints$$로도 정의할 수 있었던 것을 떠올려보자.

{: .highlight }
> 예를들어, 두 개의 spatial link A, B를 연결하는 spherical joint를 생각해보자.
> - Joint 없이 A, B가 따로 존재할 때 A에 대해서 B는 100% 자유롭게 위치할 수 있으므로 $$\sum freedom \, of \, bodies = 6$$이다(A를 기준점으로 고정시켜서 논의하므로 12가 아님에 주의하자).
> - 이제, joint를 달았는데 이 joint의 dof가 3이라는 것은 우리가 상식적으로 알고 있다.
> - "아! 그럼 이 joint를 달면서 $$\# \, of \, independent \, constraints = 3$$이 생겨났구나"라고 생각할 수 있다($$dof = \sum freedom \, of \, bodies - \# \, of \, independent \, constraints$$이므로).

| joint type  | dof     | # of constraints btw planar links | # of constraints btw spatial links |
|:------------|:--------|:----------------------------------|:-----------------------------------|
| revolute    | 1       | 2                                 | 5                                  |
| prismatic   | 1       | 2                                 | 5                                  |
| helical     | 1       | N/A                               | 5                                  |
| cylindrical | 2       | N/A                               | 4                                  |
| universal   | 2       | N/A                               | 4                                  |
| spherical   | 3       | N/A                               | 3                                  |

## IV. Grubler's Formula

어떻게 발음하는 것인지 모르겠는 사람의 이 공식은 link 갯수, joint 타입/갯수등을 딱 넣어주면 robot이 얼마의 dof를 갖는지 알려주는 아주 신박한 공식이다. 일단 아래와 같이 notation을 정의하자.

- $$N$$: 지면을 포함한 link의 수
- $$m$$: 각 link의 dof(자명하게, planar robot이면 2, spatial robot이면 3)
- $$J$$: Joint의 수
- $$f_i$$: i번째 joint의 dof
- $$c_i$$: i번째 joint의 constraint 수

이때 dof는 아래와 같이 정의된다.

$$
\begin{align*}
dof & = m(N - 1) - \sum_{1}^{J} c_i \\
    & = m(N - 1) - \sum_{1}^{J} (m - f_i) \\
    & = m(N - 1 - J) + \sum_{1}^{J} f_i
\end{align*}
$$

이 공식의 강력한 점은 언뜻보기에 몹시 복잡하게 생긴 로봇의 dof도 무지성으로 계산해낼 수 있다는 점이다. 가령 lecture에 등장하는 <strike>어떤 미친놈이 만들었나 싶은</strike> 아래의 `Stewart-Gough Platform`은 dof가 6임을 공식 1번으로 알아낼 수 있다.

![stewart](/docs/modern-robotics/00-configuration-space-00/stewart.gif)

{: .highlight }
> `Stewart-Gough Platform`은 총 14개 link, 6개의 universal joint, 6개의 prismatic joint, 6개의 spherical joint로 이루어져 있다. 공식에 그대로 대입해주면, $$dof = 6(14-1-18)+2 \cdot 6 + 1 \cdot 6 + 3 \cdot 6 = 6$$을 얻을 수 있다. 

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>