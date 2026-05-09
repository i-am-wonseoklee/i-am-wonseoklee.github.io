---
title: Inverted Pendulum Cart
layout: default
nav_order: 5
parent: Control Theory
permalink: /docs/control-theory/04-inverted-pendulum-cart
---

# Inverted Pendulum Cart

코드 없이 배운 내용만 늘어놓다 보니 자꾸 공허한 기분이 든다.
정말 이게 머릿속에 들어온 건지, 아니면 그냥 읽은 건지 헷갈리기도 하고.
그래서 간단한 예제를 하나 직접 풀어봐서 배운 게 뭔지 확인해보려고 한다.

## I. 제어 이론 복습

간략하게 지금까지 배운 내용을 복기해보도록 하자.
선형 시스템 (비선형을 선형화한 것이건 뭐건 간에) 은 아래와 같이 표현할 수 있다.

$$
\begin{aligned}
\mathbf{\dot{x}} & = \mathbf{Ax} + \mathbf{Bu}  \\
& = \mathbf{Ax} - \mathbf{BKx}                  \\
& = (\mathbf{A - BK})\mathbf{x}                 \\
& = \mathbf{Dx}                                 \\
\end{aligned}
$$

위와 같이 주어지는 시스템이 controllable한지 판단할 수 있는 방법은 controllability test이다.
controllable하다면 적절한 $$\mathbf{K}$$를 구해서 시스템을 stable하게 만들 수 있다.
stable해지려면 $$\mathbf{D} = \mathbf{A - BK}$$의 eigenvalue 실수부가 모두 음수여야 한다.
이 챕터에서는 이 $$\mathbf{K}$$를 구하는 두 가지 방법을 살펴볼 것이다.

## II. 시스템 선형화

코드를 통한 실습을 위해서 카트에 거꾸로 된 진자를 다는 경우를 생각해보자.
대략 아래와 같이 생긴 시스템이다.

![](/docs/control-theory/04-inverted-pendulum-cart/assets/figures/fig00.png)

그리고 이 시스템의 비선형 모델은 아래와 같이 주어진다.
수식이 무섭게 생겼을 거다. 걱정 말자, 내가 만든 것도 아니고 퍼온 거니까.
마지막으로 $$\delta$$는 카트의 damping 계수인데, 정확한 물리적 의미는 여기서는 중요하지 않다.
모델 자체를 이해하기보다는 선형화 과정에 집중하자.

$$
\mathbf{\dot{x}}
=
\begin{bmatrix}
\dot{x} \\
\dot{v} \\
\dot{\theta} \\
\dot{\omega}
\end{bmatrix}
=
\begin{bmatrix}
v \\

\dfrac{
    -m^2 L^2 g \cos(\theta)\sin(\theta)
    + mL^2\left(
        mL\omega^2\sin(\theta) - \delta v
    \right)
    + mL^2 u
}{
    mL^2\left(
        M + m\left(1 - \cos^2(\theta)\right)
    \right)
} \\

\omega \\

\dfrac{
    (m+M)mgL\sin(\theta)
    - mL\cos(\theta)\left(
        mL\omega^2\sin(\theta) - \delta v
    \right)
    + mL\cos(\theta)\,u
}{
    mL^2\left(
        M + m\left(1 - \cos^2(\theta)\right)
    \right)
}

\end{bmatrix}
$$

이제 $$f(\mathbf{x}, \mathbf{u}) = \mathbf{\dot{x}}$$ 이라하고 $$\mathbf{x^{\ast}} = [0\;0\;\pi\;0]^T$$, $$\mathbf{u^{\ast}} = [0]^T$$ 근방에서 선형화해보도록 하자.
그러면 아래와 같이 테일러 전개할 수 있다:

$$
\begin{aligned}
f(\mathbf{x}, \mathbf{u}) &\approx f(\mathbf{x^{\ast}}, \mathbf{u^{\ast}}) \\
&\quad + \frac{\partial f}{\partial \mathbf{x}}\bigg|_{\mathbf{x}=\mathbf{x^{\ast}}, \mathbf{u}=\mathbf{u^{\ast}}} (\mathbf{x} - \mathbf{x^{\ast}}) \\
&\quad + \frac{\partial f}{\partial \mathbf{u}}\bigg|_{\mathbf{x}=\mathbf{x^{\ast}}, \mathbf{u}=\mathbf{u^{\ast}}} (\mathbf{u} - \mathbf{u^{\ast}})
\end{aligned}
$$

정의로부터 $$f(\mathbf{x^{\ast}}, \mathbf{u^{\ast}}) = \mathbf{0}$$ (평형점에서는 가속이 0)이므로, $$\mathbf{e} = \mathbf{x} - \mathbf{x^{\ast}}$$, $$\mathbf{u_c} = \mathbf{u} - \mathbf{u^{\ast}}$$로 두면 최종적으로 아래를 얻는다.

$$
\begin{aligned}
\mathbf{\dot{e}} &= \mathbf{A}\mathbf{e} + \mathbf{B}\mathbf{u_c} \\
\text{where} \quad
\mathbf{A} &= 
\begin{bmatrix}
0 & 1 & 0 & 0 \\
0 & -\dfrac{\delta}{M} & \dfrac{mg}{M} & 0 \\
0 & 0 & 0 & 1 \\
0 & -\dfrac{\delta}{ML} & -\dfrac{(m+M)g}{ML} & 0
\end{bmatrix}, \quad
\mathbf{B} = 
\begin{bmatrix}
0 \\
\dfrac{1}{M} \\
0 \\
\dfrac{1}{ML}
\end{bmatrix}
\end{aligned}
$$

## III. Controllability 확인

이제 적당히 파라미터를 설정하고 controllability matrix를 구성해서 controllability를 확인해보자.

```python
import numpy as np

# Parameters.
m = 1.0
M = 5.0
L = 2.0
g = -9.81
delta = 1.0

# A matrix.
A = np.array(
    [
        [0, 1, 0, 0],
        [0, -delta / M, m * g / M, 0],
        [0, 0, 0, 1],
        [0, -delta / (M * L), -(m + M) * g / (M * L), 0],
    ]
)

# B matrix.
B = np.array([[0], [1 / M], [0], [1 / (M * L)]])

# Controllability matrix.
C = np.hstack((B, A @ B, A @ A @ B, A @ A @ A @ B))

# Check if the system is controllable.
if np.linalg.matrix_rank(C) == 4:
    print("The system is controllable.")
else:
    print("The system is not controllable.")
```

위 파라미터로 코드를 실행하면 이 시스템이 controllable하다는 걸 알 수 있다.

## IV. 제어 게인 설계

**Pole Placement 방법**

제어 입력이 없다면 ($$\mathbf{u} = \mathbf{0}$$) 어떻게 될까?
$$\mathbf{A}$$의 eigenvalue를 보면 양수가 포함되어 있다.
따라서 제어 없이는 시스템이 발산한다는 뜻이다.
여기서 명확히 하자. 
"발산한다"는 말은 $$\mathbf{e} = \mathbf{x} - \mathbf{x^{\ast}}$$가 0으로 수렴하지 못한다는 뜻이다.

```python
eigenvalues = np.linalg.eigvals(A)
print("Eigenvalues of A:", eigenvalues)
# Output: 
# Eigenvalues of A: [ 0.         -2.40772302 -0.23364538  2.4413684 ]
```

이제 게인 $$\mathbf{K}$$를 설정해서 폐루프 시스템의 eigenvalue를 음의 실수부로 옮기자.
우리가 원하는 위치에 eigenvalue를 지정하는 방법을 **pole placement**라고 부른다.

이 섹션에서는 두 가지 방법을 살펴본다:
1. 원하는 pole을 직접 지정 (정확한 동작 제어)
2. LQR로 자동 최적화 (성능 최적화)

### IV.1 방법 1: 직접 Pole 지정

`scipy.signal.place_poles`를 사용하면 원하는 pole을 직접 지정할 수 있다.
코드는 몹시 간단하다:

```python
from scipy.signal import place_poles

# Desired closed-loop poles.
desired_poles = np.array([-1, -1.5, -2, -2.5])
K = place_poles(A, B, desired_poles).gain_matrix
print("K:", K)

# Output:
# K: [[ -5.46089996 -15.01630989 247.28179991  98.03261978]]
```

### IV.2 방법 2: LQR 최적화

위 방법은 pole을 직접 지정하는 방식이다.
하지만 "어디에 pole을 두는 게 최적일까?"라는 질문에는 답하지 못한다.
**LQR (Linear Quadratic Regulator)**은 이 질문에 자동으로 답해주는 방법이다.
아래와 같은 비용 함수를 정의하고, 그를 최소화하는 최적 게인을 구한다.

**비용 함수 (Cost Function):**

$$
J = \int_0^\infty \left( \mathbf{e}^T \mathbf{Q} \mathbf{e} + \mathbf{u_c}^T \mathbf{R} \mathbf{u_c} \right) dt
$$

여기서:
- **$$\mathbf{Q}$$**: 상태 페널티 (대각 행렬) - 상태를 얼마나 빠르게 0에 수렴시킬지
- **$$\mathbf{R}$$**: 제어 페널티 (대각 행렬) - 제어 입력을 얼마나 절약할지

**Q와 R 행렬의 형태:**

이 예제 (뒤집힌 진자와 카트) 에서는 $$\mathbf{Q}$$ 와 $$\mathbf{R}$$ 은 아래와 같이 정의된다.

$$
\mathbf{Q} = \begin{bmatrix}
q_1 & 0 & 0 & 0 \\
0 & q_2 & 0 & 0 \\
0 & 0 & q_3 & 0 \\
0 & 0 & 0 & q_4
\end{bmatrix}, \quad
\mathbf{R} = \begin{bmatrix}
r
\end{bmatrix}
$$

- $$q_1$$: 카트 위치 제어 강도
- $$q_2$$: 카트 속도 제어 강도
- $$q_3$$: 진자 각도 제어 강도 (보통 가장 중요)
- $$q_4$$: 진자 각속도 제어 강도
- $$r$$: 제어 에너지 절약 강도 (클수록 에너지 절약)

**풀이 방법:**

최적 게인은 아래와 같이 생긴 **리카티 방정식 (Riccati Equation)**을 풀어서 구한다:

$$
\mathbf{A}^T\mathbf{P} + \mathbf{P}\mathbf{A} - \mathbf{P}\mathbf{B}\mathbf{R}^{-1}\mathbf{B}^T\mathbf{P} + \mathbf{Q} = \mathbf{0}
$$

유도 과정은 복잡한 비선형 최적화 이론을 거치는데, 나도 아직 살펴보지는 않았다.
하여튼 이 식을 풀면 대칭 행렬 $$\mathbf{P}$$ 를 얻고, 최적 게인은 아래와 같이 구할 수 있다.

$$
\mathbf{K} = \mathbf{R}^{-1}\mathbf{B}^T\mathbf{P}
$$

복잡해 보이지만, `scipy`로도 코드는 간단하다.

```python
from scipy.linalg import solve_continuous_are

# Cost function weights.
Q = np.diag([1, 1, 10, 1])
R = np.array([[1]])
# Solve continuous-time Riccati equation.
P = solve_continuous_are(A, B, Q, R)
# LQR gain: K = R^{-1} B^T P
K = np.linalg.inv(R) @ B.T @ P
print("K:", K)

# Output:
# K: [[ -1.          -5.0672681  158.72451348  64.20137372]]
```

## V. 시뮬레이션

위의 방법들을 구현한 완전한 코드와 시뮬레이션 결과는 [여기](https://github.com/i-am-wonseoklee/i-am-wonseoklee.github.io/tree/main/docs/control-theory/04-inverted-pendulum-cart/assets/src/inverted_pendulum_cart.py)에서 찾을 수 있다.

### V.1. 직접 Pole 배치하기

원하는 폐루프 pole을 $$\lambda = -1, -1.5, -2, -2.5$$로 지정했을 때의 시뮬레이션 결과는 아래와 같다.

![](/docs/control-theory/04-inverted-pendulum-cart/assets/figures/fig01.gif)

### V.2. LQR로 Pole 배치하기

$$\mathbf{Q} = \text{diag}(1, 1, 10, 1)$$, $$\mathbf{R} = 20$$으로 지정해서 Pole을 배치하면 아래와 같다.

![](/docs/control-theory/04-inverted-pendulum-cart/assets/figures/fig02.gif)