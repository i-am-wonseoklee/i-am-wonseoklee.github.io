---
title: "Limitations and Critique"
layout: default
nav_order: 7
parent: "Plan T"
grand_parent: "Reproducing Papers"
permalink: /docs/reproducing-papers/00-plan-t/06-limitations-and-critique
---

# Limitations and Critique

## TOC
{: .no_toc }

1. TOC
{:toc}

**Keywords:** `PlanT`{: .label }, `critique`{: .label }, `limitations`{: .label }

이 챕터에서는 `PlanT` 논문을 공부하면서 느낀 아쉬운 점들을 정리한다.
목표는 이 논문의 결함을 찾는 게 아니라, **다음에 모션 플래닝 논문을 공부할 때 뭘 고려해야 할지**를 생각해보는 것이다.

## I. Static Obstacle Representation

`PlanT`는 모든 객체를 **6개 속성 벡터**로 표현한다.

$$o_i = \{z_i, x_i, y_i, \phi_i, w_i, h_i\}$$

동적 차량(속도 있음)에는 잘 작동한다. 근데 도로 레이아웃, 건물, 중앙선 같은 정적 요소까지 모두 이 6-tuple bbox 형태로 표현하려니까 좀 억지 같다.
특히 확장된 구조물들은 단일 bounding box로 표현하기 어렵다.

## II. Route Input: 차선 레벨 플래닝이 먼저 필요하다

`PlanT`가 받는 입력 중 가장 까다로운 게 **route**다.

Route를 얻으려면 ego가 **"현재 어느 차선을 따라 어디로 가야 하는가"**를 미리 알아야 한다.
논문에서는 데이터셋의 ground-truth route를 사용하지만, 실제 차에 넣으려면:

1. **HD Map** 필요
2. **Global Route Planner** 필요  
3. **Lane-level Behavior Planner** 필요

즉, `PlanT`는 **"이미 내가 따라갈 차선이 정해져 있을 때, 속도와 미세한 횡방향 움직임만 조절"**하는 거다.

그 결과, `PlanT`는 차선 변경, 경로 우회, 계획 밖의 응급 기동이 불가능하다.
이게 바로 내가 다음 논문을 고를 때 봐야 할 점이다: **전제 조건이 뭐고, 그게 현실적으로 보장될 수 있나?**

## III. Motion Planning vs. Policy

내 입장에서 보면 `PlanT`는 플래닝과 정책 사이 뭔가 애매한 곳에 있다.
모션 플래닝 엔지니어 관점에서는 그냥 신박한 느낌의 속도 플래너에 가깝다.
더 고급진 건 아니지만, 신경망으로 속도를 부드럽게 뽑아낸다는 게 신박할 뿐이다.
이것도 다음 논문을 고를 때 봐야 할 점이다: **이 모델이 정말 뭘 하는 건지 정확히 파악했나?**

## IV. 느낀점

결국 이 논문이 정말 완벽한 모션 플래너는 아니라는 거고, 실제 자율주행 시스템에 그대로 쓰기엔 많은 제약이 있다.
하지만 그래도 첫 연습 삼아 신경망 기반 플래닝을 한 번 해보고, 트랜스포머와 GRU의 실제 작동을 경험해본 것만으로도 충분히 가치 있었다.


<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
