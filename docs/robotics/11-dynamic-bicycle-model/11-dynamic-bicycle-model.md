---
title: Dynamic Bicycle Model
layout: default
parent: Robotics
permalink: /docs/robotics/11-dynamic-bicycle-model
---

# Dynamic Bicycle Model

## TOC
{: .no_toc }

1. TOC
{:toc}

**Keywords:** `Dynamic Bicycle Model`{: .label }

그동안 필자에게 Bicycle Model은 곧 Kinematic Bicycle Model이었다.
언제든 아래 수식들이 자연스럽게 나올 정도로 익숙했다.

$$
\begin{align}
\dot{x}     & = v\cos{\psi} \\
\dot{y}     & = v\sin{\psi} \\
\dot{\psi}  & = \frac{v\tan{\delta}}{L} \\
\end{align}
$$

Kinematic Bicycle Model은 기본적으로 '휠 슬립(속도벡터와 각 바퀴 사이의 각)이 없다'고 가정한다.
과거에는 이 가정을 크게 신경 쓰지 않고 넘어갔다.
하지만 고속 주행, 특히 고속 선회 상황을 다룰 일이 많아지면서 휠 슬립을 수식에 반영할 필요성이 생겼다.
따라서 이번 포스팅에서는 휠 슬립을 고려하는 **Dynamic Bicycle Model**에 대해 정리해 본다.

## 1. 큰 그림 보기

이 섹션의 '큰 그림'은 비유적 표현이 아니라, 정말로 모델 유도의 기준이 되는 그림을 뜻한다.
수식 유도 과정에서는 어떤 좌표계를 기준으로 수식을 전개하는지 인지하는 것이 가장 중요하다.
따라서 아래 그림의 기하학적 관계와 좌표계를 명확히 숙지해야만 혼란을 피할 수 있다.

![fig00](/docs/robotics/11-dynamic-bicycle-model/images/fig00.drawio.png)

위 그림은 앞바퀴가 조향된 자전거 모델과 수식 유도에 필요한 주요 물리량들을 나타낸다.
좌표계별로 구성 요소를 살펴보면 다음과 같다.

- (파란색) 관성 좌표계 (고정 좌표계)
  - 자전거의 헤딩 각도는 $$\varphi$$ 이다.
  - 자전거는 각속도 $$\omega$$ 로 회전하고 있다 (강체이므로 어느 위치에서나 동일).
- (초록색) 바디 좌표계
  - 자전거의 종방향 속도는 $$v_x$$, 횡방향 속도는 $$v_y$$ 이다.
  - 전체 속도 벡터 $$v = v_x + v_y$$는 휠 슬립으로 인해 자전거의 헤딩 방향과 다를 수 있다.
  - 앞바퀴(조향륜)는 바디 좌표계를 기준으로 조향각 $$\delta$$ 를 갖는다.
- (빨강색) 타이어 좌표계
  - 차량의 거동을 만들어내는 각 타이어의 종방향/횡방향 힘을 나타낸다.
  - 후륜구동을 가정하므로 앞바퀴에는 종방향 힘을 표기하지 않았다.

## 2. 상태 및 제어 입력 정의

모델의 상태(State)와 제어 입력(Control input)을 다음과 같이 정의한다.
$$(x, y)$$는 관성 좌표계 기준 자전거 무게중심의 위치이며, 그 외 기호는 앞선 1번 섹션의 그림과 동일하다.

$$
\mathbf{x} = 
  \begin{bmatrix}
    x \\
    y \\
    \varphi \\
    v_x \\
    v_y \\
    \omega \\
  \end{bmatrix}, \quad

\mathbf{u} =
  \begin{bmatrix}
    F_{r,x} \\
    \delta  \\
  \end{bmatrix}
$$

## 3. 상태 방정식 유도

이제 상태 방정식 $$\dot{\mathbf{x}} = f(\mathbf{x}, \mathbf{u})$$를 유도한다.
이해를 돕기 위해 각 상태 변수별로 나누어 정리했다.

### 3.1. $$\dot{x}$$, $$\dot{y}$$, $$\dot{\varphi}$$

먼저 헤딩 각속도 $$\dot{\varphi}$$는 자명하게 $$\omega$$와 같다.
$$\dot{x}$$, $$\dot{y}$$는 관성 좌표계 기준의 속도이므로, 바디 좌표계의 속도 $$v_x$$, $$v_y$$를 회전 행렬을 통해 관성 좌표계로 변환($$\varphi$$만큼 회전)하면 쉽게 구할 수 있다.

$$
\begin{aligned}
  \begin{bmatrix}
    \dot{x} \\
    \dot{y} \\
  \end{bmatrix}
  & =
  \begin{bmatrix}
    \cos{\varphi} & -\sin{\varphi} \\
    \sin{\varphi} &  \cos{\varphi} \\
  \end{bmatrix}
  \begin{bmatrix}
    v_x \\
    v_y \\
  \end{bmatrix} \\
  & =
  \begin{bmatrix}
    \cos{\varphi} v_x - \sin{\varphi} v_y \\
    \sin{\varphi} v_x + \cos{\varphi} v_y \\
  \end{bmatrix}
\end{aligned}
$$

### 3.2. $$\dot{v_x}$$, $$\dot{v_y}$$

$$\dot{v_x}$$와 $$\dot{v_y}$$는 뉴턴의 제2법칙($$F=ma$$)을 적용하여 유도한다.
먼저 관성 좌표계 기준의 절대 가속도를 $$\mathbf{a}$$라 하면, [수송 정리](/docs/robotics/10-transport-theorem/)에 의해 다음 관계를 얻는다.

$$
\begin{aligned}
  \mathbf{a}
  & =
  \begin{bmatrix}
    \dot{v_x} \\
    \dot{v_y} \\
    0         \\
  \end{bmatrix}
  +
  \begin{bmatrix}
    0       \\
    0       \\
    \omega  \\
  \end{bmatrix}
  \times
  \begin{bmatrix}
    v_x \\
    v_y \\
    0   \\
  \end{bmatrix} \\
\end{aligned}
$$

가속도 벡터 $$\mathbf{a}$$를 **바디 좌표계 성분** $$[a_x, a_y, 0]^T$$로 나타내면 다음과 같다.

$$
\begin{aligned}
  \begin{bmatrix}
    a_x \\
    a_y \\
  \end{bmatrix}
  & =
  \begin{bmatrix}
    \dot{v_x} - \omega v_y \\
    \dot{v_y} + \omega v_x \\
  \end{bmatrix}
\end{aligned}
$$

{: .note }
> **아니, 관성-바디 좌표계에 대해 수송 정리를 쓰고 다시 바디 좌표계로 적는다는 게 무슨 개소리인가?**
>
> 이 식을 처음 접하면 누구나 두 가지 지점에서 혼란을 겪는다.
> 1. *"수송 정리는 좌표계를 변환하는 식인데, 왜 양변이 전부 바디 좌표계 성분인가?"*
> 2. *"원운동을 하는 회전 프레임인데, 왜 병진 가속도 항이 따로 안 보이는가?"*
>
> 혼란이 오는 이유는 **'기준 프레임(Reference Frame)'**과 **'표현 좌표계(Expressed-in Frame)'**를 혼동했기 때문이다.
>
> - **수송 정리는 좌표 변환이 아니다**: 수송 정리는 좌표계를 바꿔주는(회전 행렬 $$R$$) 식이 아니라, 회전축에서 성분만 미분한 '겉보기 미분($$\dot{\mathbf{v}}$$)'을 관성계 기준의 '진짜 물리 미분($$\mathbf{a}$$)'으로 보정해 주는 기하학적 벡터 항등식이다.
> - **속도 $$\mathbf{v}$$는 자유 벡터(Free Vector)다**: 위치(Position)는 기준 원점에 묶여 있으므로 원점 이동 항($$\mathbf{r}_{\text{origin}}$$)이 개입하지만, 속도 $$\mathbf{v}$$는 원점과 무관하게 공간에 존재하는 물리적 화살표다. 따라서 별도의 원점 병진 항 없이 $$\mathbf{v}$$ 자체에 수송 정리를 곧바로 적용한다. (선회에 의한 구심 가속도 역시 이미 $$\boldsymbol{\omega} \times \mathbf{v}$$ 안에 포함되어 있다!)
> - **기준과 표현의 분리**: 수송 정리로 얻은 가속도 $$\mathbf{a}$$는 **관성계 기준**의 진짜 가속도이지만, 계산의 편의(타이어 힘과의 결합)를 위해 단지 **바디 좌표계 축에 투영**해서 $$[a_x, a_y, 0]^T$$로 적은 것뿐이다.

이제 바디 좌표계의 $$x$$축(종방향)과 $$y$$축(횡방향)에 대해 뉴턴의 제2법칙을 각각 적용하면 다음 상태 방정식을 얻는다.

$$
\begin{aligned}
  M(\dot{v_x} - \omega v_y) & = F_{r,x} - F_{f, y} \sin{\delta}                       \\
  \Rightarrow \dot{v_x} & = \frac{1}{M}(F_{r,x} - F_{f, y} \sin{\delta}) + \omega v_y \\
  M(\dot{v_y} + \omega v_x) & = F_{r,y} + F_{f, y} \cos{\delta}                       \\
  \Rightarrow \dot{v_y} & = \frac{1}{M}(F_{r,y} + F_{f, y} \cos{\delta}) - \omega v_x \\
\end{aligned}
$$

### 3.3. $$\dot{\omega}$$

$$\dot{\omega}$$는 회전 운동에 대한 뉴턴-오일러 방정식($$\sum \tau = I_z \dot{\omega}$$)을 적용하여 유도한다.
무게중심에서 전륜 및 후륜 축까지의 거리를 각각 $$l_f$$, $$l_r$$라 하면 다음 상태 방정식을 얻는다.

$$
\dot{\omega} = \frac{1}{I_z}(l_f F_{f, y} \cos{\delta} - l_r F_{r, y})
$$

### 3.4. $$F_{f, y}$$, $$F_{r, y}$$

이제 상태 변수도, 제어 입력도 아닌 미지수는 타이어 횡력 $$F_{f, y}$$와 $$F_{r, y}$$뿐이다.
타이어 횡력은 노면 마찰 특성상 강한 비선형성을 띠며, 이를 모델링할 때 널리 쓰이는 대표적인 식이 **Pacejka의 Magic Formula**이다.
네덜란드 공학자 Hans B. Pacejka의 이름에서 따왔으며, 원어 발음은 **'파세이카'**에 가까우나 국내에서는 **'파제카'**로 흔히 불린다.
여기서 $$B, C, D, E$$는 실험 데이터로 피팅하는 타이어 형상 계수들이며, $$\alpha$$는 **슬립 앵글(Slip angle)**이다.
결국 슬립 앵글 $$\alpha$$만 상태 변수들로 표현하면 횡력을 계산할 수 있다.

$$
F_y = D \sin\left(C \arctan\left(B\alpha - E(B\alpha - \arctan(B\alpha))\right)\right)
$$

슬립 앵글은 **바퀴가 향하는 방향과 바퀴 중심의 실제 속도 벡터 사이의 사잇각**으로 정의된다.
아래 서브섹션에서 전/후륜 각각의 슬립 앵글을 구한다. 이 과정에서도 수송 정리가 쓰이니 유념하자.

#### 3.4.1. 전륜 슬립 앵글 ($$\alpha_f$$)

관성 좌표계 기준 전륜의 위치를 $$\mathbf{r}_f$$, 무게중심 위치를 $$\mathbf{r}_{\text{CoM}}$$, 무게중심에서 전륜까지의 상대 위치 벡터를 $$\mathbf{r}_{f/\text{CoM}}$$이라 하면 위치 관계식은 다음과 같다.

$$
\mathbf{r}_f = \mathbf{r}_{\text{CoM}} + \mathbf{r}_{f/\text{CoM}}
$$

이를 시간에 대해 미분하여 전륜의 절대 속도 $$\mathbf{v}_f$$를 구할 때, 바디 좌표계에 대해 회전하는 상대 위치 벡터 $$\mathbf{r}_{f/\text{CoM}}$$에 수송 정리를 적용한다.
전륜은 차량 바디에 고정된 점이므로 바디 좌표계에서 관찰한 상대 속도는 $$\mathbf{0}$$이다.

$$
\begin{aligned}
  \mathbf{v}_f
  & = \left(\frac{d\mathbf{r}_f}{dt}\right)_I \\
  & = \underbrace{\left(\frac{d\mathbf{r}_{\text{CoM}}}{dt}\right)_I}_{\mathbf{v}}
    + \left[ \underbrace{\left(\frac{d\mathbf{r}_{f/\text{CoM}}}{dt}\right)_B}_{=\mathbf{0}} + \boldsymbol{\omega} \times \mathbf{r}_{f/\text{CoM}} \right] \\
  & = \mathbf{v} + \boldsymbol{\omega} \times \mathbf{r}_{f/\text{CoM}}
\end{aligned}
$$

따라서 바디 좌표계 기준 $$\mathbf{r}_{f/\text{CoM}} = [l_f, 0, 0]^T$$를 대입하면 전륜의 속도 벡터 $$\mathbf{v}_f$$를 얻는다.
3.2절과 마찬가지로, $$\mathbf{v}_f$$ 자체는 **관성계 기준의 절대 속도 벡터**이다. 다만 바디 기준 조향각($$\delta$$)과의 사잇각을 쉽게 구하기 위해 **바디 좌표계 성분으로 나타낸 것**뿐이다.

$$
\begin{aligned}
  \mathbf{v}_f
  & = \mathbf{v} + \boldsymbol{\omega} \times \mathbf{r}_{f/\text{CoM}} \\
  & =
  \begin{bmatrix}
    v_x \\
    v_y \\
    0   \\
  \end{bmatrix}
  +
  \begin{bmatrix}
    0      \\
    0      \\
    \omega \\
  \end{bmatrix}
  \times
  \begin{bmatrix}
    l_f \\
    0   \\
    0   \\
  \end{bmatrix} \\
  & =
  \begin{bmatrix}
    v_x \\
    v_y + l_f \omega \\
    0   \\
  \end{bmatrix}
\end{aligned}
$$

바디 좌표계 기준 전륜 속도 벡터의 진행각은 $$\arctan\left(\frac{v_y + l_f \omega}{v_x}\right)$$이고, 바퀴의 조향각은 $$\delta$$이다. 따라서 전륜 슬립 앵글 $$\alpha_f$$는 다음과 같다.

$$
\alpha_f = \delta - \arctan\left(\frac{v_y + l_f \omega}{v_x}\right)
$$

#### 3.4.2. 후륜 슬립 앵글 ($$\alpha_r$$)

마찬가지로 무게중심에서 후륜까지의 상대 위치 벡터는 바디 좌표계 기준 $$\mathbf{r}_{r/\text{CoM}} = [-l_r, 0, 0]^T$$이다. 동일하게 수송 정리를 적용하면 후륜의 속도 벡터 $$\mathbf{v}_r$$를 얻는다.

$$
\begin{aligned}
  \mathbf{v}_r
  & = \mathbf{v} + \boldsymbol{\omega} \times \mathbf{r}_{r/\text{CoM}} \\
  & =
  \begin{bmatrix}
    v_x \\
    v_y \\
    0   \\
  \end{bmatrix}
  +
  \begin{bmatrix}
    0      \\
    0      \\
    \omega \\
  \end{bmatrix}
  \times
  \begin{bmatrix}
    -l_r \\
    0    \\
    0    \\
  \end{bmatrix} \\
  & =
  \begin{bmatrix}
    v_x \\
    v_y - l_r \omega \\
    0   \\
  \end{bmatrix}
\end{aligned}
$$

후륜은 조향되지 않으므로(조향각 $$0$$), 후륜 슬립 앵글 $$\alpha_r$$는 다음과 같다.

$$
\alpha_r = - \arctan\left(\frac{v_y - l_r \omega}{v_x}\right)
$$

이로써 슬립 앵글 $$\alpha_f, \alpha_r$$이 모두 상태 변수($$v_x, v_y, \omega$$)와 제어 입력($$\delta$$)으로 표현되었다. 이를 타이어 모델에 대입해 횡력 $$F_{f, y}, F_{r, y}$$를 구하면 Dynamic Bicycle Model의 모든 상태 방정식 유도가 완성된다.

## 4. 요약

앞선 섹션들에서 유도한 상태 방정식을 종합하면, 최종적인 **Dynamic Bicycle Model**은 다음과 같이 행렬(벡터) 형태로 정리할 수 있다.

$$
\dot{\mathbf{x}} =
\begin{bmatrix}
  \dot{x}       \\
  \dot{y}       \\
  \dot{\varphi} \\
  \dot{v_x}     \\
  \dot{v_y}     \\
  \dot{\omega}  \\
\end{bmatrix}
=
\begin{bmatrix}
  \cos{\varphi} v_x - \sin{\varphi} v_y                       \\
  \sin{\varphi} v_x + \cos{\varphi} v_y                       \\
  \omega                                                      \\
  \frac{1}{M}(F_{r,x} - F_{f, y} \sin{\delta}) + \omega v_y   \\
  \frac{1}{M}(F_{r,y} + F_{f, y} \cos{\delta}) - \omega v_x   \\
  \frac{1}{I_z}(l_f F_{f, y} \cos{\delta} - l_r F_{r, y})     \\
\end{bmatrix}
$$

이때 타이어 횡력 $$F_{f, y}$$, $$F_{r, y}$$는 Pacejka 모델(혹은 선형 근사 모델 $$F_y \approx C_\alpha \alpha$$)을 통해 계산되며, 대입되는 전·후륜 슬립 앵글은 다음과 같다.

$$
\begin{aligned}
  \alpha_f & = \delta - \arctan\left(\frac{v_y + l_f \omega}{v_x}\right) \\
  \alpha_r & = - \arctan\left(\frac{v_y - l_r \omega}{v_x}\right)
\end{aligned}
$$

이로써 서론에서 언급했던 '휠 슬립이 발생하는 고속 주행 및 선회 시나리오'를 시뮬레이션하고 제어할 수 있는 완전한 비선형 차량 동역학 모델이 완성된다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
