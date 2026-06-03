---
title: "Main Contribution"
layout: default
nav_order: 5
parent: "Plan T"
grand_parent: "Reproducing Papers"
permalink: /docs/reproducing-papers/00-plan-t/04-main-contribution
---

# Main Contribution

**Keywords:** `plan t`{: .label }

이 포스팅에서는 본격적으로 `PlanT`를 설명한다.
앞선 3개의 preliminary 포스팅을 잘 읽었다면 크게 어렵지 않을 것이다.

## I. Overview

우선 `PlanT`는 임의의 시점 $$t$$에 아래와 같이 구성된 driving scene을 받는 것부터 시작된다.

![fig1](/docs/reproducing-papers/00-plan-t/04-main-contribution/assets/fig1_scene.png)

- **Ego**: Ego vehicle을 나타낸다. 이후에 기술할 모든 obstacle, route는 ego frame에서 표현되므로 ego vehicle에 관련한 정보가 별도로 모델 입력으로 들어가지는 않는다. 다만, 이해를 돕기 위해 표시했다.
- **Obstacle**: Ego frame에서 oriented bounding box로 표현되는 주변 obstacle들이다. 속도($$z_{i,t}$$), 위치($$x_{i,t}, y_{i,t}$$), 방향($$\phi_{i,t}$$), 크기($$w_{i,t}, h_{i,t}$$)의 6개 속성으로 구성된 벡터로 표현된다.
- **Traffic light**: Ego vehicle이 당장 신경써야 하는 신호등으로, $$l_t \in \{\text{green}, \text{red}\}$$의 binary flag로 표현된다. 중요한 점은 traffic light는 obstacle, route와 달리 **토큰으로 임베딩되지 않는다**는 것이다. 대신, 트랜스포머가 출력한 `[CLS]` 벡터에 직접 concatenate되어 GRU 디코더의 초기 hidden state로 전달된다.
- **Route**: 사실 이해하기 가장 까다로운 녀석인데, ego vehicle이 따라가야 할 route를 oriented bounding box 형태로 표현해 놓은 것이다. 자세한 내용은 세부 섹션에서 다룬다.

## II. Tokenization

앞서 Overview에서 obstacle과 route만이 트랜스포머의 입력으로 들어간다고 설명했다.
`PlanT`는 서로 다른 종류의 객체를 통일된 형식으로 처리하기 위해, 모든 객체 $$o_{i,t}$$를 **6개의 속성**으로 구성된 벡터로 표현한다.

$$
o_{i,t} = \{z_{i,t},\; x_{i,t},\; y_{i,t},\; \phi_{i,t},\; w_{i,t},\; h_{i,t}\}
$$

| 속성                          | 의미                                                  |
|-------------------------------|-------------------------------------------------------|
| $$z_{i,t}$$                   | 객체 종류에 따라 달라지는 속성 (아래에서 설명)        |
| $$(x_{i,t}, y_{i,t})$$        | ego frame 기준 bounding box 중심 위치                 |
| $$\phi_{i,t} \in [0, 2\pi]$$  | 방향 (orientation)                                    |
| $$(w_{i,t}, h_{i,t})$$        | bounding box 크기 (extent)                            |

### II.1. Obstacle Token

Obstacle 토큰의 $$z_{i,t}$$는 해당 obstacle의 **속도**다.
Ego vehicle로부터 $$D_\text{max} = 30\,\text{m}$$ 이내의 obstacle들만 입력에 포함하며, 토큰 수는 시점마다 달라진다.
논문은 obstacle 수에 상한을 두지 않고, 배치 내에서 가장 긴 시퀀스에 맞춰 나머지를 zero-padding하는 **dynamic padding** 방식을 사용한다.
실제 실험 환경에서는 보통 수 개~십수 개 수준의 obstacle이 범위 내에 존재한다.

### II.2. Route Token

Route 표현이 이 포스팅에서 가장 독특한 부분이다.
`PlanT`는 ego vehicle 전방의 경로를 먼저 조밀하게 샘플링한 뒤, Ramer-Douglas-Peucker 알고리즘으로 일부 점들을 추려낸다.
이 알고리즘은 곡선을 이루는 점들 중에서 전체 형태를 크게 훼손하지 않는 선에서 불필요한 점들을 제거해주는 곡선 단순화 알고리즘이다.
인접한 두 추려진 점 $$u_{i,t}$$, $$u_{i+1,t}$$ 사이의 영역이 하나의 route segment가 되며, 이를 oriented bounding box로 표현한다.

Route 토큰의 6개 속성을 풀어 쓰면 다음과 같다.

| 속성                          | 의미                                                                                                  |
|-------------------------------|-------------------------------------------------------------------------------------------------------|
| $$z_{i,t}$$                   | ego vehicle에서 가장 가까운 segment부터 매기는 순서 (0, 1, ...)                                       |
| $$(x_{i,t}, y_{i,t})$$        | segment 중심의 ego frame 기준 위치                                                                    |
| $$\phi_{i,t}$$                | segment의 진행 방향                                                                                   |
| $$w_{i,t}$$                   | 차선 폭 (lane width)                                                                                  |
| $$h_{i,t}$$                   | segment 길이 $$= \lVert u_{i,t} - u_{i+1,t} \rVert_2$$ ($$L_\text{max} = 10\,\text{m}$$ 이하로 clip)  |

모델에는 항상 고정 개수 $$N_s = 2$$개의 route segment가 입력된다.

{: .note }
> Route를 bounding box로 표현한다는 아이디어의 진짜 의도는 "경로도 하나의 객체"로 취급하는 것이다.
> 주변 obstacle과 동일한 형식으로 표현함으로써, 트랜스포머가 단일한 self-attention 연산만으로 obstacle 간 관계뿐 아니라 obstacle과 경로 사이의 관계도 함께 파악할 수 있다.

{: .warning }
> **`PlanT`는 end-to-end 시스템이 아니다.**
> Route segment를 생성하려면 ego vehicle이 **어느 차선을 따라 어디로 가야 하는지**를 미리 알아야 한다.
> 논문의 주실험에서는 데이터셋이 제공하는 ground-truth route points를 그대로 사용한다.
> 실제 배포 환경에서 이 정보를 얻으려면 lane-level HD map과 global planner가 반드시 필요하다.

## III. Architecture

지금까지 설명한 요소들이 어떻게 하나의 모델로 연결되는지 정리해보자.

### III.1. Token Embedding

각 객체 벡터는 [Misc. 챕터](/docs/reproducing-papers/00-plan-t/03-miscellaneous)에서 설명한 방식 그대로 임베딩된다.

우선, 6차원 속성 벡터를 선형 투영 $$\rho : \mathbb{R}^6 \to \mathbb{R}^H$$로 $$H$$차원으로 변환한다.
그 다음, Obstacle에는 $$\mathbf{e}_v \in \mathbb{R}^H$$를, route segment에는 $$\mathbf{e}_s \in \mathbb{R}^H$$를 더한다 (type embedding).

$$
\mathbf{e}_{i,t} = \begin{cases} \rho(o_{i,t}) + \mathbf{e}_v & o_{i,t} \in \mathcal{V}_t \\ \rho(o_{i,t}) + \mathbf{e}_s & o_{i,t} \in \mathcal{S}_t \end{cases}
$$

### III.2. Transformer Encoder

[Encoder 챕터](/docs/reproducing-papers/00-plan-t/01-transformer-encoder)에서 설명한 트랜스포머 인코더를 그대로 사용하되 [Misc. 챕터](/docs/reproducing-papers/00-plan-t/03-miscellaneous)에서 설명한 대로 `[CLS]` 토큰을 시퀀스 맨 앞에 추가해 인코더에 입력한다.

논문은 pretrained 가중치를 전혀 사용하지 않고 처음부터 학습(train from scratch)하며, 모델 크기에 따른 성능 비교를 위해 커뮤니티에 잘 알려진 BERT의 MINI/SMALL/MEDIUM 스펙을 하이퍼파라미터 기준으로 빌려 아래 세 가지 크기를 실험한다.

| 모델                          | 파라미터      | Layers        | $$d_\text{model}$$    | Heads |
|-------------------------------|---------------|---------------|-----------------------|-------|
| PlanT$$_\text{MINI}$$         | 11.2M         | 4             | 256                   | 4     |
| PlanT$$_\text{SMALL}$$        | 28.8M         | 4             | 512                   | 8     |
| PlanT$$_\text{MEDIUM}$$       | 41.4M         | 8             | 512                   | 8     |

기본 설정은 MEDIUM이며, MINI는 MEDIUM 대비 추론 속도가 **5.3배 빠르면서** 동등한 driving score를 달성한다고 주장한다.

$$
\mathbf{h}_t = \tau\!\left([\mathbf{c},\; \mathbf{e}_{1,t},\; \ldots,\; \mathbf{e}_{|\mathcal{V}_t|+|\mathcal{S}_t|,t}]\right)
$$

여기서 $$\mathbf{c} \in \mathbb{R}^H$$는 학습 가능한 `[CLS]` 토큰이고, 인코더 출력 $$\mathbf{h}_t[0]$$이 `[CLS]`에 해당하는 출력 벡터가 된다.

### III.3. GRU Decoder

`PlanT`의 최종 목표는 ego vehicle이 앞으로 통과해야 할 지점들, 즉 **waypoints**를 예측하는 것이다.
$$\mathcal{W}_t = \{\mathbf{w}_{t+1}, \mathbf{w}_{t+2}, \mathbf{w}_{t+3}, \mathbf{w}_{t+4}\}$$로, 각 $$\mathbf{w}_{t+k} = (x_{t+k}, y_{t+k})$$는 미래 시점 $$t+k$$에서의 2D 좌표다 (자명하게 현재 시점의 ego frame 기준 좌표임).
이 4개의 waypoints를 [GRU 챕터](/docs/repro-plan-t/02-preliminary-gru)에서 설명한 GRU 디코더로 순차적으로 예측한다.

**Step 0: 초기 hidden state 구성**

트랜스포머가 출력한 `[CLS]` 벡터 $$\mathbf{h}_t[0] \in \mathbb{R}^H$$를 먼저 선형 레이어(`wp_head`)로 64차원으로 투영한 뒤, traffic light flag $$l_t \in \{0, 1\}$$을 이어 붙여 65차원 벡터를 만든다.
이것이 GRU(`hidden_size=65`)의 초기 hidden state가 된다.

{: .note }
> 논문 본문에는 `[CLS]` 출력에 traffic light flag를 **그냥 concatenate**한다고만 적혀 있고, 별도의 선형 투영 단계는 명시되어 있지 않다.
> `wp_head`, 64차원 투영, `hidden_size=65` 같은 구체 수치는 공개 코드 구현에서 확인되는 내용이다.

$$
\mathbf{h}_0 = [\mathbf{W}_\text{wp}\,\mathbf{h}_t[0];\; l_t] \in \mathbb{R}^{65}
$$

traffic light 정보를 여기서 주입하는 이유는, 신호등 상태가 waypoint 전체 시퀀스에 일관되게 영향을 미쳐야 하기 때문이다.
적신호이면 GRU는 처음부터 "멈춰야 한다"는 맥락을 갖고 waypoints를 생성하게 된다.

**Step 1~4: 자기회귀적 waypoint 생성**

매 스텝 $$s$$마다 GRU는 **이전 waypoint** $$\mathbf{w}_{s-1}$$과 **단기 목적지 좌표** $$\mathbf{p}_\text{target} \in \mathbb{R}^2$$를 이어 붙인 4차원 벡터를 입력으로 받는다.

출력은 waypoint 절댓값이 아니라 **이전 waypoint로부터의 delta** $$\Delta\mathbf{w}_s$$이며, 이를 누적해 최종 waypoint를 얻는다.

$$
\mathbf{h}_s = \text{GRU}\!\left(\mathbf{h}_{s-1},\; [\mathbf{w}_{s-1};\, \mathbf{p}_\text{target}]\right), \quad \Delta\mathbf{w}_s = \mathbf{W}_\text{out}\, \mathbf{h}_s, \quad \mathbf{w}_s = \mathbf{w}_{s-1} + \Delta\mathbf{w}_s
$$

첫 스텝($$s=1$$)의 입력 $$\mathbf{w}_0$$는 영벡터로 초기화한다.

{: .note }
> **$$\mathbf{p}_\text{target}$$이란?**
> 논문 본문에는 $$\mathbf{p}_\text{target}$$의 정의가 직접 나오지 않는다.
> 공개 코드를 보면 `target_point`는 route에서 뽑은 "가까운 다음 경유지"를 ego frame 2D 좌표로 바꾼 값이다.
> 학습/추론 모두 이 값을 모델 입력으로 넣으며, 이 역시 글로벌 플래너(또는 route 정보) 없이는 만들 수 없다.

### III.4. Summary

1. Obstacle, route segment를 각각 6차원 벡터로 표현한다.
2. Linear projection + token type embedding으로 $$H$$차원 임베딩을 만든다.
3. `[CLS]` 토큰과 함께 트랜스포머 인코더에 입력한다.
4. `[CLS]` 출력 벡터에 traffic light flag를 concatenate한다.
5. GRU 디코더가 4개의 waypoints를 순차적으로 예측한다.

## IV. Auxiliary Task: Obstacle Future Prediction

이 태스크를 "보조(auxiliary)"라고 부르지만, 실제로는 단순한 부가 목표가 아니다.
주 태스크인 waypoint 예측은 오직 `[CLS]` 토큰의 출력만 supervise한다.
즉, `[CLS]` 이외의 모든 obstacle 토큰 출력은 주 태스크 손실에 의해 **직접적인 학습 신호를 받지 못한다**.
이 공백을 메우는 것이 바로 이 태스크의 핵심 역할이다.

구체적으로는, 인코더가 출력한 obstacle 토큰들의 벡터 $$\{\mathbf{h}_{i,t}\}$$를 이용해 다음 시점 $$t+1$$의 각 obstacle 속성들을 예측한다.
여기서 핵심 설계 결정은 속성값을 **연속값 회귀(regression)가 아닌 이산 분류(classification)로 예측**한다는 것이다.
속성값의 범위를 $$Z_a$$개의 bin으로 균등하게 나눈 뒤, 어느 bin에 속하는지를 맞히는 분류 문제로 바꾸는 것이다.
예를 들어 속도를 4개의 bin으로 나눈다면, 코드 기준 속도 범위 $$[0, 60]\,\text{km/h}$$를 4구간으로 쪼개고 각 구간에 레이블 0, 1, 2, 3을 붙인다.

```
bin 0: [ 0, 15) km/h → "정지 또는 서행"
bin 1: [15, 30) km/h → "저속"
bin 2: [30, 45) km/h → "중속"
bin 3: [45, 60] km/h → "고속"
```

모델은 이 중 하나에 대한 확률 분포를 출력하고, cross-entropy로 학습한다.
속성마다 독립적인 선형 레이어 $$\psi_a : \mathbb{R}^H \to \mathbb{R}^{Z_a}$$를 두고 softmax로 클래스 확률을 출력한다.

$$
p_{i,t+1,a} = \text{Softmax}(\psi_a(\mathbf{h}_{i,t})), \quad a = 1, \ldots, 6
$$

속성별 bin 수는 다음과 같다.

| 속성                  | bin 수 ($$Z_a$$)      |
|-----------------------|-----------------------|
| 위치 $$(x, y)$$       | 128                   |
| 속도                  | 4                     |
| 방향                  | 32                    |

결과적으로 obstacle 토큰들은 주 태스크(waypoint 예측)에 직접 참여하지 않으면서도, 이 태스크를 통해 "주변 장애물의 미래 움직임을 이해하는" 풍부한 표현을 강제로 학습하게 된다.
이렇게 학습된 표현이 `[CLS]` 토큰의 장면 요약에 녹아들어, 결과적으로 waypoint 예측 품질을 높인다.
논문은 supplementary material에서 이 태스크를 제거하면 성능이 **크게 하락**함을 ablation으로 보인다.

## V. Training

손실 함수는 두 태스크의 손실을 가중합한다.

$$
\mathcal{L} = \underbrace{\frac{1}{W}\sum_{w=1}^{W} \lVert \mathbf{w}_w - \mathbf{w}_w^\text{gt} \rVert_1}_{\mathcal{L}_\text{waypoints}} + \lambda \underbrace{\frac{1}{|\mathcal{V}_t|}\sum_{i=1}^{|\mathcal{V}_t|} \sum_{a=1}^{6} \mathcal{L}_\text{CE}\!\left(p_{i,t+1,a},\; p_{i,t+1,a}^\text{gt}\right)}_{\mathcal{L}_\text{obstacles}}
$$

- $$\mathcal{L}_\text{waypoints}$$: 예측 waypoint와 expert waypoint 사이의 L1 손실
- $$\mathcal{L}_\text{obstacles}$$: obstacle 속성 예측에 대한 cross-entropy 손실
- $$\lambda = 0.2$$: 두 손실의 균형을 조절하는 가중치

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
