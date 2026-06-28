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

이 포스팅은 구현 난이도나 재현 과정의 고생담이 아니라, 논문 자체의 주장과 실험 설계가 어디까지 유효한지를 비판적으로 점검하는 글이다.
목적은 결과를 깎아내리는 것이 아니라, 결론의 적용 범위를 더 정확히 해석하는 데 있다.

## I. What This Critique Targets

`PlanT`는 object-level representation을 사용해 planning을 수행하고, 해석 가능성과 성능을 함께 강조한다.
문제는 이런 장점들이 어떤 가정 위에서 성립하는지, 그리고 그 가정이 깨질 때도 동일한 결론이 유지되는지가 논문에서 충분히 분리되어 검증되었는가이다.

아래의 비판 포인트는 크게 네 가지 축으로 나뉜다.

- 표현 방식(object-level tokenization)의 구조적 한계
- perception upstream 의존성
- explainability 주장에 대한 검증 강도
- evaluation protocol의 일반화 가능성

## II. Representation: What Is Gained, What Is Lost

object-level 토큰화는 계산 효율과 구조적 단순성이라는 분명한 이점을 준다.
하지만 동일한 선택은 표현 손실(lossy abstraction)도 동반한다.

연속적인 장면의 디테일, 예를 들어 차선 경계의 미세한 형상이나 지도 오차의 지역적 패턴은 bounding box 기반 객체 표현에서 직접적으로 보존되기 어렵다.
이는 인식 단계가 완벽하지 않을 때 더 크게 드러난다.
입력이 이미 추상화된 상태이기 때문에, planner가 잃어버린 정보를 복구할 여지가 거의 없다.

즉, object-level representation은 "좋은 추상화"가 될 수도 있지만, 동시에 "복구 불가능한 정보 삭제"가 될 수도 있다.
논문은 전자의 장점을 잘 보여주지만, 후자의 비용을 정량적으로 분해해 보여주지는 못한다.

## III. Planner Performance vs Perception Quality

`PlanT`의 성능은 planner 구조만으로 결정되지 않는다.
실제로는 detection, tracking, map alignment 같은 upstream 품질에 강하게 종속된다.

이때 생기는 핵심 해석 문제는 다음과 같다.

- 성능 개선이 planner 자체의 기여인지
- 아니면 cleaner한 객체 입력 덕분인지

논문에서 보고된 결과만으로는 두 효과를 명확히 분리하기 어렵다.
같은 planner라도 perception 노이즈 모델이 바뀌면 결과가 크게 달라질 수 있는데, 이 민감도 분석이 충분히 깊게 다뤄지지 않았다.

## IV. Explainability Claim: Interpretation vs Causality

논문은 explainable planning이라는 메시지를 전면에 둔다.
하지만 attention map이나 토큰 중요도 시각화는 해석 단서를 제공할 뿐, 인과적 설명(causal explanation)을 자동으로 보장하지는 않는다.

예를 들어 "이 토큰을 많이 봤다"는 사실과 "그래서 이 waypoint가 생성되었다"는 결론 사이에는 간극이 있다.
후자를 주장하려면 intervention 기반 검증(특정 토큰 제거/교란 시 출력 변화)이나 counterfactual 실험이 더 체계적으로 필요하다.

요약하면, `PlanT`의 explainability는 "읽기 쉬운 표현"에는 가깝지만, "인과적으로 검증된 설명"까지는 아직 거리가 있다.

## V. Evaluation Protocol and Generalization Limits

시뮬레이터 기반 평가는 빠르고 반복 가능하다는 장점이 있다.
반대로 말하면, 특정 시뮬레이터의 분포 편향에 결론이 묶일 위험도 크다.

특히 다음 질문들이 남는다.

- 도시 구조가 달라져도 동일한 경향이 유지되는가?
- 교통 밀도와 상호작용 복잡도가 올라가도 안정적인가?
- 희귀 사건(급정지 cut-in, 시야 가림, 엣지 케이스)에서 강건한가?

오프라인 지표(ADE/FDE)가 좋더라도 closed-loop 안정성으로 직결된다고 단정하기 어렵다.
즉, 평균 오차 지표는 필요조건일 수 있지만 충분조건은 아니다.

## VI. Safety and Long-Tail Scenarios

자율주행에서 중요한 것은 평균 성능이 아니라 tail risk다.
평균적으로 잘 달리는 모델과, 위험한 상황에서 안전한 모델은 다를 수 있다.

`PlanT`는 planning 성능을 설득력 있게 보여주지만, safety case 관점에서 다음 항목은 상대적으로 덜 다뤄진다.

- worst-case 성능 하한
- uncertainty calibration과 보수적 의사결정
- 위험 상황에서의 fail-safe 동작

결국 실제 배치 관점에서는 "평균적으로 좋다"보다 "망가질 때 어떻게 망가지는가"가 더 중요하다.
이 지점이 후속 연구로 가장 필요한 부분이다.

## VII. What Would Strengthen the Paper

논문의 가치를 깎지 않으면서도, 결론의 설득력을 크게 높일 수 있는 실험은 비교적 명확하다.

- perception 노이즈 강도별 성능 민감도 분석
- attention 설명과 intervention 결과의 상관 분석
- 다중 seed/다중 town에서 분산 포함 리포팅
- offline 지표와 closed-loop 안전 지표의 상관관계 제시
- long-tail 시나리오 전용 벤치마크 추가

이런 보강이 들어가면 `PlanT`는 "흥미로운 방법"에서 한 걸음 더 나아가 "신뢰 가능한 방법"으로 해석되기 쉬워진다.

## VIII. Closing Note

요약하면, `PlanT`는 object-level planning의 가능성을 잘 보여준 의미 있는 작업이다.
다만 논문이 제시한 강점 중 일부는 특정 가정 위에서만 강하게 성립하며, explainability와 safety에 관한 핵심 질문은 아직 열려 있다.

그래서 이 논문의 가장 큰 기여는 완결된 답이라기보다, 앞으로 무엇을 더 검증해야 하는지 명확한 연구 의제를 던졌다는 점에 있다.
