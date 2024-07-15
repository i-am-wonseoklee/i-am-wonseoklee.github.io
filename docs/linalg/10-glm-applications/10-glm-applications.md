---
title: GLM Applications
layout: default
nav_order: 11
parent: Linear Algebra
permalink: /docs/linalg/10-glm-applications
---

# GLM Applications

**Textbook:** pp.230 - 251

**Keywords:** `general linear model`{: .label }, `multicollinearity`{: .label }

`GLM` (General Linear Model) 의 응용을 소개하는 챕터로서 특별히 기록해둘만한 내용은 많지 않고, 단지 단어 소개 정도의 의미로 조금을 정리해둔다.
그나마(?) 정리할 가치가 있어보이던 내용은 이미 [직전 챕터](/docs/linalg/09-glm)에서 다루었으니 이번 챕터는 연습 문제에 의의를 두도록 

## I. Multicollinearity

`Multicollinearity`는 국문으로 다중공선성 이라고 불린다.
웹에서 의미를 찾아보면 "다중 회귀 모델에서 하나의 독립변수가 다른 독립변수로부터 상당한 정확도로 선형적으로 예측될 수 있는 것" 이라고 한다.
이렇게 읽으면 뜨악스럽지만, 사실 이 말은 단지 설계 행렬의 열에 선형 종속인 열이 존재한다는 말이다.
극단적이지만 한 방에 이해되는 예를 들어보자면, 설계 행렬의 한 열에는 섭씨 온도가, 다른 한 열에는 화씨 온도가 있는 경우쯤 되리라.

## II. Regularization

우리는 [이전 쳅터](/docs/linalg/09-glm)에서 주어진 문제를 $$\mathbf{X} \mathbf{\beta} = \mathbf{y}$$ 로 formulation 하고, 왼쪽 역행렬 (또는 당신이 마음에 들었던 설명) 을 사용해서 아래와 같이 $$\mathbf{\beta}$$ 를 구하였다.

$$
\mathbf{\beta} = (\mathbf{X}^T \mathbf{X})^{-1} \mathbf{X}^T \mathbf{y}
$$

그런데, 만약 $$(\mathbf{X}^T \mathbf{X})^{-1}$$ 이 존재하지 않으면 어떻게 하겠는가?
책에서는 이러한 상황을 해결하기 위한 방법 중 하나로 정규회를 소개하고 있다.
이 챕터에서 말하는 정규화라는 것은 뭐 대단한 것이 아니고...그냥 [Frobenius norm](/docs/linalg/04-matrices-part2) 만큼 [행렬을 이동](/docs/linalg/03-matrices-part1)시키는 것이다.
말보다는 식이 조금 더 간결하리라.
정규화를 통해 $$\mathbf{\beta}$$ 를 구한다면 아래와 같이 구할 수 있다.

$$
\begin{align*}
\mathbf{\beta} & = (\mathbf{X}^T \mathbf{X} + \gamma ||\mathbf{X}^T \mathbf{X}||_F \mathbf{I})^{-1} \mathbf{X}^T \mathbf{y} \\
 & = (\mathbf{X}^T \mathbf{X} + \gamma ||\mathbf{X}||_F^{2} \mathbf{I})^{-1} \mathbf{X}^T \mathbf{y} \\
\end{align*}
$$

## III. Exercises

이 챕터의 연습문제 풀이는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/linalg/10-glm-applications/exercises)에서 확인할 수 있다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
