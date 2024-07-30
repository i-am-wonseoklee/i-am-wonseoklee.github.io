---
title: CUDA Setup
layout: default
parent: Topic dive
permalink: /docs/topic-dive/05-cuda-env
---

# CUDA Setup

**Keywords:** `CUDA`{: .label }, `개발환경`{: .label }

CUDA를 사용하여 GPGPU를 프로그램을 작성하기 위해서는 아래 4가지가 준비되어야 한다.

1. CUDA를 지원하는 GPU
2. 1.을 위한 NVIDIA 드라이버
3. CUDA 개발 툴킷
4. 표준 C 컴파일러

## I. CUDA를 지원하는 GPU

우선, [이 링크](https://developer.nvidia.com/cuda-gpus)에 들어가면 지원하는 GPU 목록을 확인할 수 있다.

{: .note }
> **팁!**
> - 이 목록에 명시적으로 적혀있지 않은 GPU더라도 CUDA가 지원되는 경우가 있다. 예를들어, 필자가 사용 중인 랩탑의 MX150의 경우, 목록에는 없지만 CUDA 11.2까지를 무리없이 지원한다.

## II. NVIDIA 드라이버

설치를 원하는 CUDA 버전을 선택한 후에 해당 CUDA 버전에 필요한 NVIDIA 드라이버 버전을 확인하여 설치한다.
CUDA 버전별로 필요한 NVIDIA 드라이버 버전은 [여기](https://docs.nvidia.com/cuda/cuda-toolkit-release-notes/index.html)에서 확인할 수 있다.

{: .note }
> **팁!**
> - ubuntu에서의 NVIDIA 드라이버 설치는 login stuck을 만들어내기로 악명이 높다. 여러 방법들을 시도해보았더니 [이 링크](https://pstudio411.tistory.com/entry/Ubuntu-2004-Nvidia%EB%93%9C%EB%9D%BC%EC%9D%B4%EB%B2%84-%EC%84%A4%EC%B9%98%ED%95%98%EA%B8%B0)가 소개하는 방법 중 `sudo ubuntu-drivers autoinstall`을 사용하는 편이 가장 안정적인 것 같다.

## III. CUDA 개발 툴킷

[이 링크](https://developer.nvidia.com/cuda-downloads)에서 안내하는 방법대로 CUDA 툴킷을 설치하면 된다.

{: .note }
> **팁!**
> - ubuntu를 사용하는 경우, CUDA 툴킷 설치 후에 환경변수 관련한 설정을 해주어야만 한다. bashrc 파일을 열어 다음 세 줄을 추가하자. 중간의 버전은 각자의 CUDA 버전에 알맞게 수정하면 된다. `export PATH=${PATH}:/usr/local/cuda-11.2/bin`, `export CUDADIR=/usr/local/cuda-11.2`, `export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/cuda-11.2/lib64`.

## IV. 표준 C 컴파일러

ubuntu를 사용한다면 대부분 기본적으로 설치가 되어있기 때문에 별도로 설치를 진행할 필요는 없다. 그래도 정 불안하다면 `sudo apt install build-essential`을 통해 일괄적으로 설치하는 것을 추천한다.

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
