---
title: Vectors (Part 2)
layout: default
nav_order: 2
parent: Linear Algebra
grand_parent: TechTome Summaries
permalink: /docs/tech-tome-summaries/linear-algebra/01-vectors-part2
---

# Vectors (Part 2)

**Textbook:** pp.53 - 69

**Keywords:** `Linearly Independent`{: .label }

"뭐라도 블로그에 옮겨적어봐야지"라는 심산으로 쭉 챕터를 읽어보았는데, 암울하게도 딱히 옮겨적을 가치가 있는 내용은 없었다.
뭐 이런 날도 있어야 블로그 포스팅이 조금이라도 덜 부담스럽지 (~~그래서, 조금이라도 더 부지런하게 업로드하지~~) 않겠는가?
이 챕터에서 다룬 내용은 `벡터 집합`. `선형 결합`, `선형 독립성`, `부분공간`, `생성`, `기저` 따위가 있다.
모든 내용은 여느 선형대수학 교과서가 소개하는 그 수준인데, (솔직히 딱히 설명을 더 잘했다고 보기도 어려운...) 선형독립성을 수학적으로 정의하는 부분이 신박한 형태라서 그거라도 하나 정리해놓는다.

## I. Linear Independent

아마도 많은 공돌이 친구들은 (나와 같다면) 임의의 벡터 집합 $$V = \{\mathbf{v}_{1}, \mathbf{v}_{1}, ..., \mathbf{v}_{n}\}$$ 이 linearly independent하다 (i.e. 선형독립) 의 수학적 정의를 아래와 같이 외우고 있을 것이다 (i.e. 아래의 명제가 만족하면 선형독립인 것으로).

$$
\mathbf{0} = {\lambda}_{1}\mathbf{v}_{1} + {\lambda}_{2}\mathbf{v}_{2} + ... + {\lambda}_{n}\mathbf{v}_{n} \rightarrow {\lambda}_{1} = {\lambda}_{2} = ... = {\lambda}_{n} = 0
$$

이 식 (또는 정의) 을 이 책에서는 조금 신박한 형태로 기술하는데, 아래 식의 해 ($$\lambda$$) 를 구할 수 있으면, $$V$$ 가 linearly dependent하다고 한다 (i.e. 선형 종속).
뭐 솔직히 같은 말이라서 크게 주목할 필요는 없지만, 혹시라도 나중에 이 책에서 아래와 같은 표현이 나오면 당황하게 될 테니 적어 놓는다.

$$
\mathbf{0} = \mathbf{v}_{1} + \frac{\lambda_{2}}{\lambda_1}\mathbf{v}_{2} + ... + \frac{\lambda_{n}}{\lambda_1}\mathbf{v}_{n}, \lambda_1 \neq 0
$$

## III. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/tech-tome-summaries/linear-algebra/01-vectors-part2/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>