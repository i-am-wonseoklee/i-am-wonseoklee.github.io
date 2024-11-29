---
title: Graham's Scan
layout: default
parent: Robotics
permalink: /docs/robotics/00-grahams-scan
---

# Graham's Scan

**Keywords:** `Graham's Scan`{: .label }, `Convex Hull`{: .label }

`Graham's scan`은 2D 평면상에 주어진 N개의 점들을 모두 포함하는 convex polygon을 찾는 알고리즘이다.
주어진 모든 점을 포함하는 convex polygon은 `convex hull`이라고 불린다.

{: .note }
> `convex polygon`
>
> 다각형 $$P$$에서 서로 다른 임의의 두 꼭지점을 골라 이를 잇는 선분 $$L$$을 만든다고 하자.
> 선분 $$L$$ 위의 모든 점이 $$P$$의 내부(경계 포함)에 있는 경우 $$P$$는 convex polygon이다.
> 예를 들어, 아래 그림의 좌측 polygon은 convex polygon이고 우측 polygon은 convex polygon이 아니다.
> 우측 polygon에서 적색 점선 위에 있는 점들은 polygon 내부에 위치하고 있지 **않음**을 알 수 있다.
>
> ![](/docs/robotics/00-grahams-scan/convex.png)

## I. Intuition of Graham's Scan

이 문제를 아주 직관적으로 푸는 알고리즘은 [Gift wrapping algorithm](https://en.wikipedia.org/wiki/Gift_wrapping_algorithm)이다.
`Graham's scan`은 `Gift wrapping algorithm`에 정렬과 스택을 추가적으로 도입함으로써 복잡도를 개선하였다.
따라서, `Graham's scan`의 이해에 직관을 부여해 줄 수 있는 `Gift wrapping algorithm`의 동작과정을 우선 살펴보도록하자.

머릿속에 아래 그림과 같이 널빤지에 촘촘히 박혀있는 못들을 생각해보자.
그리고, "널빤지가 곧 2D 평면이요, 못들이 곧 점이니"라고 자기 암시를 해보도록 하자.
이제 우리에게 주어진 미션은 못들을 모두 포함하는 convex hull을 찾는 것이다.

![](/docs/robotics/00-grahams-scan/gwa-01.png)

아마 가장 직관적인 접근은 아래와 같을 것이다.
그리고 이것이 곧 `Gift wrapping algorithm`의 접근 방법이기도 하다.

- 무조건 convex hull에 포함될 수 밖에 없는 못 하나를 고른다.
  가장 좌측 하단에 있는 못 정도를 고르면 무리가 없을 것이다(이 못을 안 고르면 이 못을 포함시킬 방법이 없으므로).
- 위에서 고른 못에 실을 묶는다.
- 반시계 방향으로 당기면서 가장 먼저 만나는 못에 또 실을 감는다.
- 맨 처음 고른 못을 만날 때까지 위의 과정을 반복한다.

아래 그림은 위에서 설명한 과정을 그림으로 나타낸 것이다.

![](/docs/robotics/00-grahams-scan/gwa-02.png)

{: .note }
> "`가장 먼저 만나는 못`"이라는 표현이 조금은 혼란스러울 수 있을 것 같다.
> 이 표현은 다음과 같이 조금 더 formal하게 표현해줄 수 있다.
> - 실이 감겨 있는 마지막 못을 $$P_{last}$$라고 하자.
> - 실이 감겨 있지 않은 못을 $$\{P_{0}, P_{1}, ...\}$$라고 하자.
> - $$P_{last} \rightarrow P_{n} \ (n \geq 0)$$이 x축(i.e. 수평축)과 이루는 각도가 최소가 되는 못을 찾는다.
>   이 때, 각도는 시계 방향에는 음수를, 반시계 방향에는 양수를 부여한다.

`Gift wrapping algorithm`을 살펴보는 것을 통해 `Graham's scan`을 이해하기 위한 inituition은 부여가 된 것 같다.
결국에는 "greedy하게(?) 최대한 밖에 있는 점부터 감싼다"가 핵심이다.

## II. Graham's Scan

이제, `Gift wrapping algorithm`의 수행시간을 정렬과 스택을 도입하여 해결한 `Graham's scan`을 살펴보자.
예제를 가지고 한 스텝, 한 스텝 진행해보면 I절에서 이야기한 inituition을 그대로 옮긴 것을 알 수 있다.

- 우선, 무조건 convex hull에 포함될 점 하나를 고른다.
  적당히 최외곽(좌/우 상/하단)에 있는 점을 고르면 된다.
  아래 예시에서는 최좌상단에 있는 점을 골랐다.

  ![](/docs/robotics/00-grahams-scan/gs-01.png)

- 고른 점을 기준으로 나머지 점들을 반시계 방향으로 이루는 각이 작은 순서대로 정렬한다.
  조금 더 formal하게 표현하면, 고른 점을 $$P$$, 나머지 점들을 $$P_{i}$$라고 할 때, "$$P \rightarrow P_{i}$$가 x축과 이루는 각이 작은 순서대로 정렬한다." 정도가 될 수 있다.
  정렬하면, 아래 예시와 같이 점들에 순서가 부여될 것이다(이해를 돕기위해 점선으로 각들을 표현해두었다).
  
  ![](/docs/robotics/00-grahams-scan/gs-02.png)

- 정렬된 점들에서, 첫 2개의 점을 차례로 스택에 push해준다.

  ![](/docs/robotics/00-grahams-scan/gs-03.png)

- 이제, 나머지 정렬된 점들을(i.e. 2번 부터) 차례로 순회하면서 아래를 진행한다.
  기술의 편의를 위해 $$S_{curr}$$는 스택의 top을, $$S_{prev}$$는 스택의 top 바로 아래 원소를 가르킨다고 하자.
  - 이번에 보고 있는 점을 $$P_{i}$$라고 하자.
  - 만약, 스택의 원소 수가 2개 미만이라면, $$P_{i}$$는 무조건 스택에 push하고 $$P_{i+1}$$을 검사하러 간다.
  - 스택의 원소 수가 2개 이상이라면, $$S_{prev} \rightarrow S_{curr}$$이 나타내는 line 기준으로 $$P_{i}$$가 어느 방향(반시계 혹은 시계)에 있는지를 검사한다.
    - 만약 반시계 방향에 있다면, $$P_{i}$$를 스택에 push하고, $$P_{i+1}$$을 검사하러 간다.
    - 만약 시계 방향에 있다면, 스택에서 $$S_{curr}$$을 pop하고, 다시 $$P_{i}$$를 검사한다.
  - 더 이상 검사할 점 $$P_{i}$$가 남아있지 않을 때까지 반복한다.
- 마지막에, 스택에 남아 있는 정점들이 convex hull polygon의 꼭지점들이 된다.

바로 위에서 언급한 부분을 그림으로 나타내면 아래와 같다.
- (A), (B), (D), (E)에서는 보고 있는 정점이 반시계 방향에 있어서 스택에 push되었고,
- (C)에서는 시계 방향에 있어 스택에서 직전 점이 pop되었다.
- 더 이상 검사할 정점이 없는 (F)상태가 되면, 스택에 남아있는 점들이 convex hull polygon의 꼭지점이 되는 것을 알 수 있다.

![](/docs/robotics/00-grahams-scan/gs-04.png)

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>