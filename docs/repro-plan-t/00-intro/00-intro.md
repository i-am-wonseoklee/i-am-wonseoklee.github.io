---
title: Introduction
layout: default
nav_order: 1
parent: "reproducing: Plan T"
permalink: /docs/repro-plan-t/00-intro
---

# Introduction

**Keywords:** `Plan T`{: .label }

나는 모션플래닝 엔지니어라고 불리는 일을 하고 있다.
주로 바퀴달린 로봇들을 가지고 샘플링, 최적화 같은 고전적인 방법들로 문제를 풀어왔다.
그런데 요즘은 트렌드를 보면 복잡한 매니퓰레이터든, 휴머노이드 로봇이든 딥러닝 없이는 답도 안 나온다는 식이다.

상황이 이렇다보니 딥러닝도 모르면서 옛날 방식이나 붙들고 있는 내 자신이 한심하기 짝이 없곤 했다.
어제랑 비슷한 오늘을 산다면 사실 도태된 게 아니라 이미 뒤처진 거고, 앞으로도 계속 뒤처질 거다.
딥러닝이 나타나면서 갑자기 [모두가 같은 시작점](https://blogs.nvidia.co.kr/blog/nvidia-ceo-carnegie-mellon-commencement-address/)에 서게 됐는데, 그동안 내가 이렇게 해온 게 뭐 대수라고 새로운 걸 안 배우고 있단 말인가.

더 이상 한심한 꼴을 당하고만 있을 수는 없으니까, 그럴듯한 논문 하나를 골라서 제대로 공부해보고 구현해보기로 했다.
여기에는 얼마 전 Andrej Karpathy가 말한 전문가되는 방법을 한번 따라가보고 싶은 마음도 함께 작용했다.
Karpathy가 말하는 배움의 방식이 조금은 근본 없다는 생각이 들어서 항상 애써 숨겨온 적도 많은 것 같다.
그런데, 정말로 깊게 반추해보면 정말 저 방식이 늘 내겐 가장 효과적이 방법이었다.

![karpathy](/docs/repro-plan-t/00-intro/assets/karpathy.png)

하여간 각설하면, 필자는 흔히 `Plan T`라고 불리는 다음 논문을 골랐다.

> Renz, Katrin, et al. "Plant: Explainable planning transformers via object-level representations." arXiv preprint arXiv:2210.14222 (2022).

이 논문을 고른 이유는 다음과 같다:
**(1)** `Plan T`는 조사 결과 transformer를 자율주행 모션플래닝에 적용한 첫 번째 사례다.
어차피 2026년 SOTA급 연구들은 transformer를 전제로 하는 것 같다.
괜히 transformer 적용 전 논문들부터 훑어가며 시간을 낭비하기는 싫었고, 가뜩이나 딥러닝을 잘 모르는데 덜컥 SOTA부터 하기는 겁이 났다.
그래서 transformer를 처음 모션플래닝에 적용한 논문을 선택하게 되었다.
**(2)** 오픈 소스 코드가 공개되어 있다.
논문만 읽고 끝내는 게 아니라 실제로 구현을 수정하고 실험해볼 수 있다는 뜻이다. 물론 이해할 수 있을지는 별개의 문제지만.
**(3)** 막스 플랑크 연구소에서 나온 논문이다. 충분히 신뢰할 만하다.

아직 오늘은 아무내용도 작성하지 않았지만...시작이 반이다.
이제부터 `Plan T`를 찬찬히 뜯어보도록 하자.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
