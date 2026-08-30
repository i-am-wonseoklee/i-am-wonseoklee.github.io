---
title: Transport Theorem
layout: default
parent: Robotics
permalink: /docs/robotics/10-transport-theorem
---

# Transport Theorem

## TOC
{: .no_toc }

1. TOC
{:toc}

**Keywords:** `Transport Theorem`{: .label }

"Transport Theorem", 조금 더 익숙하게 국문으로는 "수송 정리"라고 부른다.
어쩌면 이 정리는 간단한 물리 혹은 기하와 관련한 포스팅에서 다루는 것이 맞을지도 모르겠다.
하지만, 필자는 이 정리를 Dynamic Bicycle Model을 유도하는 과정에 주로 사용했기 때문에 로보틱스 관련 카테고리에 넣기로 마음먹었다.
수송 정리가 다루고자 하는 질문 자체는 생각보다 간단하며, 아래와 같다.

- 회전하고 있는 프레임 상에서 관찰한 변화를 고정된 프레임 기준으로 어떻게 변환할까?

조금 더 직관적으로 상황을 예로 들어보면 다음과 같다.

- 좌표계 A의 원점에 철수가 서있다.
- 철수와 일정 거리만큼 떨어진 곳에 좌표계 B의 원점이 있고, 여기에 영희가 서있다. (물론 같은 위치에 있어도 상관없다.)
- 영희가 있는 좌표계 B는 공간 상의 고정된 위치에서 일정한 각속도로 팽이처럼 제자리 회전을 하고 있다.
- 영희는 좌표계 B에서 시간에 따라 변화하는 벡터 $$\mathbf{p}$$의 변화량 $$\left( \frac{d\mathbf{p}}{dt} \right)_{B}$$를 관찰했다.
- 이때, 좌표계 A에서 관찰되는 동일한 벡터의 변화량 $$\left( \frac{d\mathbf{p}}{dt} \right)_{A}$$는 무엇일까 하는 것이 질문의 요체이다.

결론만 놓고 보았을 때는 식도 간단했고 심지어 외우기도 쉬웠다.
하지만, 곰곰이 생각해보니 "응? 이건 왜 이렇지?"하고 고개를 갸우뚱하게 되는 순간이 더러 있었다.
따라서, 블로그에 이해 과정을 꼼꼼히 기록해두려고 한다.

## I. 회전 벡터

수송 정리를 본격적으로 설명하기에 앞서 "회전 벡터" (Rotation Vector) 라는 것이 무엇인지를 설명해야 한다.
만약, 이미 "회전 벡터"에 대해 잘 알고 있다면 이 챕터는 스킵해도 된다.

### I.1. 회전 벡터의 정의

3차원 공간에서 어떤 강체가 회전했다는 사실을 남에게 전달하려면 무엇을 알려주어야 할까?
생각해보면 딱 두 가지, **어떤 축을 중심으로 돌았는지**와 **얼마나 돌았는지**만 알려주면 충분하다.
그래서 회전축 방향의 단위 벡터를 $$\hat{\mathbf{n}}$$, 회전한 각을 $$\theta$$라고 두고, 이 둘을 하나로 묶은 아래의 벡터를 **회전 벡터**라고 부른다.

$$
\boldsymbol{\theta} = \theta \hat{\mathbf{n}}
$$

방향은 회전축을, 크기는 회전량을 나타내는 셈이니 (i.e., $$\lvert \boldsymbol{\theta} \rvert = \theta$$) 필요한 정보를 낭비 없이 담고 있는 표현이다.
참고로 $$\hat{\mathbf{n}}$$의 부호는 오른손 법칙 (right-hand rule) 으로 정한다.
오른손 엄지를 $$\hat{\mathbf{n}}$$ 방향으로 세웠을 때 나머지 네 손가락이 감기는 방향이 $$\theta > 0$$인 방향이다.

### I.2. 회전 벡터는 정말 "벡터"일까?

필자가 처음 뇌정지를 겪었던 지점이 바로 여기다.
어떤 양을 벡터라고 부르려면 크기와 방향을 갖는 것만으로는 부족하고, 평행사변형 법칙에 따라 **더할 수 있어야** 한다.
그런데 회전 벡터는 이 조건을 만족하지 않는다.

말로 하면 와닿지 않으니 스마트폰을 하나 집어 들고 직접 해보자.
화면이 나를 향하도록 스마트폰을 세워 들고, 아래 두 회전을 순서를 바꿔서 각각 해보는 것이다.
여기서 두 회전의 축은 모두 **그 회전을 시작하는 순간에 폰에 붙어 있는 축**이다.
달리 말해 세계에 고정된 축이 아니라, 앞선 회전으로 이미 함께 틀어진 폰의 현재 축을 말한다.

- 회전 A: 폰의 좌우 축을 중심으로 $$90^{\circ}$$ 눕히기 (처음 자세에서 하면 화면이 천장을 향하게 된다)
- 회전 B: 폰의 위아래 축을 중심으로 $$90^{\circ}$$ 돌리기 (처음 자세에서 하면 화면이 오른쪽을 향하게 된다)

$$A \to B$$ 순서로 하면 화면이 오른쪽을 향하지만, $$B \to A$$ 순서로 하면 화면이 천장을 향한다.
같은 두 회전을 순서만 바꿨는데 결과가 전혀 다른 곳에 도착한 것이다 (i.e., $$R_A R_B \neq R_B R_A$$).
반면 벡터의 덧셈은 순서를 바꿔도 결과가 같으므로 (i.e., $$\mathbf{u} + \mathbf{v} = \mathbf{v} + \mathbf{u}$$), 회전 벡터를 벡터처럼 더하는 것은 애초에 말이 되지 않는다.

{: .warning }
> 즉, 회전 벡터는 하나의 회전을 **표기**하는 데는 훌륭하지만 그것들을 벡터처럼 더할 수는 없다.

일반적으로 회전 벡터는 더하는 것만으로 두개의 회전을 표현할 수 없지만 회전량을 조금씩 줄여가며 같은 실험을 반복하면 재미있는 일이 벌어진다.
$$90^{\circ}$$가 아니라 $$1^{\circ}$$씩만 돌린다면, 순서를 바꿔봐도 스마트폰이 도착하는 위치가 사실상 구별되지 않는다.
이 "사실상 구별되지 않는다"를 숫자로 적어보고 싶은데, 그러려면 **두 자세가 얼마나 다른지를 재는 방법**을 먼저 정해야 한다.
자세는 숫자가 아니어서 두 자세를 그냥 뺄 수가 없으니 난감해 보인다.
다행히 회전에는 아래와 같은 편리한 성질이 있다.

- 어떤 자세에서 다른 어떤 자세로 옮겨가는 일은, 적당한 축을 하나 잘 잡으면 **언제나 딱 한 번의 회전으로** 끝낼 수 있다. (오일러 회전 정리)

그러니 재는 방법은 자연스럽게 정해진다.
$$A \to B$$로 끝난 폰과 $$B \to A$$로 끝난 폰을 나란히 놓고, **한쪽을 다른 쪽에 정확히 겹치려면 추가로 몇 도를 더 돌려야 하는지**를 세면 되는 것이다.
이 각을 두 순서의 "차이"로 삼자.
겹치는 데 필요한 각이 $$0^{\circ}$$라면 두 결과가 같다는 뜻이고, 클수록 두 결과가 멀리 떨어져 있다는 뜻이니 우리가 원하는 척도로 쓸 만하다.
앞서 해본 $$90^{\circ}$$ 실험의 경우 이 값이 $$120^{\circ}$$다.
화면이 오른쪽을 향한 폰을 화면이 천장을 향한 폰에 겹치려면, 어떤 비스듬한 축을 중심으로 $$120^{\circ}$$나 더 돌려야 한다는 뜻이다.
이제 회전량을 줄여가며 이 값을 계산해보면 아래와 같다.

| 각 회전의 회전량 | 두 순서의 결과 차이 | 회전량 대비 비율 |
|:---|:---|:---|
| 90°  | 120°     | 133 %  |
| 45°  | 33.7°    | 74.9 % |
| 20°  | 6.91°    | 34.6 % |
| 10°  | 1.74°    | 17.4 % |
| 5°   | 0.436°   | 8.72 % |
| 1°   | 0.0175°  | 1.75 % |

{: .highlight }
> 직접 계산해보고 싶은 독자를 위해 방법을 적어둔다.
> $$A \to B$$의 결과를 $$R_1 = R_A R_B$$, $$B \to A$$의 결과를 $$R_2 = R_B R_A$$라고 하면, $$R_1$$에서 $$R_2$$로 옮겨가는 회전은 $$D = R_2 R_1^{-1}$$이다.
> 그리고 임의의 회전 행렬 $$D$$의 회전각 $$\phi$$는 $$\mathrm{tr}(D) = 1 + 2\cos\phi$$로 구할 수 있다.
> 위 표의 두 번째 열은 회전량을 바꿔가며 이 $$\phi$$를 계산한 것이다.

표에서 규칙 하나가 눈에 들어온다.
**회전량을 절반으로 줄이면 순서에 따른 차이는 1/4로 줄어든다.**
$$10^{\circ}$$에서 $$5^{\circ}$$로 갈 때 차이가 $$1.74^{\circ}$$에서 $$0.436^{\circ}$$로 줄어든 것이 그 예다.
즉, 차이는 회전량의 **제곱**에 비례한다.
왜 제곱일까?
두 순서의 결과가 벌어지는 것은 앞의 회전이 뒤의 회전이 쓸 축을 미리 틀어놓기 때문인데, 이 어긋남이 실제 차이로 드러나려면 **두 회전을 모두 거쳐야** 한다.
그러니 차이의 크기는 두 회전량의 곱, 즉 $$\Delta\theta \times \Delta\theta$$에 비례하게 된다.
여기서 중요한 것은 회전량은 1차로 줄어드는데 차이는 2차로 줄어든다는 점이다.
그래서 회전량을 계속 작게 만들면 표의 마지막 열처럼 **회전량 대비 차이의 비율이 0으로 수렴한다**.
결국 무한히 작은 회전, 즉 미소 회전에서는 순서를 따지는 것이 무의미해지고, 아래와 같이 회전 벡터를 그냥 더해도 된다.

$$
R(\Delta\boldsymbol{\theta}_1) R(\Delta\boldsymbol{\theta}_2) \approx R(\Delta\boldsymbol{\theta}_1 + \Delta\boldsymbol{\theta}_2)
$$

{: .note }
> 정리하면, 유한한 회전은 벡터가 아니지만 **미소 회전은 벡터라고 부를 자격이 있다.**
> 이 사실이 II장에서 다룰 각속도 벡터를 떠받치는 근거가 된다.

### I.3. 미소 회전을 행렬로 확인해보기

앞 절의 결론은 표와 말로 얻은 것이라 찜찜할 수 있으니, 식으로도 확인해보자.
결론을 이미 받아들였다면 이 절은 건너뛰어도 무방하다.
먼저 왜 하필 **행렬**을 꺼내는지부터 짚어두자.
우리가 확인하려는 것은 "두 회전을 이어서 했을 때" 무슨 일이 벌어지는지인데, 회전을 이어서 하는 것은 회전 행렬의 **곱셈**으로 표현된다.
회전 벡터 $$\boldsymbol{\theta}$$는 회전 하나를 적어두기에는 편하지만 두 개를 이어 붙이는 연산이 없으므로, 계산을 하려면 행렬로 옮겨 타야 한다.

#### 외적을 행렬로 쓰기

미소 회전 행렬을 적으려면 $$[\mathbf{a}]_{\times}$$라는 낯선 기호가 하나 필요하다.
겁먹을 것 없이, 이것은 **이미 알고 있는 외적을 행렬 곱으로 다시 쓴 것**에 불과하다.
두 벡터의 외적을 성분으로 풀어 쓰면 아래와 같다.

$$
\mathbf{a} \times \mathbf{v} =
\begin{bmatrix} a_2 v_3 - a_3 v_2 \\ a_3 v_1 - a_1 v_3 \\ a_1 v_2 - a_2 v_1 \end{bmatrix}
$$

여기서 $$\mathbf{a}$$를 고정된 것으로 보면, 결과의 각 성분은 $$v_1, v_2, v_3$$에 대한 1차식이다.
$$\mathbf{v}$$에 대한 1차식은 곧 "어떤 행렬 곱하기 $$\mathbf{v}$$"로 쓸 수 있다는 뜻이므로, 위 식은 아래와 같이 정리된다.

$$
\mathbf{a} \times \mathbf{v} =
\underbrace{\begin{bmatrix} 0 & -a_3 & a_2 \\ a_3 & 0 & -a_1 \\ -a_2 & a_1 & 0 \end{bmatrix}}_{[\mathbf{a}]_{\times}}
\begin{bmatrix} v_1 \\ v_2 \\ v_3 \end{bmatrix}
$$

의심스러우면 직접 곱해보면 된다.
첫 번째 행을 곱하면 $$0 \cdot v_1 - a_3 v_2 + a_2 v_3$$이고, 이것은 위 외적의 첫 번째 성분 $$a_2 v_3 - a_3 v_2$$와 같다.
나머지 두 행도 마찬가지다.
즉, $$[\mathbf{a}]_{\times}$$는 "$$\mathbf{a}$$와 외적을 한다"는 **행위 자체를 행렬 하나로 굳혀놓은 것**이고, 아래와 같이 읽으면 된다.

$$
[\mathbf{a}]_{\times} \mathbf{v} = \mathbf{a} \times \mathbf{v}
$$

#### 미소 회전 행렬의 1차 근사

이제 미소 회전 행렬을 적어보자.
일반적인 축은 뒤에서 이야기하고, 우선 축을 $$z$$축으로 잡자.
$$z$$축을 중심으로 $$\theta$$만큼 도는 회전 행렬은 익숙한 아래의 모양이다.

$$
R_z(\theta) =
\begin{bmatrix} \cos\theta & -\sin\theta & 0 \\ \sin\theta & \cos\theta & 0 \\ 0 & 0 & 1 \end{bmatrix}
$$

여기에 $$\theta$$가 아주 작을 때의 근사를 넣는다.
라디안 단위에서 $$\sin$$과 $$\cos$$의 테일러 급수는 아래와 같다.

$$
\sin\theta = \theta - \frac{\theta^3}{6} + \cdots, \quad
\cos\theta = 1 - \frac{\theta^2}{2} + \cdots
$$

$$\Delta\theta$$가 아주 작다면 $$\Delta\theta^2$$ 이상의 항은 버려도 되므로 $$\sin\Delta\theta \approx \Delta\theta$$, $$\cos\Delta\theta \approx 1$$이다.
이것을 대입해서 정리하면 아래와 같다.

$$
R_z(\Delta\theta) \approx
\begin{bmatrix} 1 & -\Delta\theta & 0 \\ \Delta\theta & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}
= \underbrace{\begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}}_{I}
+ \begin{bmatrix} 0 & -\Delta\theta & 0 \\ \Delta\theta & 0 & 0 \\ 0 & 0 & 0 \end{bmatrix}
$$

여기서 두 번째 행렬을 자세히 보자.
지금 다루고 있는 회전은 $$z$$축 중심 $$\Delta\theta$$ 회전이므로, 그 회전 벡터는 $$\Delta\boldsymbol{\theta} = (0, 0, \Delta\theta)$$다.
이것을 바로 앞에서 만든 $$[\mathbf{a}]_{\times}$$ 꼴에 그대로 대입해보자 (i.e., $$a_1 = 0$$, $$a_2 = 0$$, $$a_3 = \Delta\theta$$).

$$
[\Delta\boldsymbol{\theta}]_{\times} =
\begin{bmatrix} 0 & -a_3 & a_2 \\ a_3 & 0 & -a_1 \\ -a_2 & a_1 & 0 \end{bmatrix}
= \begin{bmatrix} 0 & -\Delta\theta & 0 \\ \Delta\theta & 0 & 0 \\ 0 & 0 & 0 \end{bmatrix}
$$

두 번째 행렬과 정확히 같다.
즉, 우리가 얻은 것은 아래의 식이다.

$$
R(\Delta\boldsymbol{\theta}) \approx I + [\Delta\boldsymbol{\theta}]_{\times}
$$

축을 $$z$$축으로 잡은 것은 계산을 편하게 하려고 좌표계를 유리하게 고른 것일 뿐이다.
임의의 축 $$\hat{\mathbf{n}}$$에 대해서도 좌표계를 돌려 $$\hat{\mathbf{n}}$$이 $$z$$축이 되게 만든 뒤 위 계산을 하고 좌표계를 되돌리면 같은 결론을 얻으므로, 이 식은 축에 무관하게 성립한다.

{: .note }
> 이 식을 말로 읽으면 이렇다.
> "아주 조금 회전시키는 것은, 원래 벡터를 그대로 두고 ($$I$$) 거기에 회전 벡터와의 외적을 더해주는 것 ($$[\Delta\boldsymbol{\theta}]_{\times}$$) 과 같다."
> 즉, 임의의 벡터 $$\mathbf{v}$$에 대해 $$R(\Delta\boldsymbol{\theta})\mathbf{v} \approx \mathbf{v} + \Delta\boldsymbol{\theta} \times \mathbf{v}$$이다.
> 회전과 외적이 이렇게 붙어 있다는 사실이 다음 챕터 내용의 씨앗이 된다.

#### 두 미소 회전의 합성

준비가 끝났으니 두 개의 미소 회전을 이어서 적용해보자.

$$
\begin{align*}
R(\Delta\boldsymbol{\theta}_1) R(\Delta\boldsymbol{\theta}_2) & \approx (I + [\Delta\boldsymbol{\theta}_1]_{\times})(I + [\Delta\boldsymbol{\theta}_2]_{\times}) \\
& = I + [\Delta\boldsymbol{\theta}_1]_{\times} + [\Delta\boldsymbol{\theta}_2]_{\times} + [\Delta\boldsymbol{\theta}_1]_{\times}[\Delta\boldsymbol{\theta}_2]_{\times} \\
& \approx I + [\Delta\boldsymbol{\theta}_1]_{\times} + [\Delta\boldsymbol{\theta}_2]_{\times} \\
& = I + [\Delta\boldsymbol{\theta}_1 + \Delta\boldsymbol{\theta}_2]_{\times} \\
& = R(\Delta\boldsymbol{\theta}_1 + \Delta\boldsymbol{\theta}_2)
\end{align*}
$$

세 번째 줄에서 $$[\Delta\boldsymbol{\theta}_1]_{\times}[\Delta\boldsymbol{\theta}_2]_{\times}$$를 버렸는데, 버려도 되는 이유는 이렇다.
$$[\Delta\boldsymbol{\theta}_1]_{\times}$$의 성분은 모두 $$\Delta\theta_1$$에 비례하고, $$[\Delta\boldsymbol{\theta}_2]_{\times}$$의 성분은 모두 $$\Delta\theta_2$$에 비례한다.
그러니 이 둘을 곱한 항은 $$\Delta\theta_1 \Delta\theta_2$$에 비례하는 2차 항이다.
반면 살아남은 두 항은 각각 1차다.
회전량을 작게 만들면 2차 항이 1차 항보다 훨씬 빠르게 사라지므로 버릴 수 있는 것이다.
네 번째 줄에서는 $$[\mathbf{a}]_{\times} + [\mathbf{b}]_{\times} = [\mathbf{a} + \mathbf{b}]_{\times}$$를 사용했다.
$$[\mathbf{a}]_{\times}$$의 성분이 $$\mathbf{a}$$의 성분을 부호만 바꿔 늘어놓은 것이니 자명하게 성립한다.
최종 결과 $$R(\Delta\boldsymbol{\theta}_1 + \Delta\boldsymbol{\theta}_2)$$는 첨자 $$1$$과 $$2$$를 맞바꿔도 똑같다.
따라서 미소 회전은 순서를 바꾸어도 결과가 같고, 그 합성이 **회전 벡터의 덧셈**과 정확히 대응된다.
I.2에서 표를 보고 짐작했던 결론이 식으로도 확인된 셈이다.

## II. 각속도 벡터

앞선 챕터의 회전 벡터는 "회전이라는 상태"를 표기하는 도구였다.
수송 정리는 시간에 따른 변화를 다루는 정리이므로, 이제 그 표기를 시간으로 미분해서 "회전이라는 운동"을 다루는 도구로 바꿀 차례다.

### II.1. 각속도 벡터의 정의

미소 회전 벡터를 시간으로 나눈 것을 **각속도 벡터** (angular velocity vector) 라고 하고, 보통 $$\boldsymbol{\omega}$$로 쓴다.

$$
\boldsymbol{\omega} = \lim_{\Delta t \to 0} \frac{\Delta\boldsymbol{\theta}}{\Delta t}
$$

I.2와 I.3에서 미소 회전끼리는 순서에 무관하게 더해진다는 것을 확인했으므로, 그것을 시간으로 나눈 각속도 벡터는 마음 놓고 벡터라고 불러도 된다.
따라서 아래와 같이 각속도끼리 자유롭게 더할 수 있는데, 이 성질은 여러 개의 회전 프레임이 겹쳐 있는 상황을 다룰 때 요긴하게 쓰인다.

$$
\boldsymbol{\omega} = \boldsymbol{\omega}_1 + \boldsymbol{\omega}_2
$$

### II.2. 회전하는 벡터의 시간 변화율

이제 수송 정리를 위해 진짜로 필요한 결과를 하나 얻어보자.
원점을 지나는 축 $$\hat{\mathbf{n}}$$을 중심으로 각속도 $$\boldsymbol{\omega} = \omega\hat{\mathbf{n}}$$로 회전하는 강체를 생각하고, 그 강체에 박혀 있는 위치 벡터 $$\mathbf{r}$$을 하나 잡자.
$$\mathbf{r}$$을 회전축에 평행한 성분과 수직인 성분으로 쪼개면 아래와 같다.

$$
\mathbf{r} = \mathbf{r}_{\parallel} + \mathbf{r}_{\perp}, \quad \mathbf{r}_{\parallel} = (\mathbf{r} \cdot \hat{\mathbf{n}}) \hat{\mathbf{n}}
$$

여기까지의 설정을 그림으로 그리면 아래와 같다.
회색 점선은 회전에 따라 $$\mathbf{r}$$의 끝점이 그리는 원이고, 초록색 화살표는 이제부터 유도할 결과다.

![fig01](/docs/robotics/10-transport-theorem/images/fig01.png)

축에 평행한 성분 $$\mathbf{r}_{\parallel}$$은 축을 중심으로 돌아도 전혀 변하지 않는다.
따라서 $$\mathbf{r}$$의 변화는 전부 $$\mathbf{r}_{\perp}$$에서 나오는데, $$\mathbf{r}_{\perp}$$는 반지름 $$\lvert \mathbf{r}_{\perp} \rvert$$인 원 위를 각속도 $$\omega$$로 돌고 있는 벡터일 뿐이다.
그러므로 시간 $$\Delta t$$ 동안 $$\mathbf{r}_{\perp}$$의 끝점은 호의 길이 $$\lvert \mathbf{r}_{\perp} \rvert \omega \Delta t$$만큼, $$\hat{\mathbf{n}} \times \mathbf{r}_{\perp}$$ 방향으로 움직인다.
이를 정리하면 아래와 같다.

$$
\begin{align*}
\Delta\mathbf{r} & \approx \lvert \mathbf{r}_{\perp} \rvert \, \omega \, \Delta t \cdot \frac{\hat{\mathbf{n}} \times \mathbf{r}_{\perp}}{\lvert \hat{\mathbf{n}} \times \mathbf{r}_{\perp} \rvert} \\
& = \lvert \mathbf{r}_{\perp} \rvert \, \omega \, \Delta t \cdot \frac{\hat{\mathbf{n}} \times \mathbf{r}_{\perp}}{\lvert \mathbf{r}_{\perp} \rvert} \quad - \because \hat{\mathbf{n}} \perp \mathbf{r}_{\perp}, \, \lvert \hat{\mathbf{n}} \rvert = 1 \\
& = \omega \, \Delta t \, (\hat{\mathbf{n}} \times \mathbf{r}_{\perp}) \\
& = \omega \, \Delta t \, (\hat{\mathbf{n}} \times (\mathbf{r} - \mathbf{r}_{\parallel})) \\
& = \omega \, \Delta t \, (\hat{\mathbf{n}} \times \mathbf{r}) \quad - \because \hat{\mathbf{n}} \times \mathbf{r}_{\parallel} = \mathbf{0}
\end{align*}
$$

양변을 $$\Delta t$$로 나누고 $$\Delta t \to 0$$의 극한을 취하면 최종적으로 아래를 얻는다.

$$
\dot{\mathbf{r}} = \omega \hat{\mathbf{n}} \times \mathbf{r} = \boldsymbol{\omega} \times \mathbf{r}
$$

{: .note }
> 말로 풀면 "회전하는 강체에 박혀 있는 벡터의 시간 변화율은 각속도 벡터와 그 벡터의 외적과 같다"는 뜻이다.
> 다음 챕터에서 수송 정리를 유도할 때 사용할 핵심 도구이니 이 식만큼은 꼭 기억해두자.

## III. 수송 정리의 유도

준비가 모두 끝났다.
이제 맨 처음에 던졌던 질문으로 돌아가보자.

- 회전하고 있는 프레임 상에서 관찰한 변화를 고정된 프레임 기준으로 어떻게 변환할까?

### III.1. 두 명의 관찰자

프레임 두 개와 관찰자 두 명을 준비하자.

- 고정 프레임 $$\{A\}$$: 정지해 있는 프레임이고, 여기에 관찰자 $$A$$가 서 있다.
- 회전 프레임 $$\{B\}$$: $$\{A\}$$에 대해 각속도 $$\boldsymbol{\omega}$$로 회전하는 프레임이고, 여기에 관찰자 $$B$$가 프레임과 함께 돌면서 서 있다.

프레임 $$\{B\}$$의 기저 벡터를 $$\hat{\mathbf{b}}_1, \hat{\mathbf{b}}_2, \hat{\mathbf{b}}_3$$라고 하자.
그리고 시간에 따라 변하는 임의의 벡터 $$\mathbf{p}(t)$$를 하나 잡고, 이것을 $$\{B\}$$의 기저로 아래와 같이 분해하자.

$$
\mathbf{p}(t) = \sum_{i=1}^{3} p_i(t) \hat{\mathbf{b}}_i(t)
$$

여기서 헷갈리기 쉬운 지점을 하나 짚어두어야 한다.
관찰자 $$A$$가 보기에는 성분 $$p_i$$도 변하고, 기저 $$\hat{\mathbf{b}}_i$$ 역시 프레임과 함께 돌기 때문에 변한다.
반면 관찰자 $$B$$는 자신의 기저와 함께 돌고 있으므로 $$\hat{\mathbf{b}}_i$$가 변한다는 사실을 감지할 수 없고, 오직 성분 $$p_i$$가 변하는 것만 관찰한다.
그러니 두 관찰자가 측정한 $$\mathbf{p}$$의 시간 변화율은 반드시 구분해서 적어야 하며, 이 포스팅에서는 아래와 같이 표기하기로 한다.

$$
\left( \frac{d\mathbf{p}}{dt} \right)_{A}, \quad \left( \frac{d\mathbf{p}}{dt} \right)_{B} = \sum_{i=1}^{3} \frac{dp_i}{dt} \hat{\mathbf{b}}_i
$$

{: .note }
> 오른쪽 식이 곧 "회전하는 프레임 상에서 관찰한 변화"의 수학적 정의다.
> 즉, $$\left( \frac{d\mathbf{p}}{dt} \right)_{B}$$는 기저를 상수로 취급하고 성분만 미분한 것이다.

### III.2. 유도

이제 관찰자 $$A$$의 입장에서 $$\mathbf{p}$$를 그냥 곱의 미분법 (product rule) 으로 미분해보자.

$$
\left( \frac{d\mathbf{p}}{dt} \right)_{A} = \sum_{i=1}^{3} \frac{dp_i}{dt} \hat{\mathbf{b}}_i + \sum_{i=1}^{3} p_i \left( \frac{d\hat{\mathbf{b}}_i}{dt} \right)_{A}
$$

첫 번째 항은 III.1에서 정의한 $$\left( \frac{d\mathbf{p}}{dt} \right)_{B}$$ 그 자체다.
두 번째 항의 $$\hat{\mathbf{b}}_i$$는 회전 프레임에 박혀 있는 벡터이므로, II.2에서 얻은 결과를 그대로 적용해서 아래와 같이 정리할 수 있다.

$$
\begin{align*}
\sum_{i=1}^{3} p_i \left( \frac{d\hat{\mathbf{b}}_i}{dt} \right)_{A} & = \sum_{i=1}^{3} p_i (\boldsymbol{\omega} \times \hat{\mathbf{b}}_i) \quad - \because \left( \frac{d\hat{\mathbf{b}}_i}{dt} \right)_{A} = \boldsymbol{\omega} \times \hat{\mathbf{b}}_i \\
& = \boldsymbol{\omega} \times \sum_{i=1}^{3} p_i \hat{\mathbf{b}}_i \quad - \because \text{외적의 선형성} \\
& = \boldsymbol{\omega} \times \mathbf{p}
\end{align*}
$$

두 항을 합치면 드디어 **수송 정리**를 얻는다.

$$
\left( \frac{d\mathbf{p}}{dt} \right)_{A} = \left( \frac{d\mathbf{p}}{dt} \right)_{B} + \boldsymbol{\omega} \times \mathbf{p}
$$

결론만 보면 정말 간단하다.
회전하는 프레임에서 관찰한 변화율에 $$\boldsymbol{\omega} \times \mathbf{p}$$ 하나만 더해주면 고정된 프레임에서의 변화율이 된다.
필자가 이 식을 두고 고개를 갸우뚱했던 지점들을 마지막으로 정리해둔다.

- **$$\boldsymbol{\omega} \times \mathbf{p}$$ 항의 정체는 무엇인가?** $$\mathbf{p}$$가 $$\{B\}$$ 안에서 전혀 움직이지 않아도, 프레임이 돌기 때문에 생기는 변화량이다. 즉, 벡터 자신의 변화가 아니라 **기저의 변화**가 만들어낸 항이다.
- **$$\mathbf{p}$$는 위치 벡터여야 하는가?** 아니다. 유도 과정에서 $$\mathbf{p}$$가 위치라는 가정은 한 번도 쓰이지 않았다. 속도, 각속도, 힘 등 프레임에 대해 성분으로 적을 수 있는 임의의 벡터에 모두 적용된다.
- **$$\mathbf{p}$$가 $$\{B\}$$에 고정되어 있다면?** $$\left( \frac{d\mathbf{p}}{dt} \right)_{B} = \mathbf{0}$$이 되어 II.2의 $$\dot{\mathbf{p}} = \boldsymbol{\omega} \times \mathbf{p}$$로 되돌아온다. 수송 정리가 II.2의 일반화임을 확인할 수 있다.
- **양변을 어떤 프레임의 성분으로 적어야 하는가?** 이 식은 좌표계와 무관한 벡터 등식이므로 어느 쪽 성분으로 적어도 무방하다. 다만 한 등식 안에서는 반드시 같은 프레임의 성분으로 통일해야 한다.

## IV. 수송 정리 예제: 구체적인 수치 계산

실제 숫자를 대입하여 수송 정리가 어떻게 작동하는지 직관적으로 확인해보자. 상황에 따라 두 가지 예시를 준비했다.

### IV.1. 예제 1: 원점이 고정된 회전 플랫폼 (제자리 자전)

다음과 같은 상황을 가정해본다:
- **고정 프레임 A**: 지상에 고정된 관제탑. 원점은 지면.
- **회전 프레임 B**: 관제탑으로부터 $$x$$축 방향으로 $$10\text{ m}$$ 떨어진 곳($$\mathbf{r}_{origin} = \begin{bmatrix} 10 & 0 & 0 \end{bmatrix}^T$$)에 위치한 안테나 플랫폼. 이 플랫폼은 자신의 원점을 지나는 수직축(A 프레임의 $$z$$축과 평행한 축)을 중심으로 초당 $$2\text{ rad}$$의 속도로 회전 중이다. 즉, 관제탑(A)에서 바라본 각속도 벡터는 $$\boldsymbol{\omega} = \begin{bmatrix} 0 & 0 & 2 \end{bmatrix}^T \text{ rad/s}$$ 이다.
- **관찰 대상**: 하늘을 날고 있는 드론.

어느 순간, 회전하는 플랫폼(B)에 있는 관찰자가 **자신의 원점(안테나)으로부터** 드론의 상대 위치와 속도를 측정했다.
- 안테나 기준 드론의 상대 위치: $$\mathbf{r}_B = \begin{bmatrix} 1 & 2 & 0 \end{bmatrix}^T \text{ m}$$
- 안테나 기준 드론의 상대 속도: $$\mathbf{v}_B = \left( \frac{d\mathbf{r}_B}{dt} \right)_B = \begin{bmatrix} 3 & 0 & 0 \end{bmatrix}^T \text{ m/s}$$

이제 지상 관제탑(A) 입장에서 드론의 실제 속도 $$\mathbf{v}_A$$를 구해보자. 프레임 B의 원점 자체는 이동하지 않고 제자리 회전만 하므로 병진 속도는 없다 ($$\mathbf{v}_{origin} = \mathbf{0}$$). 따라서 A 관찰자가 본 드론의 절대 위치 $$\mathbf{r}_A = \mathbf{r}_{origin} + \mathbf{r}_B$$ 를 미분하면 다음과 같이 수송 정리가 적용된다.

$$
\mathbf{v}_A = \mathbf{v}_{origin} + \mathbf{v}_B + \boldsymbol{\omega} \times \mathbf{r}_B = \mathbf{0} + \mathbf{v}_B + \boldsymbol{\omega} \times \mathbf{r}_B
$$

우선 회전에 의해 생기는 겉보기 속도 항($$\boldsymbol{\omega} \times \mathbf{r}_B$$)을 외적을 통해 계산한다.

$$
\boldsymbol{\omega} \times \mathbf{r}_B =
\begin{bmatrix} 0 \\ 0 \\ 2 \end{bmatrix} \times \begin{bmatrix} 1 \\ 2 \\ 0 \end{bmatrix} =
\begin{bmatrix} -4 \\ 2 \\ 0 \end{bmatrix} \text{ m/s}
$$

이제 측정한 상대 속도와 회전 효과를 더해준다.

$$
\mathbf{v}_A = \begin{bmatrix} 3 \\ 0 \\ 0 \end{bmatrix} + \begin{bmatrix} -4 \\ 2 \\ 0 \end{bmatrix} = \begin{bmatrix} -1 \\ 2 \\ 0 \end{bmatrix} \text{ m/s}
$$

### IV.2. 예제 2: 공전과 자전이 복합된 상황 (태양-지구-달)

이번에는 앞서 방금 말했던 것처럼 회전하는 프레임의 원점이 크게 궤도를 도는(공전하는) 경우를 생각해보자.

- **고정 프레임 A (태양)**: 우주 공간에 정지해 있는 태양 중심 좌표계.
- **회전 프레임 B (지구)**: 태양으로부터 $$x$$축 방향으로 $$100\text{ m}$$ 떨어진 지구 중심 좌표계 ($$\mathbf{r}_{origin} = \begin{bmatrix} 100 & 0 & 0 \end{bmatrix}^T$$). 
  지구는 태양을 중심으로 초당 $$1\text{ rad}$$의 각속도로 원운동(공전) 중이다 ($$\boldsymbol{\Omega}_{orbit} = \begin{bmatrix} 0 & 0 & 1 \end{bmatrix}^T \text{ rad/s}$$).
  또한, 지구 자체도 초당 $$3\text{ rad}$$의 각속도로 팽이처럼 자전 중이다 ($$\boldsymbol{\omega}_{spin} = \begin{bmatrix} 0 & 0 & 3 \end{bmatrix}^T \text{ rad/s}$$).
  따라서 태양(A) 관찰자가 본 지구(B 프레임) 기저 벡터들의 총 회전 각속도는 $$\boldsymbol{\omega} = \boldsymbol{\Omega}_{orbit} + \boldsymbol{\omega}_{spin} = \begin{bmatrix} 0 & 0 & 4 \end{bmatrix}^T \text{ rad/s}$$ 이다.
- **관찰 대상 (달)**: 하늘을 날고 있는 달(혹은 우주선).

어느 순간, 지구(B)에 있는 관찰자가 측정한 달의 상대 위치와 속도는 다음과 같다.
- 지구 기준 달의 상대 위치: $$\mathbf{r}_B = \begin{bmatrix} 10 & 0 & 0 \end{bmatrix}^T \text{ m}$$
- 지구 기준 달의 상대 속도: $$\mathbf{v}_B = \begin{bmatrix} 0 & 5 & 0 \end{bmatrix}^T \text{ m/s}$$

이제 태양(A)에서 바라본 달의 실제 속도 $$\mathbf{v}_A$$를 구해보자. 앞선 예제와 달리 이번에는 프레임 B의 원점(지구) 자체가 공전하고 있으므로 병진 속도 $$\mathbf{v}_{origin}$$이 0이 아니다.

**1. 병진 속도 ($$\mathbf{v}_{origin}$$) 계산**
지구가 태양 주위를 도는 원운동 속도이다.
$$
\mathbf{v}_{origin} = \boldsymbol{\Omega}_{orbit} \times \mathbf{r}_{origin} = \begin{bmatrix} 0 \\ 0 \\ 1 \end{bmatrix} \times \begin{bmatrix} 100 \\ 0 \\ 0 \end{bmatrix} = \begin{bmatrix} 0 \\ 100 \\ 0 \end{bmatrix} \text{ m/s}
$$

**2. 수송 정리 효과 ($$\boldsymbol{\omega} \times \mathbf{r}_B$$) 계산**
프레임 B의 총 회전(공전+자전)으로 인해 발생하는 속도이다. 여기서 각속도는 위에서 구한 총 각속도($$4\text{ rad/s}$$)를 사용한다.
$$
\boldsymbol{\omega} \times \mathbf{r}_B = \begin{bmatrix} 0 \\ 0 \\ 4 \end{bmatrix} \times \begin{bmatrix} 10 \\ 0 \\ 0 \end{bmatrix} = \begin{bmatrix} 0 \\ 40 \\ 0 \end{bmatrix} \text{ m/s}
$$

**3. 속도 합성**
병진 속도, 상대 속도, 수송 정리 효과를 모두 더한다.
$$
\mathbf{v}_A = \mathbf{v}_{origin} + \mathbf{v}_B + \boldsymbol{\omega} \times \mathbf{r}_B = \begin{bmatrix} 0 \\ 100 \\ 0 \end{bmatrix} + \begin{bmatrix} 0 \\ 5 \\ 0 \end{bmatrix} + \begin{bmatrix} 0 \\ 40 \\ 0 \end{bmatrix} = \begin{bmatrix} 0 \\ 145 \\ 0 \end{bmatrix} \text{ m/s}
$$

{: .note }
> **각속도 벡터의 덧셈이 지니는 강력함**
> 
> 위 예제에서 가장 아름다운 부분은 복잡한 회전(공전+자전)을 처리하는 방식이다. **어떤 프레임에 여러 개의 회전이 중첩되어 있더라도, 그 프레임에 작용하는 모든 각속도 벡터들을 단순히 '벡터의 덧셈($$\boldsymbol{\omega}_{total} = \boldsymbol{\omega}_1 + \boldsymbol{\omega}_2 + \dots$$)'으로 합쳐버리기만 하면 된다.** 
> 이렇게 구한 총 각속도 벡터 하나만 수송 정리의 $$\boldsymbol{\omega}$$ 자리에 대입하면, 모든 겉보기 회전 효과가 단번에 정확하게 계산된다. 앞서 `II.1`에서 "미소 회전(각속도)은 벡터로서 더할 수 있다"고 짚고 넘어간 이유가 바로 이것이다!

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
