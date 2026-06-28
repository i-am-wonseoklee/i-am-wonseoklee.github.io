---
title: "GRU Decoder"
layout: default
nav_order: 3
parent: "Plan T"
grand_parent: "Reproducing Papers"
permalink: /docs/reproducing-papers/00-plan-t/02-gru-decoder
---

# GRU Decoder

## TOC
{: .no_toc }

1. TOC
{:toc}


**Keywords:** `GRU`{: .label }, `decoder`{: .label }

{: .note }
> 이 챕터부터 이어질 몇 개의 후속 챕터는 `PlanT` 논문을 수월하게 이해하기 위해 알고 있어야 할 내용들을 정리한다.
> 물론, 이 내용들은 필자의 주관과 경험에 따라 선정되었음을 참고하자.
> 즉, 자명해보여도 필자가 모르던 것이면 정리할 것이고, 어려워보여도 필자가 알던 것이면 정리하지 않을 것이다.

앞선 챕터에서 트랜스포머 인코더를 살펴봤다.
인코더는 driving scene을 구성하는 토큰들을 받아 문맥이 반영된 벡터들을 내놓는다.
그런데 `PlanT`의 목표는 결국 미래 주행 경로, 즉 waypoints를 예측하는 것이다.
인코더가 내놓은 벡터들을 어떻게 waypoints 시퀀스로 바꾸냐는 문제가 남아있는 것이다.
그 역할을 맡은 것이 **GRU 디코더**다.
이번 챕터에서는 GRU가 무엇인지, 디코더로서 어떻게 동작하는지 설명하겠다.

## I. Overview

필자는 GRU 디코더를 이해하기 위해 여러 웹 페이지와 동영상 강의를 찾아보았다.
모두들 RNN -> LSTM -> GRU 순으로 설명을 진행하고 있었다.
결론만 알고 싶었던 필자로서는 몹시 답답한 상황이었는데, 어느 정도 윤곽을 잡고 보니 그 순서를 거치지 않고는 GRU를 설명하기 어렵다는 것을 깨달았다.
그래서 필자도 동일한 순서로 설명한다.
다만 LSTM은 그 자체로 매우 복잡하므로, 설명에서 제외하고 GRU로 직행할 것이다.

## II. RNN과 그 한계

RNN은 입력을 순차적으로 처리하되, 이전 스텝의 hidden state와 현재 스텝의 입력이 함께 이번 hidden state를 결정하는 구조다.
아래 그림은 이를 나타내고 있다.

![fig1](/docs/reproducing-papers/00-plan-t/02-gru-decoder/assets/fig1_rnn.png)

$$
\mathbf{h}_t = \tanh(\mathbf{W}_{hh}\mathbf{h}_{t-1} + \mathbf{W}_{xh}\mathbf{x}_t + \mathbf{b}_h)
$$

$$
\mathbf{y}_t = \sigma(\mathbf{W}_{hy}\mathbf{h}_t + \mathbf{b}_y)
$$

$$\mathbf{x}_t$$는 현재 스텝의 입력, $$\mathbf{h}_t$$는 지금까지의 정보를 압축한 메모리, $$\mathbf{y}_t$$는 현재 스텝의 출력이다.
직전 메모리 $$\mathbf{h}_{t-1}$$과 현재 입력 $$\mathbf{x}_t$$를 합쳐 새 메모리 $$\mathbf{h}_t$$를 만들고, 이로부터 출력 $$\mathbf{y}_t$$를 계산하는 구조다.

그림에서 볼 수 있듯이 순차적으로 동작하므로 시퀀스 형태의 입출력을 다루기에 적절한 구조이다.
하지만 문제는 이 구조를 학습할 때 생긴다.
먼저 로스 $$L$$을 정의해보자.
보통 매 스텝마다 출력이 있는 태스크에서는 (`PlanT`의 waypoint 예측처럼) 각 스텝의 로스를 모두 더해 전체 로스를 정의한다.

$$
L = L_1(\mathbf{h}_1) + L_2(\mathbf{h}_2) + \cdots + L_T(\mathbf{h}_T)
$$

이제 $$\mathbf{W}_{hh}$$의 gradient를 구해보자.
RNN에서 $$\mathbf{W}_{hh}$$는 모든 스텝에서 **공유**되므로, 계산 그래프에서 $$\mathbf{W}_{hh}$$로부터 $$\mathbf{h}_1, \mathbf{h}_2, \ldots, \mathbf{h}_T$$로 가지가 T개 뻗어 있다.
가지가 갈라지는 노드의 gradient는 각 가지의 gradient를 더한 것이므로:

$$
\frac{\partial L}{\partial \mathbf{W}_{hh}}
= \underbrace{\frac{\partial L}{\partial \mathbf{h}_1} \frac{\partial \mathbf{h}_1}{\partial \mathbf{W}_{hh}}}_{\mathbf{h}_1 \text{ 가지}}
+ \underbrace{\frac{\partial L}{\partial \mathbf{h}_2} \frac{\partial \mathbf{h}_2}{\partial \mathbf{W}_{hh}}}_{\mathbf{h}_2 \text{ 가지}}
+ \cdots
+ \underbrace{\frac{\partial L}{\partial \mathbf{h}_T} \frac{\partial \mathbf{h}_T}{\partial \mathbf{W}_{hh}}}_{\mathbf{h}_T \text{ 가지}}
$$

그런데 각 항의 $$\frac{\partial L}{\partial \mathbf{h}_t}$$는 생각보다 단순하지 않다.
$$\frac{\partial L}{\partial \mathbf{h}_t}$$는 "$$\mathbf{h}_t$$가 조금 바뀌면 $$L$$ 전체가 얼마나 바뀌는가"인데, $$\mathbf{h}_t$$는 $$L$$에 두 경로로 영향을 준다.

- **직접**: $$\mathbf{h}_t$$는 그 스텝의 로스 $$L_t$$에 바로 영향을 준다.
- **간접**: $$\mathbf{h}_t$$는 forward 계산에서 $$\mathbf{h}_{t+1}$$의 입력이기도 하다. $$\mathbf{h}_{t+1}$$이 바뀌면 $$L_{t+1}$$도 바뀌고, 나아가 $$\mathbf{h}_{t+2}$$도 바뀌어 $$L_{t+2}$$도 바뀐다. 이 연쇄는 마지막 스텝 $$T$$까지 이어진다.

예를 들어, $$T=3$$일 때 $$\frac{\partial L}{\partial \mathbf{h}_1}$$을 풀어 쓰면:

$$
\frac{\partial L}{\partial \mathbf{h}_1}
= \underbrace{\frac{\partial L_1}{\partial \mathbf{h}_1}}_{직접}
+ \underbrace{\frac{\partial L_2}{\partial \mathbf{h}_2} \frac{\partial \mathbf{h}_2}{\partial \mathbf{h}_1}}_{\mathbf{h}_2 \text{ 경유}}
+ \underbrace{\frac{\partial L_3}{\partial \mathbf{h}_3} \frac{\partial \mathbf{h}_3}{\partial \mathbf{h}_2} \frac{\partial \mathbf{h}_2}{\partial \mathbf{h}_1}}_{\mathbf{h}_2 \to \mathbf{h}_3 \text{ 경유}}
$$

$$
\frac{\partial \mathbf{h}_t}{\partial \mathbf{h}_{t-1}} = \mathrm{diag}(1 - \mathbf{h}_t \odot \mathbf{h}_t) \cdot \mathbf{W}_{hh}
$$

$$\mathrm{diag}(1 - \mathbf{h}_t \odot \mathbf{h}_t)$$는 $$\tanh$$의 미분으로, 각 원소의 값이 항상 $$(0, 1)$$ 범위에 속한다.
위의 식 전개를 살펴보면 초반 스텝일수록 이 미분이 더 많이 곱해진다는 사실을 알 수 있다.
예를 들어, 위의 $$T=3$$ 예시에서 $$\frac{\partial L}{\partial \mathbf{h}_1}$$의 마지막 항에는 $$\frac{\partial \mathbf{h}_t}{\partial \mathbf{h}_{t-1}}$$이 두 번 곱해지지만, $$\frac{\partial L}{\partial \mathbf{h}_2}$$에는 한 번만 곱해진다.
각 원소가 $$(0, 1)$$ 사이의 값이므로, 곱할수록 gradient는 지수적으로 0에 가까워진다.
긴 시퀀스에서 초반 스텝의 gradient가 이렇게 소멸하는 현상을 **gradient vanishing**이라 부른다.
waypoint 예측처럼 먼 과거의 context를 참조해야 하는 태스크에서는 학습에 있어 치명적인 약점이다.

## III. GRU

GRU (Gated Recurrent Unit)는 이 gradient vanishing 문제를 완화하기 위해 제안된 구조다.
핵심 아이디어는 정보를 얼마나 기억하고 얼마나 갱신할지를 **게이트(gate)**라는 메커니즘으로 학습 가능하게 만드는 것이다.
LSTM보다 단순하고 파라미터도 적으면서 성능은 비슷한 경우가 많아, `PlanT`처럼 디코더에 쓰기 딱 좋다.

![fig2](/docs/reproducing-papers/00-plan-t/02-gru-decoder/assets/fig2_gru.jpg)

그림에 보이듯이 GRU에는 두 종류의 게이트가 있다 (주황색).
필자의 생각에는 "게이트"라는 설명이 초반 이해를 조금 어렵게 하는 것 같다.
"게이트"는 단순히 벡터들일 뿐이니 어렵게 이해하지 않기를 바란다.
아래 기술할 내용의 핵심은 결국 $$\mathbf{h}_t$$의 계산 경로를 살짝 변형하여 상술한 vanishing gradient 문제를 해결하는 것이다.

### III.1. Reset Gate

$$
\mathbf{r}_t = \sigma(\mathbf{W}_r [\mathbf{h}_{t-1};\, \mathbf{x}_t] + \mathbf{b}_r)
$$

여기서 $$[\mathbf{h}_{t-1};\, \mathbf{x}_t]$$는 단순히 두 벡터를 이어 붙인 것(concatenation)이다.
각 항의 차원은 다음과 같다.

| 항                                        | 차원                          | 설명                  |
|-------------------------------------------|-------------------------------|-----------------------|
| $$\mathbf{h}_{t-1}$$                      | $$d_h$$                       | 직전 hidden state     |
| $$\mathbf{x}_t$$                          | $$d_x$$                       | 현재 입력             |
| $$[\mathbf{h}_{t-1};\, \mathbf{x}_t]$$    | $$d_h + d_x$$                 | concatenation 결과    |
| $$\mathbf{W}_r$$                          | $$d_h \times (d_h + d_x)$$    | 학습 파라미터         |
| $$\mathbf{b}_r$$                          | $$d_h$$                       | 학습 파라미터         |
| $$\mathbf{r}_t$$                          | $$d_h$$                       | reset gate 출력       |

$$\mathbf{W}_r$$의 출력 차원이 $$d_h$$인 이유는, 이후 단계에서 $$\mathbf{r}_t \odot \mathbf{h}_{t-1}$$처럼 hidden state와 element-wise 곱을 해야 하기 때문이다.
두 벡터의 차원이 같아야 element-wise 곱이 가능하므로, reset gate의 출력은 반드시 $$d_h$$여야 한다.

**reset gate** $$\mathbf{r}_t \in (0, 1)^{d_h}$$는 직전 hidden state의 **어느 부분을 잊을지**를 결정한다.
$$\mathbf{r}_t$$의 원소가 0에 가까울수록 해당 차원의 $$\mathbf{h}_{t-1}$$ 정보를 지운다.
reset gate 덕분에 GRU는 필요 없는 과거 정보를 선택적으로 폐기할 수 있다.

### III.2. Update Gate

$$
\mathbf{z}_t = \sigma(\mathbf{W}_z [\mathbf{h}_{t-1};\, \mathbf{x}_t] + \mathbf{b}_z)
$$

각 항의 차원은 reset gate와 동일하다.

| 항                                        | 차원                          | 설명                  |
|-------------------------------------------|-------------------------------|-----------------------|
| $$\mathbf{h}_{t-1}$$                      | $$d_h$$                       | 직전 hidden state     |
| $$\mathbf{x}_t$$                          | $$d_x$$                       | 현재 입력             |
| $$[\mathbf{h}_{t-1};\, \mathbf{x}_t]$$    | $$d_h + d_x$$                 | concatenation 결과    |
| $$\mathbf{W}_z$$                          | $$d_h \times (d_h + d_x)$$    | 학습 파라미터         |
| $$\mathbf{b}_z$$                          | $$d_h$$                       | 학습 파라미터         |
| $$\mathbf{z}_t$$                          | $$d_h$$                       | update gate 출력      |

$$\mathbf{W}_z$$의 출력 차원이 $$d_h$$인 이유도 reset gate와 같다.
이후 단계에서 $$(1 - \mathbf{z}_t) \odot \mathbf{h}_{t-1} + \mathbf{z}_t \odot \tilde{\mathbf{h}}_t$$처럼 $$\mathbf{h}_{t-1}$$, $$\tilde{\mathbf{h}}_t$$와 element-wise 연산을 해야 하므로, 차원이 $$d_h$$로 맞춰진다.

**update gate** $$\mathbf{z}_t \in (0, 1)^{d_h}$$는 **이전 hidden state를 얼마나 유지하고, 새 정보를 얼마나 반영할지**를 결정한다.
$$\mathbf{z}_t$$가 0이면 이전 상태를 그대로 유지하고, 1이면 완전히 새 정보로 교체하는 방향이다.

### III.3. Candidate Hidden State

$$
\tilde{\mathbf{h}}_t = \tanh(\mathbf{W}_h [\mathbf{r}_t \odot \mathbf{h}_{t-1};\, \mathbf{x}_t] + \mathbf{b}_h)
$$

각 항의 차원은 다음과 같다.

| 항                                                        | 차원                          | 설명                          |
|-----------------------------------------------------------|-------------------------------|-------------------------------|
| $$\mathbf{r}_t \odot \mathbf{h}_{t-1}$$                   | $$d_h$$                       | reset gate 적용 후 과거 정보  |
| $$\mathbf{x}_t$$                                          | $$d_x$$                       | 현재 입력                     |
| $$[\mathbf{r}_t \odot \mathbf{h}_{t-1};\, \mathbf{x}_t]$$ | $$d_h + d_x$$                 | concatenation 결과            |
| $$\mathbf{W}_h$$                                          | $$d_h \times (d_h + d_x)$$    | 학습 파라미터                 |
| $$\mathbf{b}_h$$                                          | $$d_h$$                       | 학습 파라미터                 |
| $$\tilde{\mathbf{h}}_t$$                                  | $$d_h$$                       | 후보 hidden state 출력        |

$$\mathbf{W}_h$$의 출력 차원이 $$d_h$$인 이유는, $$\tilde{\mathbf{h}}_t$$가 다음 단계에서 $$\mathbf{h}_{t-1}$$과 보간(interpolation)되어야 하기 때문이다.
두 벡터의 차원이 같아야 보간이 가능하므로, 후보 hidden state의 출력도 $$d_h$$여야 한다.

reset gate를 적용한 과거 정보 $$\mathbf{r}_t \odot \mathbf{h}_{t-1}$$와 현재 입력 $$\mathbf{x}_t$$를 합쳐 **후보 hidden state** $$\tilde{\mathbf{h}}_t$$를 만든다.
이름 그대로, 다음 hidden state가 될 **후보**다.
$$\odot$$ 는 element-wise 곱셈 (Hadamard product) 이다.

### III.4. Hidden State 갱신

$$
\mathbf{h}_t = (1 - \mathbf{z}_t) \odot \mathbf{h}_{t-1} + \mathbf{z}_t \odot \tilde{\mathbf{h}}_t
$$

update gate $$\mathbf{z}_t$$로 이전 hidden state와 후보 hidden state를 보간(interpolation)해 최종 $$\mathbf{h}_t$$를 계산한다.
이 식이 GRU의 핵심이다.
$$\mathbf{z}_t$$가 작으면 $$\mathbf{h}_{t-1}$$이 거의 그대로 살아남는다.
즉, **gradient가 $$\mathbf{h}_{t-1}$$을 통해 시퀀스를 거슬러 올라갈 수 있는 경로가 확보**되어 RNN에 비해 gradient vanishing이 크게 완화된다.

### III.5. GRU 요약

정리하면, GRU 한 스텝의 수식은 다음과 같다.

$$
\begin{aligned}
\mathbf{r}_t &= \sigma(\mathbf{W}_r [\mathbf{h}_{t-1};\, \mathbf{x}_t] + \mathbf{b}_r) \\
\mathbf{z}_t &= \sigma(\mathbf{W}_z [\mathbf{h}_{t-1};\, \mathbf{x}_t] + \mathbf{b}_z) \\
\tilde{\mathbf{h}}_t &= \tanh(\mathbf{W}_h [\mathbf{r}_t \odot \mathbf{h}_{t-1};\, \mathbf{x}_t] + \mathbf{b}_h) \\
\mathbf{h}_t &= (1 - \mathbf{z}_t) \odot \mathbf{h}_{t-1} + \mathbf{z}_t \odot \tilde{\mathbf{h}}_t
\end{aligned}
$$

## IV. 디코더로서의 GRU

이제 GRU의 계산 흐름은 이해했다.
이제 "디코더"라는 역할을 GRU에게 맡긴다는 게 구체적으로 무슨 뜻인지 짚어보자.
동작 흐름은 다음과 같다.

**Step 0: 초기화**

인코더에서 생성된 context 벡터 $$\mathbf{c}$$를 GRU의 **초기 hidden state**로 쓴다.

$$
\mathbf{h}_0 = \mathbf{c}
$$

이 시점에서 GRU의 메모리에는 "지금까지 입력에서 무엇을 봤는가"에 관한 정보가 압축되어 있다.

**Step 1 ~ T: 자기회귀 생성**

GRU를 $$T$$ 번 반복 실행하며 출력 시퀀스를 하나씩 생성한다.
각 스텝 $$t$$에서:

1. 이전 스텝에서 생성한 출력 $$\mathbf{y}_{t-1}$$를 현재 입력 $$\mathbf{x}_t$$로 사용한다.
   - 첫 스텝($$t=1$$)에는 태스크에 따라 시작 토큰이나 영벡터를 쓴다.
2. GRU 수식에 따라 $$\mathbf{h}_t = \text{GRU}(\mathbf{h}_{t-1}, \mathbf{x}_t)$$를 계산한다.
3. 선형 투영으로 $$\mathbf{h}_t$$에서 이번 스텝의 출력을 읽어낸다.

전체 흐름을 수식으로 정리하면 다음과 같다.

$$
\mathbf{h}_0 = \mathbf{c}, \quad \mathbf{h}_t = \text{GRU}(\mathbf{h}_{t-1},\, \mathbf{y}_{t-1}), \quad \mathbf{y}_t = \mathbf{W}_\text{out} \mathbf{h}_t
$$

출력을 생성할수록 GRU의 hidden state는 "여기까지 이렇게 왔다"는 경로 정보를 누적한다.
이 덕분에 각 스텝의 예측이 앞선 스텝들과 일관성을 유지한다.

## V. PyTorch 사용법

PyTorch에서 GRU는 `nn.GRU`로 제공된다.
디코더로 쓸 때는 한 스텝씩 직접 반복하는 방식이 자연스럽다.

```python
import torch
import torch.nn as nn

class GRUDecoder(nn.Module):
    def __init__(
        self,
        context_dim: int,  # context 벡터 차원
        input_dim: int,    # 각 스텝의 입력 차원 (d_x)
        hidden_dim: int,   # hidden state 차원 (d_h)
        output_dim: int,   # 각 스텝의 출력 차원
        seq_len: int,      # 생성할 시퀀스 길이 (T)
    ):
        super().__init__()
        self.seq_len = seq_len
        self.input_dim = input_dim
        self.gru = nn.GRU(
            input_size=input_dim,   # 각 스텝의 입력 차원 (d_x)
            hidden_size=hidden_dim, # hidden state 차원 (d_h)
            num_layers=1,
            batch_first=True,       # 입력 형태: (batch, seq, feature)
        )
        self.context_proj = nn.Linear(context_dim, hidden_dim)  # c → h_0
        self.out_proj = nn.Linear(hidden_dim, output_dim)       # h_t → y_t

    def forward(self, context: torch.Tensor) -> torch.Tensor:
        batch = context.size(0)
        h = self.context_proj(context).unsqueeze(0)                        # h_0: (1, batch, d_h)
        x = torch.zeros(batch, 1, self.input_dim, device=context.device)   # 시작 토큰: (batch, 1, d_x)

        outputs = []
        for _ in range(self.seq_len):
            out, h = self.gru(x, h)   # out: (batch, 1, d_h)
            y = self.out_proj(out)    # y:   (batch, 1, output_dim)
            outputs.append(y)
            x = y                    # 자기회귀: 이번 출력을 다음 입력으로

        return torch.cat(outputs, dim=1)  # (batch, seq_len, output_dim)

# context: batch_size=2, context_dim=256
context = torch.randn(2, 256)
decoder = GRUDecoder(context_dim=256, input_dim=16, hidden_dim=128, output_dim=16, seq_len=5)
out = decoder(context)  # 출력: (2, 5, 16)
```

파라미터와 앞서 설명한 개념의 대응을 정리하면 다음과 같다.

| 파라미터          | 의미                                                                              | 관련 섹션 |
|-------------------|-----------------------------------------------------------------------------------|-----------|
| `context_dim`     | context 벡터 $$\mathbf{c}$$ 의 차원.                                              | IV        |
| `input_dim`       | 각 스텝의 입력 차원.                                                              | IV        |
| `hidden_size`     | hidden state $$\mathbf{h}_t$$ 의 차원 $$d_h$$.                                    | III       |
| `output_dim`      | 각 스텝의 출력 차원.                                                              | IV        |
| `context_proj`    | context 벡터 $$\mathbf{c}$$ 를 $$\mathbf{h}_0$$ 로 변환하는 선형 투영.            | IV        |
| `out_proj`        | hidden state $$\mathbf{h}_t$$ 에서 출력 $$\mathbf{y}_t$$ 를 읽어내는 선형 투영.   | IV        |

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
