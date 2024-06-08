---
title: Inverse
layout: default
nav_order: 7
parent: Linear Algebra
grand_parent: TechTome Summaries
permalink: /docs/tech-tome-summaries/linear-algebra/06-inverse
---

# Inverse

**Textbook:** pp.159 - 178

**Keywords:** `left/right inverse matrix`{: .label }

이 챕터에서 정리해둘만한 내용은 left/right inverse matrix 밖에 없다.
(일반적인) inverse matrix 에 대한 내용은 대학교 선형대수학 입문 과정을 벗어나지 않고, Moore-Penrose inverse matrix 에 대한 설명은 다음 챕터로 미뤄지면서 깊게 다뤄지지 않는다.
필자의 경우 부끄럽게도 left/right inverse matrix 라는 개념 자체를 처음 들어보았다.

## I. Left inverse matrix

직관적으로 이야기하면 어떠한 행렬 $$\mathbf{A}$$ 에 대해서 $$\mathbf{L}\mathbf{A} = \mathbf{I}$$ 가 되게 하는 $$\mathbf{L}$$ 을 $$\mathbf{A}$$ 의 left inverse 라고 부른다.
그리고, 당연히 일반적으로 $$\mathbf{A}\mathbf{L} \neq \mathbf{I}$$ 이다.
정의만 적고보면 "뭔 뚱딴지 같은 소리야?" 싶다.
그런데, left inverse matrix를 갖는 예제 하나에 대해서 살펴보면 조금 더 와닿는다.

{: .note }
> 필자는 사실 책에 소개되어 있는 이 예제 말고 left inverse matrix 가 존재하는 다른 경우가 있는지 모르겠다.
> 위키피디아에도 그냥 이 예제만 찍 하고 나와있다.

Left inverse matrix를 갖는 행렬 $$\mathbf{A}$$ 의 예제는 "최대 계수를 갖는 높은 행렬 (i.e. 행수 > 열수)" 이다.
높은 행렬은 당연히 정방행렬이 아니기 때문에 일반적인 inverse matrix 는 존재하지 않는다.
하지만, $$\mathbf{A}^T\mathbf{A}$$ 는 정방행렬이 되고 inverse matrix 를 갖는다.
따라서, $$(\mathbf{A}^T\mathbf{A})^{-1}\mathbf{A}^T\mathbf{A} = \mathbf{I}$$ 로 부터 $$\mathbf{A}$$ 의 left inverse, $$\mathbf{L} = (\mathbf{A}^T\mathbf{A})^{-1}\mathbf{A}^T$$ 을 얻을 수 있다.

직전의 설명에서 "$$\mathbf{A}^T\mathbf{A}$$ 는 정방행렬이 되고 inverse matrix 를 갖는다." 라고 이야기했다.
아마도, "미친놈이 왜 지 맘대로 주장만하고 지랄이야" 싶은 독자들이 있으리라.
이건 구구절절 증명하면 할 수 있는데, 귀찮으니 여기에 아래의 정리만 하나 던져놓고 가도록 하겠다.
증명은 rank-nullity 정리를 잘 사용하면 할 수 있다.

{: .note }
> $$rank(\mathbf{A}) = rank(\mathbf{A}^T) = rank(\mathbf{A}\mathbf{A}^T) = rank(\mathbf{A}^T\mathbf{A})$$

## II. Right inverse matrix

위에서 left inverse matrix 를 설명하고, 이걸 여기에 또 정리하는 것은 아무리 생각해도 바이트 낭비이다.
Left inverse matrix 와 비슷하게, "최대 계수를 갖는 낮은 행렬 (i.e. 행수 < 열수)" 에 대해 정의되는 역행렬로 이해하고 넘어가자.

## III. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/tech-tome-summaries/linear-algebra/06-inverse/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
