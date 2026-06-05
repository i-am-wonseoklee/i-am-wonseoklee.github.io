---
title: State Estimation Example
layout: default
nav_order: 8
parent: Control Theory
permalink: /docs/control-theory/07-state-estimation-example
---

# State Estimation Example

**Keywords:** `State Estimation`{: .label }, `Kalman Filter`{: .label }

지금까지 state estimator에 대해 학습한 내용을 간단한 코드를 통해 확인해보자.
이를 위해서 이전에 살펴보았던 [도립 진자 카트 시스템](/docs/control-theory/04-inverted-pendulum-cart/)을 다시 가져오겠다.

## I. System Setup

도립 진자 카트 시스템의 상태 방정식은 다음과 같이 표현된다.

$$
\begin{aligned}
\mathbf{\dot{x}} &= \mathbf{A}\mathbf{x} + \mathbf{B}\mathbf{u} \\
\text{where} \quad
\mathbf{A} &= 
\begin{bmatrix}
        0 & 1                   & 0                     & 0 \\
        0 & -\dfrac{\delta}{M}  & \dfrac{mg}{M}         & 0 \\
        0 & 0                   & 0                     & 1 \\
        0 & -\dfrac{\delta}{ML} & -\dfrac{(m+M)g}{ML}   & 0
\end{bmatrix}, \quad
\mathbf{B} = 
\begin{bmatrix}
        0               \\
        \dfrac{1}{M}    \\
        0               \\
        \dfrac{1}{ML}
\end{bmatrix}
\end{aligned}
$$

> 필자는 최근에 GPT와 대화를 하던 중 깨달은 내용인데, inverted pendulum cart는 국문으로는 "도립 진자 카트"라고 부른단다. 딱히 마음에 드는 단어는 아니지만, inverted pendulum cart 보다는 음절도, 타이핑도 적어서 앞으로는 그냥 이렇게 부르도록 하겠다.

## II. Observability Check

이제 다양한 $$\mathbf{C}$$ 에 대해서 observability를 체크해보도록 하자.
아래 결과를 보면 $$\mathbf{C} = [1\,,0\,,0\,,0]$$ 인 경우를 제외하고는 모두 다 rank deficient, 즉, observable하지 않은 것을 알 수 있다.

```python
m = 1.0
M = 5.0
L = 2.0
g = -9.81
delta = 1.0

A = np.array(
    [
        [0, 1, 0, 0],
        [0, -delta / M, m * g / M, 0],
        [0, 0, 0, 1],
        [0, -delta / (M * L), -(m + M) * g / (M * L), 0],
    ]
)

B = np.array(
    [
        [0],
        [1 / M],
        [0],
        [1 / (M * L)],
    ]
)

def calculate_observability_matrix(A, C):
    n = A.shape[0]
    rows = [C]
    for i in range(1, n):
        rows.append(rows[-1] @ A)
    return np.vstack(rows)

def is_observable(A, C):
    O = calculate_observability_matrix(A, C)
    return np.linalg.matrix_rank(O) == A.shape[0]

print(is_observable(A, np.array([[1, 0, 0, 0]]))) # Result: True
print(is_observable(A, np.array([[0, 1, 0, 0]]))) # Result: False
print(is_observable(A, np.array([[0, 0, 1, 0]]))) # Result: False
print(is_observable(A, np.array([[0, 0, 0, 1]]))) # Result: False
```

그런데, 곰곰이 생각해보면 좀 억울하지 않은가? $$\mathbf{A}$$ 를 살펴보면 $$\mathbf{A}$$ 의 첫 열은 영 벡터이므로 사실 $$x$$ (위치) 는 이 시스템 다이나믹스에 영향을 주지 않는 값임을 알 수 있다.
그런데, $$x$$ 를 직접 측정하지 않고서는 full state를 복원할 길이 없는 상황이라니.
아래와 같이 시스템을 $$x$$ 에 무관하게 다시 정의해보자.
상태 벡터를 $$\tilde{\mathbf{x}} = [\dot{x}\,,\,\theta\,,\,\dot{\theta}]^\top$$ 으로 줄이면, 대응하는 $$\tilde{\mathbf{A}}$$, $$\tilde{\mathbf{B}}$$ 는 다음과 같다.

$$
\begin{aligned}
\tilde{\mathbf{A}} &=
\begin{bmatrix}
-\dfrac{\delta}{M}  & \dfrac{mg}{M}         & 0 \\
0                   & 0                     & 1 \\
-\dfrac{\delta}{ML} & -\dfrac{(m+M)g}{ML}   & 0
\end{bmatrix}, \quad
\tilde{\mathbf{B}} =
\begin{bmatrix}
\dfrac{1}{M} \\ 0 \\ \dfrac{1}{ML}
\end{bmatrix}
\end{aligned}
$$

이 상태에서 다양한 $$\tilde{\mathbf{C}}$$ 에 대해서 observability를 다시 체크해보도록 하자.
이번에는 또 이게 나름대로 골 때리는 상황이다.
아래에서 확인할 수 있듯 이번에는 모든 $$\tilde{\mathbf{C}}$$ 에 대해서 observable한 것을 알 수 있다.

```python
A_tilde = A[1:, 1:]
B_tilde = B[1:, 0:]
print(is_observable(A_tilde, np.array([[1, 0, 0]]))) # True
print(is_observable(A_tilde, np.array([[0, 1, 0]]))) # True
print(is_observable(A_tilde, np.array([[0, 0, 1]]))) # True
```

위와 같이 $$\tilde{\mathbf{C}}$$ 를 뭐로 설정하든 observable하다면 무슨 기준으로 $$\tilde{\mathbf{C}}$$ 를 설정하면 될까?
물론, 센서 정확도나 비용은 고려할 필요가 없다고 할 때 말이다.

## III. Sensor Selection Criterion

역시 [앞선 챕터](/docs/control-theory/05-observability/)에서 배운 observability Gramian을 기억하자.
$$\mathcal{O} = \mathbf{U \Sigma V^T}$$ 로 singular value decomposition하면 $$\mathbf{\Sigma}$$ 의 대각 원소, 즉 singular value들은 각 방향으로 state를 얼마나 잘 관측할 수 있는지를 나타낸다.
따라서 $$\det(\mathcal{O}^\top\mathcal{O}) = \prod_i \sigma_i^2$$ 를 observability의 전반적인 척도로 활용할 수 있다.
결과를 보면 $$\dot{x}$$ 를 측정하는 경우의 observability가 극단적으로 좋은 것을 확인할 수 있다.

```python
O1 = calculate_observability_matrix(A_tilde, np.array([[1, 0, 0]]))
O2 = calculate_observability_matrix(A_tilde, np.array([[0, 1, 0]]))
O3 = calculate_observability_matrix(A_tilde, np.array([[0, 0, 1]]))

print(np.linalg.det(O1.T @ O1)) # 556.78
print(np.linalg.det(O2.T @ O2)) # 0.37
print(np.linalg.det(O3.T @ O3)) # 0.70
```

## IV. Kalman Filter Example

사실 controller를 붙이지 않은 상태에서 도립 진자 카트에 Kalman filter를 실습하는 것은 매우 어렵다.
이는 시스템이 컨트롤 없이는 unstable하기 때문이다.
따라서, 여기에서는 도립 진자가 아니라 현수 진자 시스템에 대해서 데모해보도록 하자.

### IV.1. Hanging Pendulum Cart System

현수 진자 카트 시스템은 진자가 아래를 향해 매달린 형태로, 평형점이 stable하다.
도립 진자와 동일한 상태 벡터 $$\mathbf{x} = [x\,,\,\dot{x}\,,\,\theta\,,\,\dot{\theta}]^\top$$ 를 사용하되,
이번에는 $$\theta = 0$$ 이 아래를 향한 평형점을 의미한다.
$$\mathbf{A}$$ , $$\mathbf{B}$$ 는 다음과 같다.

$$
\mathbf{A}_{hang} =
\begin{bmatrix}
0 & 1                    & 0                     & 0 \\
0 & -\dfrac{\delta}{M}   & -\dfrac{mg}{M}        & 0 \\
0 & 0                    & 0                     & 1 \\
0 & \dfrac{\delta}{ML}   & \dfrac{(m+M)g}{ML}    & 0
\end{bmatrix}
\quad
\mathbf{B}_{hang} = \begin{bmatrix} 0 \\ \dfrac{1}{M} \\ 0 \\ -\dfrac{1}{ML} \end{bmatrix}
$$

출력 행렬은 위치 $$x$$ 를 측정하는 $$\mathbf{C} = [1\,,0\,,0\,,0]$$ 으로 설정했다.

```python
A_hang = np.array(
    [
        [0, 1, 0, 0],
        [0, -delta / M, -m * g / M, 0],
        [0, 0, 0, 1],
        [0, delta / (M * L), (m + M) * g / (M * L), 0],
    ]
)
B_hang = np.array([[0], [1 / M], [0], [-1 / (M * L)]])
C_hang = np.array([[1, 0, 0, 0]])
```

### IV.2. Augmented system for simulation

사실 이걸 굳이 별도 챕터로 빼서 설명해야 하나에 대해 조금 고민하기는 했다.
하지만, 행렬을 다루는 트릭으로 언급할 가치가 충분하므로 정리하기로 결정했다.
우리가 결국 표현하고자 하는 시스템은 프로세스 노이즈와 메저먼트 노이즈가 있는 아래와 같이 정의되는 시스템이다.

$$
\begin{aligned}
\dot{\mathbf{x}} & = \mathbf{Ax} + \mathbf{Bu} + \mathbf{V_d d} + 0 \cdot \mathbf{n}  \\
\mathbf{y}       & = \mathbf{Cx} + 0 \cdot \mathbf{u} + 0 \cdot \mathbf{d} + \mathbf{V_n n}   \\
\end{aligned}
$$

조금 더 이쁘게 행렬 모양으로 적으면 다음과 같다.

$$
\begin{aligned}
\dot{\mathbf{x}} &= \mathbf{A}\mathbf{x} + \mathbf{B}_{aug}\tilde{\mathbf{u}} \\
\mathbf{y}       &= \mathbf{C}\mathbf{x} + \mathbf{D}_{aug}\tilde{\mathbf{u}}
\end{aligned}
\quad \text{where} \quad
\mathbf{B}_{aug} = \begin{bmatrix} \mathbf{B} & \mathbf{V_d} & \mathbf{0} \end{bmatrix}, \quad
\mathbf{D}_{aug} = \begin{bmatrix} \mathbf{0} & \mathbf{0} & \mathbf{V_n} \end{bmatrix}, \quad
\tilde{\mathbf{u}} = \begin{bmatrix} \mathbf{u} \\ \mathbf{d} \\ \mathbf{n} \end{bmatrix}
$$

즉, 제어 입력 $$\mathbf{u}$$, process noise $$\mathbf{d}$$, measurement noise $$\mathbf{n}$$ 을 하나의 확장된 입력 벡터 $$\tilde{\mathbf{u}}$$ 로 묶고, 이에 대응하는 $$\mathbf{B}_{aug}$$, $$\mathbf{D}_{aug}$$ 를 hstack으로 구성하면 표준 상태 공간 형태를 유지할 수 있다.

> 갑자기 $$\mathbf{D}_{aug}$$, $$\tilde{\mathbf{u}}$$ 가 나와 당황했을 텐데, 이런 텀을 feedthrough라고 부른다.

하여간, 이제 우리는 $$(\mathbf{A},\, \mathbf{B}_{aug},\, \mathbf{C},\, \mathbf{D}_{aug})$$ 로 표현되는 augmented system을 얻었으므로, `scipy.signal.lsim` 으로 바로 시뮬레이션할 수 있다.
MATLAB의 `lsim` 과 동일한 인터페이스로, `StateSpace` 객체와 입력 시계열 $$\tilde{\mathbf{U}}$$ 를 넘기면 출력 $$\mathbf{y}$$ 와 상태 궤적 $$\mathbf{x}$$ 를 돌려준다.
노이즈 없는 시뮬레이션과 노이즈 있는 시뮬레이션 모두, $$\tilde{\mathbf{u}}(t) = [\mathbf{u}(t);\,\mathbf{d}(t);\,\mathbf{n}(t)]$$ 를 그대로 구성해서 넘기면 된다.
아래는 $$\mathbf{u}$$ 에 임펄스 입력을 가했을 때, 노이즈가 있고 없을 때의 출력을 비교하여 보여주는 코드와 그 실행 결과이다.

```python
from scipy import signal
import matplotlib.pyplot as plt

# Augmented system 구성
Vd = np.eye(4) * 0.5  # process noise covariance
Vn = np.array([[1.0]])  # measurement noise covariance
B_aug = np.hstack([B_hang, Vd, np.zeros((4, 1))])  # (4, 6)
D_aug = np.hstack([np.zeros((1, 1)), np.zeros((1, 4)), Vn])  # (1, 6)

sys_aug = signal.StateSpace(A_hang, B_aug, C_hang, D_aug)

T = 5.0
dt = 0.01
t = np.arange(0, T + dt, dt)
N = len(t)

# 노이즈 없는 입력: u = impulse, d = 0, n = 0
U_clean = np.zeros((N, 6))
U_clean[0, 0] = 10.0 / dt  # impulse

_, y_clean, x_clean = signal.lsim(sys_aug, U=U_clean, T=t)

# 노이즈 있는 입력: u = impulse, d = process noise, n = measurement noise
np.random.seed(42)
D_noise = np.random.multivariate_normal(np.zeros(4), Vd, N)  # (N, 4)
N_noise = np.random.multivariate_normal(np.zeros(1), Vn, N)  # (N, 1)

U_noisy = np.zeros((N, 6))
U_noisy[0, 0] = 10.0 / dt  # impulse
U_noisy[:, 1:5] = D_noise  # process noise
U_noisy[:, 5:] = N_noise  # measurement noise

_, y_noisy, x_noisy = signal.lsim(sys_aug, U=U_noisy, T=t)

# 비교 플롯
fig, ax = plt.subplots(figsize=(10, 4))
ax.plot(t, y_clean, label="Clean output", linewidth=1.5)
ax.plot(t, y_noisy, label="Noisy output", linewidth=1.0, alpha=0.7)
ax.set_xlabel("Time [s]")
ax.set_ylabel(r"$y = x$")
ax.legend()
ax.grid(True)
plt.tight_layout()
plt.show()
```

![simulation result](/docs/control-theory/07-state-estimation-example/asset/simulation.png)

### IV.3. Kalman Filter

이제 곧바로 이어서 [이전 챕터](/docs/control-theory/06-state-estimation/) 에서 배운 방법으로 Kalman filter gain $$\mathbf{L}$$ 을 구해보자.

```python
import scipy.linalg

Q_kf = Vd   # process noise covariance
R_kf = Vn   # measurement noise covariance

P = scipy.linalg.solve_continuous_are(A_hang.T, C_hang.T, Q_kf, R_kf)
L = P @ C_hang.T @ np.linalg.inv(R_kf)
print(L)
#[[ 1.48600675]
# [ 0.85410804]
# [-0.49596633]
# [-1.0414812 ]]
```

이제 이 $$\mathbf{L}$$ 을 이용해 연속 시간 observer를 시뮬레이션해보자.
IV.2 에서와 비슷하게 augmented system을 만들어서 쉽게 시뮬레이션할 수 있다.
Observer의 다이나믹스는 다음과 같다.

$$
\dot{\hat{\mathbf{x}}} = (\mathbf{A} - \mathbf{LC})\hat{\mathbf{x}} + \begin{bmatrix} \mathbf{B} & \mathbf{L} \end{bmatrix} \begin{bmatrix} \mathbf{u} \\ \mathbf{y} \end{bmatrix}
$$

```python
A_obs = A_hang - L @ C_hang
B_obs = np.hstack([B_hang, L])  # (4, 2): u, y를 입력으로
C_obs = np.eye(4)               # 상태 전체를 출력
D_obs = np.zeros((4, 2))

sys_obs = signal.StateSpace(A_obs, B_obs, C_obs, D_obs)

# IV.2에서 구한 y_noisy를 측정값으로 사용
U_obs = np.zeros((N, 2))
U_obs[0, 0] = 10.0 / dt  # impulse (u)
U_obs[:, 1] = y_noisy    # noisy measurement (y)

_, x_hat, _ = signal.lsim(sys_obs, U=U_obs, T=t)
```

마지막으로 clean 출력, noisy 측정값, Kalman filter 추정 결과를 한 플롯에 비교해보자.
출력 $$y = x$$ 와 함께 나머지 3개 상태도 함께 확인한다.

```python
# 비교 플롯, x_clean, x_noisy, x_hat
fig, axs = plt.subplots(4, 1, figsize=(10, 8), sharex=True)
state_labels = [
    "x1 (cart pos)",
    "x2 (cart vel)",
    "x3 (pole angle)",
    "x4 (pole ang vel)",
]
for i in range(4):
    axs[i].plot(t, x_clean[:, i], label="Clean state", linewidth=1.5)
    axs[i].plot(t, x_noisy[:, i], label="Noisy state", linewidth=1.0, alpha=0.7)
    axs[i].plot(t, x_hat[:, i], label="Estimated state", linewidth=1.0, linestyle="--")
    axs[i].set_ylabel(state_labels[i])
    axs[i].legend()
    axs[i].grid(True)
axs[-1].set_xlabel("Time [s]")
plt.tight_layout()
plt.show()
```

![kalman filter result](/docs/control-theory/07-state-estimation-example/asset/kalman.png)

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>

