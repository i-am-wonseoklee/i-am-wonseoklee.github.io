---
title: Miscellaneous
layout: default
nav_order: 4
parent: "Plan T"
grand_parent: "Reproducing Papers"
permalink: /docs/reproducing-papers/00-plan-t/03-miscellaneous
---

# Miscellaneous

**Keywords:** `token type embedding`{: .label }, `classification token`{: .label }

{: .note }
> 이 챕터부터 이어질 몇 개의 후속 챕터는 `PlanT` 논문을 수월하게 이해하기 위해 알고 있어야 할 내용들을 정리한다.
> 물론, 이 내용들은 필자의 주관과 경험에 따라 선정되었음을 참고하자.
> 즉, 자명해보여도 필자가 모르던 것이면 정리할 것이고, 어려워보여도 필자가 알던 것이면 정리하지 않을 것이다.

앞선 챕터들에서 트랜스포머 인코더와 GRU 디코더에 대해 설명하였다.
앞선 챕터의 설명들은 다분히 일반적인 트랜스포머 인코더와 GRU 디코더에 대한 설명이었다.
`PlanT`는 여기에 약간의 테크닉을 더해 제안되었는데, **(1)** token type embedding 과 **(2)** classification token의 사용이 그것이다.
이번 챕터에서는 이 두 가지를 차례로 설명한다.

## I. Token Type Embedding

인코더 챕터에서 `PlanT`가 driving scene을 어떻게 토큰 시퀀스로 표현하는지 살펴봤다.
장면을 구성하는 각 요소, 즉 ego의 경로 waypoint이든 주변 차량이든 보행자든, 모두 linear projection을 통해 $$d_\text{model}$$ 차원의 벡터로 변환한다.
그런데 여기서 한 가지 문제가 있다.
linear projection은 원시 입력의 수치적인 특성만을 반영할 뿐, 그 토큰이 *어떤 종류의 객체인지*라는 정보는 담지 않는다.
예를 들어, "좌표가 (2.0, 1.5)인 route waypoint"와 "좌표가 (2.0, 1.5)인 차량"은 원시 입력 수치는 같아도 의미상으로 전혀 다른 존재다.
인코더가 self-attention을 수행할 때 이 둘을 구별하지 못한다면, 맥락을 잘못 읽을 가능성이 있다.

이 문제를 해결하는 방법은 놀랍도록 간단하다.
토큰의 종류마다 하나씩 **학습 가능한 벡터**를 추가로 정의하고, 각 토큰의 feature embedding에 해당 타입 벡터를 **더해주는 것이다**.
이것이 **token type embedding**이다.
중요한 점은 type embedding이 **타입 하나당 벡터 하나**라는 것이다.
같은 타입의 토큰이 여러 개 있더라도 동일한 type embedding 벡터를 공유한다.
장면 안에 자동차 10대가 있어도 이들은 모두 동일한 $$\mathbf{e}_\text{vehicle}$$ 을 각자의 feature embedding에 더한다.
자동차마다 위치와 속도가 달라 feature embedding은 제각각이지만, "차량임"이라는 타입 정보는 동일하게 반영되는 것이다.

$$
\mathbf{x}_i = \underbrace{\mathbf{W}_i \mathbf{x}_{i,\text{raw}} + \mathbf{b}_i}_{\text{feature embedding}} + \underbrace{\mathbf{e}_{\text{type}(i)}}_{\text{type embedding}}
$$

`PlanT`에서는 토큰 타입이 두 가지다: ego route와 그 외 교통 참여자(차량 등).
따라서 학습 파라미터로 두 개의 타입 임베딩 벡터가 추가된다.
원시 수치가 같더라도 타입이 다르면 인코더에 들어가는 벡터가 달라지므로, 인코더는 토큰의 종류를 구분할 수 있게 된다.

{: .note }
> 이 아이디어는 BERT (Bidirectional Encoder Representations from Transformers) 에서 두 문장을 구분하기 위해 도입한 **segment embedding**과 완전히 동일한 발상이다.
> 솔직히 말하면 필자도 BERT를 제대로 공부한 적이 없다. 그냥 "NLP 쪽에서 유명한 트랜스포머 기반 모델"이라는 정도만 알고 있을 뿐이다.
> 어쨌든, BERT는 "문장 A"와 "문장 B"를 구별하기 위해 각 토큰에 문장 소속 정보를 벡터로 더했고, `PlanT`는 이를 객체 타입 구분에 그대로 응용한다.

## II. Classification Token

인코더가 시퀀스를 처리하고 나면 토큰마다 하나씩, 총 $$N$$개의 출력 벡터가 생긴다.
GRU 디코더는 이 출력들로부터 waypoints를 하나씩 생성해야 하는데, 초기 hidden state로 삼을 **장면 전체를 요약한 벡터 하나**가 필요하다.
$$N$$개짜리 벡터 묶음을 어떻게 하나로 압축할 것인가?

가장 단순한 방법은 $$N$$개의 출력 벡터를 평균 내는 것이다.
하지만 이 방식은 모든 토큰을 동등하게 취급한다는 문제가 있다.
전방 가까이 있는 차량과 저 멀리 있는 표지판이 waypoint 예측에 동등하게 기여해야 할 이유는 없다.

더 나은 방법은 시퀀스 맨 앞에 **특수 토큰 하나를 추가**하는 것이다.
이 특수 토큰을 **classification token**, 줄여서 `[CLS]` 토큰이라 부른다.
`[CLS]` 토큰은 아무런 실제 객체도 나타내지 않는다.
초기값은 임의로 설정한 학습 가능한 벡터이며, 의미상으로는 "아직 아무것도 모르는 빈 요약자" 정도로 볼 수 있다.

이 `[CLS]` 토큰이 인코더를 통과하면 어떻게 될까?
self-attention에 의해 `[CLS]` 토큰은 시퀀스 내 모든 다른 토큰에 주목할 수 있다.
즉, 중요한 토큰에는 높은 attention weight를, 덜 중요한 토큰에는 낮은 attention weight를 부여하면서 장면 전체의 정보를 선택적으로 흡수한다.
그 결과, 인코더 출력에서 `[CLS]` 토큰에 해당하는 벡터는 장면 전체를 학습된 방식으로 요약한 표현이 된다.

`PlanT`에서는 이 `[CLS]` 토큰의 인코더 출력을 GRU 디코더의 초기 hidden state로 사용한다.
GRU는 이 요약 벡터로부터 시작해 waypoints를 순차적으로 생성한다.

{: .note }
> `[CLS]` 토큰 역시 BERT에서 처음 대중화된 기법이다.
> BERT는 문장 분류 태스크에서 `[CLS]` 토큰의 최종 출력을 분류 헤드에 연결하는 식으로 활용했다고 하는데, 필자가 BERT를 잘 모르니 이 설명이 완전히 정확한지는 장담하기 어렵다.
> 발상은 동일하다: 개별 토큰 출력을 직접 쓰는 대신, 인코더가 알아서 전체 문맥을 `[CLS]` 하나에 응집시키도록 학습시킨다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
