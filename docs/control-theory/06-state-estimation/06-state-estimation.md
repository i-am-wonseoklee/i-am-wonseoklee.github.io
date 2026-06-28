---
title: State Estimation
layout: default
nav_order: 7
parent: Control Theory
permalink: /docs/control-theory/06-state-estimation
---

# State Estimation

## TOC
{: .no_toc }

1. TOC
{:toc}


**Keywords:** `State Estimation`{: .label }, `Kalman Filter`{: .label }

[앞선 챕터](/docs/control-theory/05-observability/)에서 observability가 무엇이고 왜 필요한지 살펴보았다.
이제 한 단계 더 나아가, 실제로 측정 가능한 출력 $$\mathbf{y}$$ 만으로 상태 $$\mathbf{x}$$ 를 어떻게 추정하는지 정리해보자.

## I. 문제 설정

우리가 다루는 선형 시스템은 아래와 같다.

$$
\dot{\mathbf{x}} = \mathbf{Ax} + \mathbf{Bu}, \quad \mathbf{y} = \mathbf{Cx}
$$

각 기호의 의미와 차원을 한 눈에 정리하면 아래와 같다.
시스템의 상태 개수를 $$n$$, 입력 개수를 $$m$$, 측정 가능한 출력 개수를 $$p$$ 라 하자.

| 기호 | 의미 | 차원 |
|---|---|---|
| $$\mathbf{x}$$ | 상태 벡터 | $$n \times 1$$ |
| $$\mathbf{u}$$ | 입력 벡터 | $$m \times 1$$ |
| $$\mathbf{y}$$ | 출력(측정) 벡터 | $$p \times 1$$ |
| $$\mathbf{A}$$ | 시스템 행렬 | $$n \times n$$ |
| $$\mathbf{B}$$ | 입력 행렬 | $$n \times m$$ |
| $$\mathbf{C}$$ | 출력 행렬 | $$p \times n$$ |
| $$\mathbf{K}$$ | 제어 게인 | $$m \times n$$ |
| $$\mathbf{L}$$ | observer 게인 | $$n \times p$$ |
| $$\hat{\mathbf{x}}$$ | 상태 추정값 | $$n \times 1$$ |

$$\mathbf{K}$$ 는 제어기에서, $$\mathbf{L}$$ 은 observer에서 설계하는 두 개의 게인 행렬이다.
$$\mathbf{K}$$ 가 $$\mathbf{A} - \mathbf{BK}$$ 의 극점을 결정하듯, $$\mathbf{L}$$ 은 $$\mathbf{A} - \mathbf{LC}$$ 의 극점을 결정한다.

앞선 챕터의 상태 피드백 제어 $$\mathbf{u} = -\mathbf{Kx}$$ 는 "상태 $$\mathbf{x}$$ 를 전부 알고 있다"는 가정 위에 서 있다.
하지만 실제로는 센서가 제한적이라 $$\mathbf{x}$$ 일부만 측정되는 경우가 대부분이다.
그래서 $$\mathbf{y}$$ 와 $$\mathbf{u}$$ 를 이용해 $$\mathbf{x}$$ 를 복원하는 블록, 즉 **state estimator (observer)** 가 필요하다.

## II. State Estimator Dynamics

가장 기본적인 연속시간 observer는 아래처럼 쓴다.

$$
\dot{\hat{\mathbf{x}}} = \mathbf{A}\hat{\mathbf{x}} + \mathbf{Bu} + \mathbf{L}(\mathbf{y} - \hat{\mathbf{y}}),
\quad
\hat{\mathbf{y}} = \mathbf{C}\hat{\mathbf{x}}
$$

여기서 각 항의 의미는 다음과 같다.

1. $$\mathbf{A}\hat{\mathbf{x}} + \mathbf{Bu}$$: 모델이 예측한 상태 변화
2. $$\mathbf{y} - \hat{\mathbf{y}}$$: 실제 출력과 예측 출력의 차이(innovation, residual)
3. $$\mathbf{L}(\mathbf{y} - \hat{\mathbf{y}})$$: 오차를 이용한 보정량

즉, observer는 "모델 예측 + 측정 기반 보정" 구조다.

## III. Estimation Error Dynamics

추정 오차를 아래처럼 정의하자.

$$
\mathbf{e} = \mathbf{x} - \hat{\mathbf{x}}
$$

이제 한 줄씩 전개해보자.

먼저 오차를 미분하면

$$
\dot{\mathbf{e}} = \dot{\mathbf{x}} - \dot{\hat{\mathbf{x}}}
$$

이고, 시스템과 observer 식을 그대로 대입하면

$$
\begin{aligned}
\dot{\mathbf{e}}
&= (\mathbf{Ax} + \mathbf{Bu}) - \big(\mathbf{A}\hat{\mathbf{x}} + \mathbf{Bu} + \mathbf{L}(\mathbf{y} - \hat{\mathbf{y}})\big) \\
&= \mathbf{A}(\mathbf{x} - \hat{\mathbf{x}}) - \mathbf{L}(\mathbf{y} - \hat{\mathbf{y}})
\end{aligned}
$$

여기서 $$\mathbf{Bu}$$ 항이 소거되는 걸 볼 수 있다.

또한 $$\mathbf{y} = \mathbf{Cx}$$, $$\hat{\mathbf{y}} = \mathbf{C}\hat{\mathbf{x}}$$ 이므로

$$
\mathbf{y} - \hat{\mathbf{y}} = \mathbf{C}(\mathbf{x} - \hat{\mathbf{x}}) = \mathbf{Ce}
$$

를 얻는다. 이를 다시 대입하면

$$
\begin{aligned}
\dot{\mathbf{e}}
&= \mathbf{A}\mathbf{e} - \mathbf{L}(\mathbf{Ce}) \\
&= (\mathbf{A} - \mathbf{LC})\mathbf{e}
\end{aligned}
$$

즉, 오차 시스템도 하나의 선형 시스템이며 상태행렬은 $$\mathbf{A} - \mathbf{LC}$$ 이다.

여기서 중요한 포인트는 두 가지다.

1. $$\dot{\mathbf{e}}$$ 는 입력 $$\mathbf{u}$$ 에 직접 의존하지 않는다.
2. 오차 수렴 여부는 오직 $$\mathbf{A} - \mathbf{LC}$$ 의 고유값으로 결정된다.

결국 estimator 설계 목표는 단순하다.

$$
\operatorname{eig}(\mathbf{A} - \mathbf{LC}) \subset \mathbb{C}_{-}
$$

즉, $$\mathbf{A} - \mathbf{LC}$$ 를 안정화해서 $$\mathbf{e}(t) \to \mathbf{0}$$ 로 만들면 된다.

## IV. Observer Gain $$\mathbf{L}$$ 설계

### IV.1 Pole Placement

Observer gain $$\mathbf{L}$$ 을 구하려면 $$\mathbf{A} - \mathbf{LC}$$ 의 극점을 원하는 위치에 배치해야 한다.
그런데 `place_poles`를 그냥 쓰면 안 된다. 이유를 차원부터 따져보자.

**`place_poles` 가 기대하는 입력 모양**

`place_poles(A, B, poles)` 는 내부적으로 $$\mathbf{A} - \mathbf{BK}$$ 꼴을 풀어서 $$\mathbf{K}$$ 를 반환한다.
이때 필요한 차원 조건은 아래와 같다.

| 인자 | 역할 | 차원 |
|---|---|---|
| 첫 번째 인자 ($$\mathbf{A}$$ 역할) | 정방 시스템 행렬 | $$n \times n$$ |
| 두 번째 인자 ($$\mathbf{B}$$ 역할) | 입력이 어느 상태에 들어오는지 | $$n \times m$$ |
| 반환값 $$\mathbf{K}$$ | 게인 | $$m \times n$$ |

**왜 $$\mathbf{C}$$ 를 그대로 두 번째 인자로 못 넣는가**

우리 문제에서 $$\mathbf{C}$$ 는 $$p \times n$$ 이다.
`place_poles` 의 두 번째 인자는 $$n \times (\cdot)$$ 이어야 하는데,
$$\mathbf{C}$$ 는 행이 $$p$$ 개라 차원이 맞지 않는다.

예제 수치로 보면 더 명확하다.
$$\mathbf{A}$$ 는 $$2 \times 2$$, $$\mathbf{C}$$ 는 $$1 \times 2$$ 인데,
`place_poles(A, C, poles)` 를 호출하면 두 번째 인자가 $$1 \times 2$$ 라 행 수가 안 맞아서 바로 에러가 난다.

**어떻게 해결하는가**

핵심 관찰은 아래 두 가지다.

1. $$\mathbf{A} - \mathbf{LC}$$ 를 전치하면 $$(\mathbf{A} - \mathbf{LC})^T = \mathbf{A}^T - \mathbf{C}^T\mathbf{L}^T$$ 이다.
2. 행렬과 그 전치는 고유값이 같다. 즉 극점이 동일하다.

그러면 $$\mathbf{A}^T - \mathbf{C}^T\mathbf{L}^T$$ 는 $$\mathbf{A} - \mathbf{BK}$$ 꼴이 되고, 여기서

$$
\mathbf{A}^T \xrightarrow{\text{역할}} \mathbf{A}, \qquad
\mathbf{C}^T \xrightarrow{\text{역할}} \mathbf{B}, \qquad
\mathbf{L}^T \xrightarrow{\text{역할}} \mathbf{K}
$$

로 대응된다.
차원을 다시 확인해보자.

| | 원래 문제 | `place_poles` 에 넣는 값 |
|---|---|---|
| 시스템 행렬 | $$\mathbf{A}$$, $$n \times n$$ | $$\mathbf{A}^T$$, $$n \times n$$ ✓ |
| "$$\mathbf{B}$$" 역할 | — | $$\mathbf{C}^T$$, $$n \times p$$ ✓ |
| 구하는 게인 | $$\mathbf{L}$$, $$n \times p$$ | $$\mathbf{L}^T$$, $$p \times n$$ (반환 후 전치) |

$$\mathbf{C}^T$$ 는 $$n \times p$$ 라 행이 $$n$$ 개 — `place_poles` 가 기대하는 모양과 딱 맞는다.
`place_poles` 가 반환하는 $$\mathbf{L}^T$$ ($$p \times n$$) 에 `.T` 를 붙이면 원래 $$\mathbf{L}$$ ($$n \times p$$) 을 얻는다.

즉, $$\mathbf{L}$$ 설계는 $$\mathbf{A}^T, \mathbf{C}^T$$ 에 대한 pole placement와 동일하다.

```python
import numpy as np
from scipy.signal import place_poles

A = np.array([[0, 1], [-2, -3]])
B = np.array([[0], [1]])
C = np.array([[1, 0]])

desired_observer_poles = np.array([-5.0, -6.0])
L = place_poles(A.T, C.T, desired_observer_poles).gain_matrix.T
print(L)  # [[8.], [4.]]
```

### IV.2 Pole 선택 직관

경험적으로 observer pole은 controller pole보다 보통 더 왼쪽(더 빠른 동특성)에 둔다.
대략 2~5배 정도 빠르게 잡는 경우가 많다.

{: .note }
> observer를 지나치게 빠르게 만들면 노이즈 증폭이 심해질 수 있다.
> 따라서 "무조건 빠르게"가 아니라, 노이즈/모델오차와의 트레이드오프를 고려해야 한다.

## V. Kalman Filter (개요)

지금까지 만든 observer에는 사실 크게 비현실적인 가정이 하나 숨어 있다.
센서가 완벽하고, 모델도 완벽하다는 가정이다.

현실은 다르다.
센서에는 노이즈가 섞이고, 우리가 만든 모델은 언제나 실제 시스템의 근사일 뿐이다.
그렇다면 "$$\mathbf{L}$$ 을 어떻게 잡아야 가장 현명한가?"라는 질문이 자연스럽게 생긴다.
Kalman filter는 바로 그 질문에 대한 답이다.

**핵심 아이디어: 두 정보 중 어느 쪽을 더 믿을 것인가**

observer는 매 순간 두 가지 정보를 조합한다.

1. **모델의 예측** — $$\dot{\hat{\mathbf{x}}} = \mathbf{A}\hat{\mathbf{x}} + \mathbf{Bu}$$
2. **센서의 측정** — $$\mathbf{y}$$

이 두 정보 중 어느 쪽을 얼마나 믿을지를 $$\mathbf{L}$$ 이 결정한다.
$$\mathbf{L}$$ 이 크면 센서를 더 따라가고, $$\mathbf{L}$$ 이 작으면 모델 예측을 더 따라간다.

직관적으로 생각해보면 이렇다.

- 모델이 엉망이고 센서가 정확하다면? → 센서를 믿어야 한다 → $$\mathbf{L}$$ 을 크게.
- 센서가 노이즈 투성이고 모델이 꽤 정확하다면? → 모델을 믿어야 한다 → $$\mathbf{L}$$ 을 작게.

Kalman filter는 이 직관을 수학적으로 형식화해서, "추정 오차의 분산을 최소화하는 $$\mathbf{L}$$"을 자동으로 계산해준다.

**Q와 R: 얼마나 못 믿는가를 수치로**

모델 오차의 크기를 $$\mathbf{Q}$$(process noise 공분산), 센서 오차의 크기를 $$\mathbf{R}$$(measurement noise 공분산)으로 나타낸다.
이 두 값을 직접 설정하면 Kalman filter가 그에 맞는 최적의 $$\mathbf{L}$$ 을 계산한다.

- $$\mathbf{Q}$$ 를 크게 → "모델을 못 믿겠다" → 센서를 더 따름 → $$\mathbf{L}$$ 커짐
- $$\mathbf{R}$$ 을 크게 → "센서를 못 믿겠다" → 모델을 더 따름 → $$\mathbf{L}$$ 작아짐

이 구조가 LQR과 완전히 대칭이라는 점도 눈여겨볼 만하다.
LQR은 $$\mathbf{Q}, \mathbf{R}$$ 로 "상태를 얼마나 빠르게 줄일지 vs 입력을 얼마나 아낄지"를 조정했다.
Kalman filter는 $$\mathbf{Q}, \mathbf{R}$$ 로 "모델을 얼마나 믿을지 vs 센서를 얼마나 믿을지"를 조정한다.
설계자가 조정하는 손잡이(knob)의 역할이 완전히 대응된다.

**Q와 R 설정 방법**

$$\mathbf{R}$$ 은 센서 스펙에서 바로 읽을 수 있다.
센서 노이즈의 표준편차가 $$\sigma$$ 라면 $$\mathbf{R}$$ 에 $$\sigma^2$$ 을 넣으면 된다.

센서가 하나($$p=1$$)면 스칼라다.
예를 들어 "위치 센서 정밀도 ±0.1 m (1σ)"이면 $$\mathbf{R} = [0.01]$$.

센서가 여러 개($$p > 1$$)면 $$p \times p$$ 대각 행렬이 된다.
예를 들어 위치 센서($$\sigma = 0.1\,\text{m}$$)와 각도 센서($$\sigma = 0.05\,\text{rad}$$)를 함께 쓴다면

$$
\mathbf{R} = \begin{bmatrix} 0.01 & 0 \\ 0 & 0.0025 \end{bmatrix}
$$

두 센서가 서로 독립이면 비대각 원소는 0이다.
같은 진동에 같이 흔들리는 등 서로 연관된 경우에만 비대각 원소에 값을 넣는다.

$$\mathbf{Q}$$ 는 직접 측정하기 어렵다.
보통 아래 전략으로 시작한다.

1. 일단 $$\mathbf{Q} = \mathbf{I}$$ (단위행렬)로 놓고 돌려본다.
2. 추정이 센서를 너무 따라 튀면 → $$\mathbf{Q}$$ 를 줄인다.
3. 추정이 너무 굼뜨게 반응하면 → $$\mathbf{Q}$$ 를 키운다.

$$\mathbf{Q}$$ 도 보통은 대각행렬로 쓴다.
각 상태 채널의 노이즈가 서로 독립이라고 가정하면 비대각 원소는 0이 되고, 실용적으로도 대각 원소만 조정하는 것이 훨씬 다루기 쉽기 때문이다.
채널별로 불확실성이 다르다면 대각 원소 값을 다르게 잡으면 된다.
예를 들어 위치 모델보다 속도 모델이 더 부정확하다면 속도 채널에 해당하는 대각 원소를 더 크게 잡는 식이다.

절댓값보다 **비율 $$\mathbf{Q}/\mathbf{R}$$** 이 중요하다.
$$\mathbf{Q}$$ 와 $$\mathbf{R}$$ 을 둘 다 10배 키워도 $$\mathbf{L}$$ 은 바뀌지 않는다.

**코드로는 이렇게**

수식 유도는 여기서 다루지 않는다.
결론적으로 정상상태 Kalman gain은 아래처럼 구한다.

```python
from scipy.linalg import solve_continuous_are
import numpy as np

# 예: 위치/속도 2-상태 시스템, 위치 센서 1개 (σ = 0.1 m)
# R: 센서 분산 (0.1^2 = 0.01)
R = np.array([[0.01]])
# Q: 모델 불확실성 (초기값은 단위행렬로 놓고 튜닝)
Q = np.eye(2)

P = solve_continuous_are(A.T, C.T, Q, R)
L = P @ C.T @ np.linalg.inv(R)
```

`solve_continuous_are` 에 $$\mathbf{A}^T, \mathbf{C}^T$$ 를 넘기는 이유는 IV.1에서 pole placement 때 전치를 썼던 것과 같은 이유다.
Kalman filter도 duality에 의해 LQR Riccati와 동일한 함수로 풀린다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
