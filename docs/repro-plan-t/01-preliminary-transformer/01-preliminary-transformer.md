---
title: "preliminary: Transformer"
layout: default
nav_order: 2
parent: "reproducing: Plan T"
permalink: /docs/repro-plan-t/01-preliminary-transformer
---

# Transformer

**Keywords:** `Transformer`{: .label }

이 챕터부터 이어질 몇 개의 후속 챕터는 `PlanT` 논문을 수월하게 이해하기 위해 알고 있어야 할 내용들을 정리한다.
물론, 이 내용들은 필자의 주관과 경험에 따라 선정되었음을 참고하자.

트랜스포머, 트랜스포머, 트랜스포머.
요즘에는 로보틱스건 NLP건 signal processing이건 뭐건 모두들 트랜스포머를 이야기한다.
필자에게 익숙한 트랜스포머는 옵티머스 프라임뿐인데, 뭐 어쩌라는걸까?
옵티머스 프라임 상태에서 시작해서 다른 트랜스포머가 머리에 들어올 때까지 학습을 시작해보도록 하자.

![optimus](/docs/repro-plan-t/01-preliminary-transformer/assets/transformer.png)

## I. Input and Output

트랜스포머의 세부 메커니즘에 들어가기 전에 큰 그림을 먼저 잡아두자.
세부 내용은 이후 섹션에서 순서대로 채워나갈 것이다.
트랜스포머는 크게 **인코더(encoder)**와 **디코더(decoder)**로 구성된다.
인코더는 입력 시퀀스를 받아 각 토큰에 문맥 정보를 녹인 표현으로 변환하고, 디코더는 그 표현을 참조해 출력 시퀀스를 생성한다.
큰 그림에서 입출력을 보면 다음과 같다:

- **인코더 입력**: $$[x_1, x_2, \ldots, x_N]$$, 각 $$x_i \in \mathbb{R}^{d_\text{model}}$$. token embedding(II)을 통해 원시 입력을 고정 차원 벡터로 변환한 것이다. 이 시점에서 각 토큰은 자기 자신만의 정보만 담고 있고, 아직 다른 토큰들을 "본" 적이 없다.
- **인코더 출력**: $$[e_1, e_2, \ldots, e_N]$$, 각 $$e_i \in \mathbb{R}^{d_\text{model}}$$. 형태는 입력과 같지만, 각 벡터가 시퀀스 전체 문맥을 담고 있다. 예를 들어 "나는 강가에서 배를 먹었다"에서 "배"에 해당하는 $$e_i$$ 는 앞뒤 문맥을 반영해 "과일"에 가까운 표현이 된다. 이 출력이 디코더의 cross-attention으로 전달된다.
- **디코더 입력**: $$[y_1, y_2, \ldots, y_M]$$, 각 $$y_j \in \mathbb{R}^{d_\text{model}}$$. 번역 task라면 지금까지 생성된 출력 단어들이 들어온다. 길이 $$M$$ 은 인코더 입력 $$N$$ 과 달라도 되는데, 입력 언어와 출력 언어의 문장 길이가 다를 수 있기 때문이다.
- **디코더 출력**: $$[o_1, o_2, \ldots, o_M]$$, 각 $$o_j \in \mathbb{R}^{d_\text{model}}$$. 이 벡터들을 최종적으로 어떻게 활용할지는 task에 따라 다르다. NLP 번역이라면 $$o_j$$ 에 선형 변환 $$W \in \mathbb{R}^{V \times d_\text{model}}$$ 을 적용해 어휘 크기 $$V$$ 차원의 logit 벡터를 만들고, 거기에 softmax를 취해 다음 단어의 확률 분포를 구한다. 이 과정으로 "I ate a pear by the river"를 한 단어씩 뽑아낸다.

이어지는 섹션에서는 입력 표현 방법(II), 핵심 계산 메커니즘(III-V), 그리고 전체 구조(VI) 순으로 설명한다.

## II. Token

NLP에서 먼저 제안된 개념이니, 문장을 예로 들어 설명하겠다.
예를 들어, 문장은 단어의 집합인 것처럼 자율주행에서 하나의 scene은 여러 요소들 (ego, obstacle, etc)의 집합이다.
문장 또는 scene을 구성하는 하나하나의 요소를 token이라는 이름으로 부른다.
각 token은 고정된 차원의 벡터인데, 단어 하나나 장애물의 8개 좌표를 모두 128차원 벡터로 바꾸는 식이다.
이렇게 원시 입력을 고정된 차원의 토큰으로 만드는 과정을 token embedding이라고 부른다.
보통 token embedding은 다음과 같은 방법을 사용한다.

### II.1. Lookup table

입력이 단어처럼 이산적인(discrete) 경우에 사용한다.
어휘(vocabulary)에 속하는 각 단어에 고유한 정수 ID를 부여하고,
$$V \times d_\text{model}$$ 크기의 학습 가능한 행렬 $$E$$ 를 준비한다 ( $$V$$ : 어휘 크기, $$d_\text{model}$$ : 토큰 벡터 차원).
단어 ID $$i$$ 에 해당하는 토큰 벡터는 단순히 $$E$$ 의 $$i$$ 번째 행 $$E_i \in \mathbb{R}^{d_\text{model}}$$ 이다.

### II.2. Linear projection

입력이 좌표나 센서 값처럼 연속적인(continuous) 경우에 사용한다.
원시 입력 벡터 $$x \in \mathbb{R}^n$$ 에 학습 가능한 가중치 행렬 $$W \in \mathbb{R}^{d_\text{model} \times n}$$ 과 편향 $$b \in \mathbb{R}^{d_\text{model}}$$ 를 적용하여 $$Wx + b \in \mathbb{R}^{d_\text{model}}$$ 로 변환한다.
PlanT처럼 자율주행 scene의 각 요소(ego, obstacle 등)를 토큰으로 사용할 때는 이 방식이 자주 쓰인다.
여기서 $$W$$ 와 $$b$$ 는 고정된 값이 아니라 다른 레이어의 가중치들과 마찬가지로 역전파(backpropagation)를 통해 학습되는 파라미터임에 주의하자.

## III. Self-Attention

이제 트랜스포머가 입력 시퀀스를 처리해 출력 시퀀스를 만드는 핵심 메커니즘을 살펴보자.
그 핵심 메커니즘은 **self-attention**이고, QKV (Query, Key, Value) 세 가지 벡터를 중심으로 동작한다.
뭐, 개념적으로는 query와 유사한 key를 찾고 그 key에 해당하는 value를 돌려주는 자료구조 정도로 이해하면 된다.
물론 개념적인 설명만으로는 딱히 도움될 게 없으므로 좀 더 깊게 설명하겠다.

### III.1. Q, K, V 생성

앞서 token embedding을 통해 모든 토큰을 $$d_\text{model}$$ 차원의 벡터로 표현했다.
이제 각 토큰 벡터 $$x \in \mathbb{R}^{d_\text{model}}$$ 를 세 개의 서로 다른 선형 변환을 통해 Query, Key, Value 벡터로 변환한다.

$$
q = W_Q x, \quad k = W_K x, \quad v = W_V x
$$

여기서 $$W_Q, W_K, W_V \in \mathbb{R}^{d_k \times d_\text{model}}$$ 는 각각 학습 가능한 가중치 행렬이고, 결과적으로 $$q, k, v \in \mathbb{R}^{d_k}$$ 를 얻는다.
II 섹션의 Linear projection과 마찬가지로, $$W_Q, W_K, W_V$$ 모두 역전파를 통해 학습된다.

{: .note }
> 이론적으로 Q/K의 차원과 V의 차원은 달라도 무방하지만, 원래 논문과 대부분의 구현(PyTorch 포함)에서는 Q, K, V 차원을 모두 $$d_k$$ 로 통일한다. 이 문서도 그 관례를 따른다.

직관적으로는 이렇게 이해하면 된다.

- **Query**: 현재 토큰이 다른 토큰들에게 던지는 질문. "나는 어떤 정보가 필요한가?"
- **Key**: 현재 토큰이 다른 토큰들의 질문에 답하기 위한 자기소개. "나는 이런 정보를 갖고 있다."
- **Value**: 질문에 답하기로 결정됐을 때 실제로 전달하는 정보. "내가 전달할 내용은 이것이다."

### III.2. Attention score

시퀀스에 $$N$$ 개의 토큰이 있다고 하자.
토큰 $$i$$ 의 Query $$q_i$$ 와 토큰 $$j$$ 의 Key $$k_j$$ 의 내적(dot product)으로 토큰 $$i$$ 가 토큰 $$j$$ 에 얼마나 주목해야 하는지를 나타내는 점수를 계산한다.

$$
\text{score}(i, j) = \frac{q_i \cdot k_j}{\sqrt{d_k}}
$$

$$\sqrt{d_k}$$ 로 나누는 이유는 $$d_k$$ 가 커질수록 내적값의 분산이 커져 softmax가 극단적으로 포화되는 현상을 방지하기 위함이다.
이 점수를 모든 토큰 쌍에 대해 계산한 뒤 softmax를 적용하면 attention weight $$\alpha_{ij}$$ 를 얻는다.

$$
\alpha_{ij} = \text{softmax}_j \left( \text{score}(i, j) \right) = \frac{\exp(\text{score}(i, j))}{\sum_{j'} \exp(\text{score}(i, j'))}
$$

$$\alpha_{ij}$$ 는 토큰 $$i$$ 가 토큰 $$j$$ 에 부여하는 가중치로, 모든 $$j$$ 에 대해 합산하면 1이 된다.
마지막으로, 토큰 $$i$$ 의 출력 벡터는 각 토큰의 Value를 attention weight로 가중합하여 구한다.

$$
o_i = \sum_{j=1}^{N} \alpha_{ij} v_j
$$

self-attention은 "각 토큰이 시퀀스 내 모든 토큰을 참조하여 자신을 새롭게 표현"하는 연산이다.
token embedding이 각 토큰을 독립적으로 표현했다면, self-attention은 시퀀스 내 토큰 간의 관계를 반영한 표현으로 갱신한다.

## IV. Multi-head Attention

III 섹션의 self-attention은 토큰마다 Q, K, V를 하나씩 만들어 attention을 계산했다.
**Multi-head attention**은 이 과정을 $$h$$ 번 병렬로 수행한다.

각 "헤드"는 독립적인 가중치 행렬 $$W_Q^{(i)}, W_K^{(i)}, W_V^{(i)}$$ 를 갖고, 전체 입력 $$X \in \mathbb{R}^{N \times d_\text{model}}$$ 을 받아 독립적으로 attention을 계산한다.
단, 각 헤드의 **출력** 차원은 $$d_k = d_\text{model} / h$$ 로 설정한다.
이렇게 하면 헤드를 늘려도 전체 계산량이 단일 헤드 ( $$d_k = d_\text{model}$$ ) 와 거의 같게 유지된다. $$h \cdot d_k = d_\text{model}$$ 이기 때문이다.

$$h$$ 개 헤드의 출력 $$o^{(1)}, \ldots, o^{(h)} \in \mathbb{R}^{N \times d_k}$$ 를 이어 붙이면 $$\mathbb{R}^{N \times d_\text{model}}$$ 이 되고, 선형 변환 $$W_O \in \mathbb{R}^{d_\text{model} \times d_\text{model}}$$ 로 최종 출력을 만든다.

$$
\text{MultiHead}(X) = \text{Concat}(o^{(1)}, \ldots, o^{(h)}) W_O
$$

헤드마다 서로 다른 "관점"으로 토큰 간 관계를 볼 수 있다는 것이 핵심이다.
예를 들어, 하나의 헤드는 문법적 관계를, 다른 헤드는 의미적 유사성을 잡아내는 식으로 분업이 일어난다.

## V. Feed-Forward Network

Self-attention은 시퀀스 내 토큰 간의 관계를 포착하는 데 특화되어 있지만, 본질적으로 Value의 가중합이라는 **선형 연산**이다.
**Feed-forward network (FFN)**은 이 선형성을 보완하는 역할을 한다.
Self-attention이 "어떤 토큰을 얼마나 참조할지"를 결정했다면, FFN은 그 결과를 바탕으로 각 토큰을 **비선형적으로 변환**하는 단계다.
또한 FFN은 각 토큰에 **독립적으로** 적용된다. 즉, 토큰 간 상호작용은 없고 오직 해당 토큰의 표현만 변환한다.
구조는 은닉층 하나짜리 MLP다.

$$
\text{FFN}(x) = W_2 \text{ReLU}(W_1 x + b_1) + b_2
$$

여기서 $$W_1 \in \mathbb{R}^{d_\text{ff} \times d_\text{model}}$$ , $$W_2 \in \mathbb{R}^{d_\text{model} \times d_\text{ff}}$$ 이고, $$d_\text{ff}$$ 는 은닉층의 차원이다.
$$d_\text{ff}$$ 는 보통 $$d_\text{model}$$ 의 4배로 설정한다. 차원을 한번 크게 늘렸다가 다시 줄이는 구조로, 이 구간에서 비선형 변환이 일어난다.
입출력 차원은 모두 $$d_\text{model}$$ 로 동일하다.

## VI. Encoder & Decoder

앞선 섹션들에서 self-attention(III), multi-head attention(IV), FFN(V)이라는 세 가지 부품을 살펴봤다.
트랜스포머는 이 부품들을 조합한 레이어를 여러 겹 쌓아 **인코더**와 **디코더**를 구성한다.

역할을 한 문장으로 먼저 정리하면 이렇다.

- **인코더**: 입력 시퀀스를 읽어서 각 토큰을 문맥이 반영된 벡터로 변환한다. "입력을 이해하는" 파트다.
- **디코더**: 인코더가 만든 표현을 참조하면서, 출력 시퀀스를 한 토큰씩 생성한다. "출력을 만드는" 파트다.

번역을 예로 들면, 인코더는 한국어 문장 전체를 읽고 각 단어의 의미를 문맥에 맞게 압축한다.
디코더는 그 압축된 정보를 보면서 영어 단어를 하나씩 골라 출력한다.

### VI.1. Encoder

인코더 한 층(layer)은 다음 두 연산을 순서대로 수행한다.

1. **Multi-head self-attention**: 입력 시퀀스 내 토큰끼리 서로 참조해, 각 토큰의 표현에 문맥 정보를 녹인다.
2. **FFN**: 각 토큰을 독립적으로 비선형 변환한다.

각 연산 뒤에는 잔차 연결(residual connection)과 layer normalization이 붙어 학습을 안정시킨다.

{: .note }
> - **Residual connection**: 층을 통과한 결과에 입력을 그냥 더해준다. 즉 출력 = 입력 + 층이 계산한 것. 층을 수십 겹 쌓으면 gradient가 역전파 도중 소실되는 문제가 생기는데, 입력을 바로 더해주면 gradient가 그 경로를 타고 무사히 흘러가므로 깊은 네트워크를 학습할 수 있다.
> - **Layer normalization**: 각 토큰의 벡터값들이 너무 크거나 작아지면 학습이 불안정해진다. Layer normalization은 한 토큰의 값들을 평균 0, 분산 1 근처로 스케일을 맞춰주는 정규화 단계다.

이 한 층을 여러 겹 쌓으면 토큰들이 층마다 점점 더 풍부한 문맥 정보를 담게 된다.
차원 흐름을 정리하면 다음과 같다.

- **층 입력**: $$[x_1, \ldots, x_N]$$, 각 $$x_i \in \mathbb{R}^{d_\text{model}}$$.
- **Multi-head attention 출력**: $$[a_1, \ldots, a_N]$$, 각 $$a_i \in \mathbb{R}^{d_\text{model}}$$ — $$W_O$$ 투영 덕분에 입력과 차원이 같다.
- **FFN 출력 (= 층 출력)**: $$[o_1, \ldots, o_N]$$, 각 $$o_i \in \mathbb{R}^{d_\text{model}}$$ — FFN도 입출력 차원이 동일하다.

결국 인코더 한 층의 입출력 차원은 모두 $$(N, d_\text{model})$$ 이다.
매 층의 출력이 다음 층의 입력으로 그대로 들어가도 차원이 유지되기 때문에, 층을 몇 겹 쌓아도 문제없다.

### VI.2. Decoder

디코더는 인코더와 달리 두 가지를 동시에 참조해야 한다.
하나는 지금까지 자신이 생성한 출력 토큰들이고, 다른 하나는 인코더가 만들어 준 입력 표현이다.
이 두 가지를 모두 반영하기 위해 디코더 한 층은 세 단계로 구성된다.

1. **Masked multi-head self-attention**: 지금까지 생성된 출력 토큰끼리 서로 참조한다. 단, 미래 위치는 마스킹해 보지 못하게 한다. 아직 생성하지 않은 토큰을 미리 참조하면 시험지를 보고 시험을 치는 격이라 의미가 없다.
2. **Cross-attention**: 디코더의 각 토큰이 인코더 출력 전체를 참조한다. 여기서 Query는 디코더 토큰에서, Key와 Value는 인코더 최종 출력에서 가져온다. 인코더와 디코더를 이어주는 핵심 단계다.
3. **FFN**: 각 토큰을 독립적으로 비선형 변환한다.

인코더 섹션과 마찬가지로 각 단계 뒤에 residual connection과 layer normalization이 붙는다.

번역 예시로 구체적으로 보면 이렇다.
인코더는 "나는 강가에서 배를 먹었다"를 읽어 각 단어의 문맥 표현을 만들었다.
디코더는 지금까지 "I ate a"를 생성한 상태에서 다음 단어를 고른다.

- **1단계 (Masked self-attention)**: "I", "ate", "a" 세 토큰끼리 서로 참조해, 지금까지의 출력 문맥을 파악한다. "a" 뒤에 명사가 와야 한다는 문법적 흐름을 이 단계에서 잡아낸다.
- **2단계 (Cross-attention)**: "a" 토큰의 Query가 인코더 출력 전체를 훑으며, "배"에 해당하는 인코더 표현에 높은 attention weight를 부여한다.
- **3단계 (FFN)**: 각 토큰을 비선형 변환해 최종 표현을 완성한다. 이 출력이 선형 변환 + softmax를 거쳐 "pear"라는 단어를 선택하게 된다.

차원 흐름을 정리하면 다음과 같다 (디코더 입력 길이 $$M$$, 인코더 입력 길이 $$N$$, $$M \neq N$$ 이어도 된다).

- **층 입력**: $$(M, d_\text{model})$$.
- **Masked self-attention 출력**: $$(M, d_\text{model})$$.
- **Cross-attention**: Query $$(M, d_\text{model})$$, Key/Value는 인코더 최종 출력 $$(N, d_\text{model})$$에서 가져온다. 출력은 $$(M, d_\text{model})$$.
- **FFN 출력 (= 층 출력)**: $$(M, d_\text{model})$$.

세 단계 모두 $$d_\text{model}$$ 차원을 유지하므로, 층을 몇 겹 쌓아도 차원이 흐트러지지 않는다.

### VI.3. 파라미터 정리

지금까지 설명한 내용을 `nn.Transformer` 파라미터에 매핑하면 다음과 같다.

| 파라미터 | 의미 | 관련 섹션 |
|---|---|---|
| `d_model` | 모든 토큰 벡터의 차원. 인코더/디코더 전반에 걸쳐 고정. | II, VI.1 |
| `nhead` | Multi-head attention의 헤드 수 $$h$$. | IV |
| `dim_feedforward` | FFN 은닉층의 차원 $$d_\text{ff}$$. | V |
| `num_encoder_layers` | 인코더 층의 수. | VI.1 |
| `num_decoder_layers` | 디코더 층의 수. | VI.2 |


<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
