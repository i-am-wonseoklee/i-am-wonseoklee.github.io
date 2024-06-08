---
title: Vector Applications
layout: default
nav_order: 3
parent: Linear Algebra
permalink: /docs/linalg/02-vector-applications
---

# Vector Applications

**Textbook:** pp.70 - 83

**Keywords:** `Pearson Correlation Coefficient`{: .label }

이 챕터에서는 벡터의 개념을 가지고 해볼 수 있는 여러가지 응용들이 개괄되었다.
역시나 그닥 특별하다고 볼만한 내용은 없었고, 필자가 모르고 있었던 것만을 정리하도록 한다.

## I. Pearson Correlation Coefficient

임의의 두 벡터, $$\mathbf{v} = (v_{1}, v_{2}, ..., v_{n})$$, $$\mathbf{w} = (w_{1}, w_{2}, ..., w_{n})$$, 가 있다고 해보자.
두 벡터 사의의 correlation을 `Pearson Correlation Coefficient` (이하 `PCC`)라는 것으로 나타낼 수 있다고 한다.
뭔가 싶어 조금 쫄았는데, 사실 이것은 그냥 (1) 두 벡터를 `평균중심화` 한 뒤에 구한 (2) `Cosine similarity` 이다.
`평균중심화`도 쫄 필요가 전혀 없는 것이...그냥 주어진 벡터에서 벡터 요소의 평균 값을 뻰 것이라고 한다.
구구 절절히 살명하기 보다는 그냥 식으로 한 줄 적고 끝내는 것이 나으리라.

$$\mathbf{v} = (v_{1}, v_{2}, ..., v_{n})$$, $$\mathbf{w} = (w_{1}, w_{2}, ..., w_{n})$$ 의 `PCC`, $$PCC(\mathbf{v}, \mathbf{w})$$는 아래와 같이 구한다.

{: .highlight }
> - Let $$\bar{v} = \frac{\Sigma_{i=1}^{n}{v_i}}{n}$$
> - Let $$\bar{w} = \frac{\Sigma_{i=1}^{n}{w_i}}{n}$$
> - Let $$\bar{\mathbf{v}} = (v_1 - \bar{v}, v_2 - \bar{v}, ..., v_n - \bar{v})$$
> - Let $$\bar{\mathbf{w}} = (w_1 - \bar{w}, w_2 - \bar{w}, ..., w_n - \bar{w})$$
> - Then, $$PCC(\mathbf{v}, \mathbf{w}) = \frac{\bar{\mathbf{v}}^T \bar{\mathbf{w}}}{\lvert\bar{\mathbf{v}}\rvert{\ }\lvert\bar{\mathbf{w}}\rvert}$$

## III. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/linalg/02-vector-applications/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
