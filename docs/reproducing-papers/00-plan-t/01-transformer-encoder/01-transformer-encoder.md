---
title: "Transformer Encoder"
layout: default
nav_order: 2
parent: "Plan T"
grand_parent: "Reproducing Papers"
permalink: /docs/reproducing-papers/00-plan-t/01-transformer-encoder
---

# Transformer Encoder

## TOC
{: .no_toc }

1. TOC
{:toc}


**Keywords:** `transformer`{: .label }, `encoder`{: .label }

{: .note }
> 이 챕터부터 이어질 몇 개의 후속 챕터는 `PlanT` 논문을 수월하게 이해하기 위해 알고 있어야 할 내용들을 정리한다.
> 물론, 이 내용들은 필자의 주관과 경험에 따라 선정되었음을 참고하자.
> 즉, 자명해보여도 필자가 모르던 것이면 정리할 것이고, 어려워보여도 필자가 알던 것이면 정리하지 않을 것이다.

로보틱스건 NLP건 신호처리건, 요즘 논문 아무거나 집어 들면 절반은 (솔직히말해 절반 이상은) 트랜스포머 얘기다.
어떤 바람이 불어서 이러는 건지 모르겠지만, 필자가 공부 중인 `PlanT`도 어김없이 트랜스포머 인코더를 사용한다.
필자에게 트랜스포머란 오랫동안 옵티머스 프라임 한 명뿐이었는데, 이제 그 이름이 전혀 다른 무언가를 가리키게 됐다.
아는 게 옵티머스 프라임뿐이기에 좀 막막하지만, 차근차근 이해해보도록 하자.
단, 이 포스팅의 목적은 어디까지나 `PlanT`를 이해하기 위한 배경지식 전달이므로, **트랜스포머 전체가 아닌 인코더만을 다룰 것이다.**

## I. Overview

세부 내용에 들어가기 전에 큰 그림부터 잡아두자.
결론부터 말하자면, 인코더는 토큰이 들어가면 문맥이 반영된 벡터들이 나오는 **token-in-context-out** 블록이다.
이 설명이 다분히 추상적이었음을 부정할 길이 없다.
하지만, 달리 다르게 표현할 방도도 없다.
뒷부분을 다 읽고 여기로 다시 오면, 저절로 납득이 될 것이니 일단 가볍게 한번 읽어보도록 하자.
결국 벡터들을 넣으면 그 벡터끼리 영향을 주고 받은 상태의 다른 벡터들이 나온다는 것만 받아들이면 된다.

- **인코더 입력**: $$[\mathbf{x}_1, \mathbf{x}_2, \ldots, \mathbf{x}_N]$$, 각 $$\mathbf{x}_i \in \mathbb{R}^{d_\text{model}}$$.
  - 토큰 임베딩을 통해 원시 입력을 고정 차원 벡터로 변환한 것이다.
  - 각 토큰은 자기 자신의 정보만 담고 있으며, 옆 토큰이 존재하는지조차 모르는 상태다.
- **인코더 출력**: $$[\mathbf{e}_1, \mathbf{e}_2, \ldots, \mathbf{e}_N]$$, 각 $$\mathbf{e}_i \in \mathbb{R}^{d_\text{model}}$$.
  - 차원은 입력과 같지만, 각 벡터가 문맥을 반영한 표현으로 변경되어 있다.
  - 각 벡터는 이웃 토큰들의 정보를 어느 정도 흡수한 상태다.

이어지는 섹션에서는 입력 표현 방법 (II), 핵심 계산 방식 (III-V) 순으로 설명할 것이다.

## II. Token

토큰이란 시퀀스를 구성하는 하나하나의 요소다.
`PlanT`에서는 하나의 driving scene이 시퀀스가 되고, scene을 구성하는 각 요소 (ego route, 장애물 등) 가 각각 토큰이 된다.
각 토큰은 고정된 차원의 벡터로 표현되는데, 트랜스포머 인코더는 뭘 집어넣든 일단 이 형식으로 맞춰줘야 받아주는 까다로운 녀석이다.
원시 입력을 이 고정 차원 벡터로 변환하는 이 과정을 **토큰 임베딩 (token embedding)**이라고 부른다.

`PlanT`에서는 scene의 각 요소가 좌표나 속도 같은 연속적인 값이므로, **linear projection**을 사용한다.
이름만 무섭지 별건 아니다.
아래와 같이 원시 입력 벡터 $$\mathbf{x}_{raw} \in \mathbb{R}^n$$ 에 학습 가능한 행렬 $$\mathbf{W} \in \mathbb{R}^{d_\text{model} \times n}$$ 을 곱하고 편향 $$\mathbf{b} \in \mathbb{R}^{d_\text{model}}$$ 를 더해 토큰 임베딩 벡터를 만드는 것이다.
여기서 원시 입력의 타입별로 $$\mathbf{W}$$ 와 $$\mathbf{b}$$ 는 각각 정의되며 동일 타입의 원시 입력끼리는 공유하는 값임에 주의하자.

$$
\text{x}_{i} = \mathbf{W}_{\text{type of }i}\mathbf{x}_{raw} + \mathbf{b}_{\text{type of }i} \in \mathbb{R}^{d_\text{model}}
$$

![fig1](/docs/reproducing-papers/00-plan-t/01-transformer-encoder/assets/fig1_token_embedding.png)

## III. Self-Attention

이제 트랜스포머가 입력 토큰들을 처리해 출력 벡터들을 만드는 핵심 메커니즘을 살펴보자.
그 핵심 메커니즘은 **self-attention**이라 불리고, **QKV (Query, Key, Value)** 세 가지 벡터를 중심으로 동작한다.
개념적으로는 query와 유사한 key를 찾고 그 key에 해당하는 value를 돌려주는 key-value 자료구조 정도로 이해하면 된다.
물론 개념적인 설명만으로는 동작을 이해하는데 한계가 있으므로 이어지는 서브 섹션에서 좀 더 깊게 설명하겠다.

### III.1. Q, K, V 생성

앞서 토큰 임베딩을 통해 모든 토큰을 $$d_\text{model}$$ 차원의 벡터로 표현했다.
이제 각 토큰 벡터 $$\mathbf{x} \in \mathbb{R}^{d_\text{model}}$$ 를 세 개의 서로 다른 선형 변환을 통해 Query, Key, Value 벡터로 변환한다.
여기서 $$\mathbf{W}_{Q\text{, }K\text{, }V} \in \mathbb{R}^{d_k \times d_\text{model}}$$ 는 각각 학습 가능한 가중치 행렬이다.
이들을 임베딩된 토큰에 곱하여 $$\mathbf{q}, \mathbf{k}, \mathbf{v} \in \mathbb{R}^{d_k}$$ 를 얻는다.

$$
\mathbf{q} = \mathbf{W}_Q \mathbf{x}, \quad \mathbf{k} = \mathbf{W}_K \mathbf{x}, \quad \mathbf{v} = \mathbf{W}_V \mathbf{x}
$$

![fig2](/docs/reproducing-papers/00-plan-t/01-transformer-encoder/assets/fig2_qkv.png)

### III.2. Attention 스코어

인코더 입력이 총 $$N$$ 개의 토큰이고, 각 토큰의 $$\mathbf{q}$$, $$\mathbf{k}$$, $$\mathbf{v}$$ 를 구했다고 해보자.
근본적으로 이 다음 단계에서 하고 싶은 일은 토큰 $$i$$ 가 토큰 $$j$$ 에 얼마나 주목해야 하는지를 나타내는 attention score를 계산하는 것이다.
그리고 이 점수는 cosine similarity와 유사하게 토큰 $$i$$ 의 Query $$\mathbf{q}_i$$ 와 토큰 $$j$$ 의 Key $$\mathbf{k}_j$$ 의 내적으로 계산한다.

$$
\text{score}(i, j) = \frac{\mathbf{q}_i \cdot \mathbf{k}_j}{\sqrt{d_k}}
$$

{: .note }
> $$\sqrt{d_k}$$ 로 나누는 이유는 $$d_k$$ 가 커질수록 내적값의 분산이 커져 softmax가 극단적으로 포화되는 현상을 방지하기 위함이다.

이 점수를 모든 토큰 쌍에 대해 계산한 뒤 softmax를 적용하면 정규화된 attention score, 즉, attention weight $$\alpha_{ij}$$ 를 얻는다.

$$
\alpha_{ij} = \text{softmax}_j \left( \text{score}(i, j) \right) = \frac{\exp(\text{score}(i, j))}{\sum_{j'} \exp(\text{score}(i, j'))}
$$

마지막으로, 토큰 $$i$$ 의 인코딩 결과 (출력 벡터) 는 각 토큰의 Value를 attention weight로 아래와 같이 가중합하여 구한다.
조금 추상적으로 말하면, self-attention은 "각 토큰이 시퀀스 내 모든 토큰의 Value를 적절히 섞어 자신을 새롭게 표현"하는 연산이다.
이 "적절히 섞는" 과정에 기준이 되는 것이 곧 attention score이고.

$$
\mathbf{o}_i = \sum_{j=1}^{N} \alpha_{ij} \mathbf{v}_j
$$

### III.3. Vectorization

여기까지만 설명하면 마치 각 토큰별로 for-loop을 돌면서 attention 스코어를 계산하고 누적합하는 코드가 떠오를 것이다.
하지만, self-attention에서 수행하는 일은 전부 행렬 연산으로 깔끔하게 표현할 수 있다.

우선, 시퀀스의 모든 토큰 벡터를 행 방향으로 쌓아 행렬을 만든다.

$$
\mathbf{X} = \begin{bmatrix} \mathbf{x}_1^\top \\ \vdots \\ \mathbf{x}_N^\top \end{bmatrix} \in \mathbb{R}^{N \times d_\text{model}}
$$

그러면 Q, K, V를 토큰마다 따로 계산하는 대신, 행렬 하나로 한 번에 구할 수 있다.

$$
\mathbf{Q} = \mathbf{X}\mathbf{W}_Q^\top, \quad \mathbf{K} = \mathbf{X}\mathbf{W}_K^\top, \quad \mathbf{V} = \mathbf{X}\mathbf{W}_V^\top \quad \text{where } \mathbf{W}_Q, \mathbf{W}_K, \mathbf{W}_V \in \mathbb{R}^{d_k \times d_\text{model}}
$$

![fig3](/docs/reproducing-papers/00-plan-t/01-transformer-encoder/assets/fig3_vectorization.png)

다음으로, 모든 토큰 쌍의 attention 스코어도 행렬 곱 하나로 구한다.

$$
\mathbf{S} = \frac{\mathbf{Q}\mathbf{K}^\top}{\sqrt{d_k}} \in \mathbb{R}^{N \times N}
$$

$$\mathbf{S}_{ij}$$ 가 바로 III.2에서 정의한 $$\text{score}(i, j)$$ 다.
이 $$N$$ 개 값을 softmax로 정규화하면 합이 1인 가중치 분포, 즉 "토큰 $$i$$ 가 각 토큰을 얼마나 참조할지"가 된다.

$$
\mathbf{A} = \text{softmax}_\text{row}(\mathbf{S}) \in \mathbb{R}^{N \times N}
$$

$$\mathbf{A}_{ij} = \alpha_{ij}$$ 이고, III.2에서 정의한 그것과 같다.
마지막으로 $$\mathbf{A}$$ 와 $$\mathbf{V}$$ 를 곱하면 모든 토큰의 출력 벡터를 한 번에 얻는다.

$$
\mathbf{O} = \mathbf{A}\mathbf{V} \in \mathbb{R}^{N \times d_k}
$$

정리하면, self-attention 전체를 다음 한 줄로 쓸 수 있다.

$$
\text{Attention}(\mathbf{Q}, \mathbf{K}, \mathbf{V}) = \text{softmax}\!\left(\frac{\mathbf{Q}\mathbf{K}^\top}{\sqrt{d_k}}\right)\mathbf{V}
$$

이것이 바로 그 유명한 "Attention is All You Need"에 등장하는 바로 그 수식이다.

## IV. Multi-head Attention

III 섹션의 self-attention은 단일의 $$\mathbf{W}_Q, \mathbf{W}_K, \mathbf{W}_V$$ 로 attention을 한 번 계산했다.
**Multi-head attention**은 쉽게 말하면 이 가중치 행렬을 $$h$$ 쌍 사용하겠다는 것이다.

각 헤드 $$i$$ 는 독립적인 가중치 행렬 $$\mathbf{W}_Q^{(i)}, \mathbf{W}_K^{(i)}, \mathbf{W}_V^{(i)}$$ 를 갖고, 동일한 입력 $$\mathbf{X}$$ 로부터 독립적으로 attention을 계산한다.
이때 각 헤드의 투영 차원을 $$d_k = d_\text{model} / h$$ 로 설정한다.
결국 $$d_\text{model}$$ 차원을 $$h$$ 개 헤드에 균등하게 나눠주는 것으로, $$\mathbf{W}_Q^{(i)}, \mathbf{W}_K^{(i)}, \mathbf{W}_V^{(i)} \in \mathbb{R}^{d_k \times d_\text{model}}$$ 이고 각 헤드의 출력 $$\mathbf{O}^{(i)} \in \mathbb{R}^{N \times d_k}$$ 다.
이렇게 하면 헤드가 늘어나도 전체 파라미터 수와 연산량이 단일 헤드( $$d_k = d_\text{model}$$ )와 거의 같게 유지된다.

$$h$$ 개 헤드의 출력 $$\mathbf{O}^{(1)}, \ldots, \mathbf{O}^{(h)} \in \mathbb{R}^{N \times d_k}$$ 를 열 방향으로 이어 붙이면 $$(N \times d_\text{model})$$ 이 된다.
이 시점에서 각 헤드의 정보는 그냥 나란히 쌓여 있을 뿐, 헤드 간 상호작용이 없다.
$$\mathbf{W}_O \in \mathbb{R}^{d_\text{model} \times d_\text{model}}$$ 는 이 헤드별 출력을 **서로 섞어주는 학습 가능한 선형 변환**으로, 여기서 비로소 헤드들의 정보가 통합된다.

$$
\text{MultiHead}(\mathbf{X}) = \text{Concat}(\mathbf{O}^{(1)}, \ldots, \mathbf{O}^{(h)}) \mathbf{W}_O \in \mathbb{R}^{N \times d_\text{model}}
$$

핵심은 헤드마다 서로 다른 "관점"으로 토큰 간 관계를 볼 수 있다는 점이다.
하나의 헤드가 잡아내지 못한 관계를 다른 헤드가 보완하는 식으로 분업이 일어난다.

## V. Feed-Forward Network

Self-attention은 본질적으로 Value의 가중합이라는 **선형 연산**이다.
**Feed-forward network (FFN)**은 이 선형성을 보완하기 위해 각 토큰을 **비선형적으로 변환**하는 단계다.
FFN은 self-attention 출력 토큰에 **독립적으로** 적용된다.
구조는 단순히 은닉층 하나짜리 MLP다.

$$
\text{FFN}(\mathbf{x}) = \mathbf{W}_2 \, \text{ReLU}(\mathbf{W}_1 \mathbf{x} + \mathbf{b}_1) + \mathbf{b}_2
$$

여기서 $$\mathbf{W}_1 \in \mathbb{R}^{d_\text{ff} \times d_\text{model}}$$, $$\mathbf{W}_2 \in \mathbb{R}^{d_\text{model} \times d_\text{ff}}$$ 이고, $$d_\text{ff}$$ 는 은닉층 차원으로 보통 $$4 \, d_\text{model}$$ 로 설정한다.
차원을 한 번 크게 늘렸다가 다시 줄이는 구조로, 이 구간에서 비선형 변환이 일어난다.
입출력 차원은 모두 $$d_\text{model}$$ 로 동일하다.

## VI. 인코더 레이어

앞선 섹션들에서 multi-head attention(IV)과 FFN(V)이라는 두 가지 부품을 살펴봤다.
인코더 한 층(layer)은 이 부품들을 다음 순서로 조합한다.

1. **Multi-head self-attention**: 입력 시퀀스 내 토큰끼리 서로 참조해 각 토큰의 표현에 문맥 정보를 녹인다.
2. **FFN**: 각 토큰을 독립적으로 비선형 변환한다.

각 연산 뒤에는 잔차 연결(residual connection)과 layer normalization이 붙어 학습을 안정시킨다.

{: .note }
> **잔차 연결 (residual connection)**: 층을 통과한 결과에 입력을 그대로 더한다. 즉 출력 = 입력 + 층이 계산한 것. 층을 수십 겹 쌓으면 gradient가 역전파 도중 소실되는 문제가 생기는데, 입력을 바로 더해주면 gradient가 그 경로를 타고 흘러가므로 깊은 네트워크를 학습할 수 있다.

{: .note }
> **Layer normalization**: 각 토큰의 벡터값들이 너무 크거나 작아지면 학습이 불안정해진다. 한 토큰의 값들을 평균 0, 분산 1 근처로 정규화하는 단계다.

차원 흐름을 정리하면 다음과 같다.

- **층 입력**: $$(N,\, d_\text{model})$$
- **Multi-head attention 출력**: $$(N,\, d_\text{model})$$, $$\mathbf{W}_O$$ 투영 덕분에 입력과 차원이 같다.
- **FFN 출력 (= 층 출력)**: $$(N,\, d_\text{model})$$, FFN도 입출력 차원이 동일하다.

이 한 층을 $$L$$ 겹 쌓으면 토큰들이 층마다 점점 더 풍부한 문맥 정보를 담게 된다.
매 층의 입출력 차원이 $$(N, d_\text{model})$$ 로 동일하므로, 몇 겹을 쌓아도 차원이 흐트러지지 않는다.

## VII. PyTorch 사용법

PyTorch에서는 인코더 한 층을 `nn.TransformerEncoderLayer`로, 이를 $$L$$ 겹 쌓은 인코더 전체를 `nn.TransformerEncoder`로 제공한다.

```python
import torch
import torch.nn as nn

encoder_layer = nn.TransformerEncoderLayer(
    d_model=256,          # 토큰 벡터 차원 (d_model)
    nhead=8,              # 헤드 수 h, d_model은 nhead의 배수여야 함 → d_k = 32
    dim_feedforward=1024, # FFN 은닉층 차원 (d_ff)
)

encoder = nn.TransformerEncoder(encoder_layer, num_layers=6)

# 입력: batch_size=2, seq_len=10, d_model=256
x = torch.randn(2, 10, 256)
out = encoder(x)  # 출력: (2, 10, 256)
```

파라미터와 앞서 설명한 개념의 대응을 정리하면 다음과 같다.

| 파라미터          | 의미                                                        | 관련 섹션 |
|-------------------|-------------------------------------------------------------|-----------|
| `d_model`         | 토큰 벡터 차원 $$d_\text{model}$$. 인코더 전반에 걸쳐 고정. | II, VI    |
| `nhead`           | 헤드 수 $$h$$. `d_model / nhead`가 헤드당 차원 $$d_k$$.     | IV        |
| `dim_feedforward` | FFN 은닉층 차원 $$d_\text{ff}$$.                            | V         |
| `num_layers`      | 인코더 층 수 $$L$$.                                         | VI        |

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
