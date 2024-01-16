---
title: Chapter 01
layout: default
parent: Professional C++
grand_parent: TechTome Summaries
permalink: /docs/tech-tome-summaries/professional-cpp/00-chapter-01
---

# Chapter 01

**Textbook:** pp.58 - 170

한글 번역서를 기준으로 챕터 1의 제목은 "C++와 표준 라이브러리 초단기 속성 코스"이다.
어이 없게 긴 제목이지만, C++11 이후부터 C++20 에 이르는 C++ 및 표준 라이브러리에 대한 내용을 한 번 쭉 개괄해주기 때문에 꽤 유용한 챕터이다.
다만, 이 챕터에 나온 모든 내용을 하나하나 다 정리하는 것은 그야말로 데이터 낭비이므로, 이곳에는 챕터의 내용중 필자가 모르고 있었거나, 잊고 있었던 것들만을 정리한다.
이는 곧 이 포스팅의 내용은 다분히 필자의, 필자에 의한, 필자를 위한 정리라는 것이다.
이 정리가 맘에 들지 않는다면...책을 사서 읽으시길 권한다.

## How to compile C++20 source code

이 내용은 딱히 책에 친절히 설명되어 있지 않았지만, 책에 나오는 실습을 진행하는 과정에서 필요로 되므로 간략하게 정리해둔다.
필자의 환경은 `Ubuntu 22.04 LTS` 이고, 공교롭게도 얼마전 포맷을 해서 mint 상태이다.

```cpp
// This is an example source file using c++20.
import <iostream>;

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
```

필자는 위의 헬로월드 소스파일을 `hello_world.cc` 라는 이름으로 작성하였고, 아래의 bash command들을 통해서 이 소스파일의 executable을 만들 수 있었다.

```bash
# When using g++ you need to create map file for each system header as below:
g++ -std=c++20 -fmodules-ts -xc++-system-header iostream
# After creating map file(s), compile the source code as below:
g++ -std=c++20 -fmodules-ts -o hello_world hello_world.cc
```

system header의 map file (지금은 이게 뭔지도 모르겠다...) 을 만들어주기 위한 스텝이 하나 추가된 것과, `g++`에 처음보는 `-fmodules-ts` 옵션이 붙는 것이 당황스럽지만, 일단 컴파일되고 잘 실행되니 책에서 설명해주기 전까지는 당분간 위의 방법을 사용하도록하자.

## Nested namespace

사실 이 기능은 C++17 부터 있었다고 하는데, 필자는 모르고 있었다.
심지어 이 문법은 굉장히 많이 쓰고 있었는데 ~~(동시에 짜증내고 있던)~~ 말이다.

```cpp
namespace outer {
namespace inner {
// Your code.
}
}
```

와 같이 층층이 길게 써주어야 하던 것을

```cpp
namespace outer::inner {
// Your code.
}
```

와 같이 축약해서 써줄 수 있다.

## Three-way comparison operator

`Three-way comparison operator`는 C++20부터 도입된 기능이다.
사실 연산자 모양이 `<=>` 이렇게 생겨서 `spaceship operator`라고도 부른단다.
두 피연산자를 취해서 (1)`보다 작다`, (2)`보다 크다`, (3)`같다` 세 가지 중 하나를 리턴한다.
말보다는 코드로 보는 것이 쉬우므로 코드를 통해 살펴보자.

```cpp
import <compare>;

using namespace std;

int main() {
  int one{1};
  int two{2};
  strong_ordering result{one <=> two};
  if (result == strong_ordering::less) {
    cout << "less" << endl;
  } else if (result == strong_ordering::greater) {
    cout << "greater" << endl;
  } else if (result == strong_ordering::equal) {
    cout << "equal" << endl;
  }
  return 0;
}
```

## Attributes

필자는 아래에 적을 attribute 들 중 `[[maybe_unused]]` 이외에는 사용해본 기억이 없다.
그만큼 쓸 데 없는 기능인가 하는 생각이 들긴하지만, 몇개는 신박했으므로 아래에 쭉 코드 형식으로 정리한다.

```cpp
// 이 function의 return을 버리면 안된다.
[[nodiscard]] bool IsZero(int number);
// C++20 부터는 nodiscard에 이유를 설명하는 스트링을 붙일 수 있다고 한다.
[[nodiscard("To prevent human error")]] bool IsZero(int number);

// 파라미터 `int a`는 경우에 따라 사용되지 않을 수도 있다.
int DivideAbyB([[maybe_unused]] int a, int b);

// 이 함수는 return하지 (caller로 돌아오지) 않는다.
[[noreturn]] void CleanupAndDie() { std::exit(1); }

// 이 함수는 deprecated되었다.
[[deprecated]] void OldAdder(int a, int b);
// 그리고, 여기에는 deprecate된 함수가 사용될 때 출력할 (컴파일) 경고 스트링을 붙일 수도 있다.
[[deprecated("Please use NewAdder")]] void OldAdder(int a, int b);

// branch prediction을 향상시켜준다고 한다.
switch (number_of_fingers) {
  [[likely]] case 5: // 많이 taken될만한 곳.
    break;
  [[unlikely]] case 99: // 거의 taken될 일이 없는 곳.
    break;
}
```

## Return value optimization

{: .note }
> - RVO가 적용되는 경우들
>   - return object가 매개변수이다.
>   - return object가 임싯값이다.
> - NRVO가 적용되는 경우들
>   - return object가 local variable이다.

## Terminologies

이 섹션에서 기술할 내용들은 책에 따로 언급이 되어 있는 것들은 아니다.
대부분 특정 문법 요소의 이름을 정리하는 것인데, 필자는 처음들어본 것도 있고 아예 다른 이름으로 잘못 부르고 있던 것들이 있었다.
코드 리뷰 따위를 할 때 의외로 이런 용어를 사용해야 하는 경우가 더러 있으므로 이참에 정리를 해놓고자 한다.

```cpp
// curly brace를 사용하는 초기화를 uniform initializer를 사용한 초기화라고 부른다.
int number{0};

// 아래와 같이 template 인자를 주지 않아도 되는 것은 CTAD (Class Template Argument Deduction) 덕이다.
std::array {1, 2, 3};

// 아래와 같이 struct, array, pair 등에 담긴 값을 한 번에 뽑아오는 것을 structured binding이라고 부른다.
std::array<int> arr{1, 2, 3};
int [a, b, c] {arr};

// 클래스의 멤버변수를 초기화 하는 방법에 따라 이름이 다르다.
class Example {
  Example(int b) : b_{b} // constructor initializer라고 부른다.
  {}
private:
  int a_{1}; // in-class initializer라고 부른다.
  int b_;
};

// public 데이터 멤버만 있고, custom c'tor가 없는 간단한 구조체, 클래스는 aggregate type이라고 부른다.
struct ExampleAggType {
  int a;
  int b;
};

// C++20부터는 aggregate type에 대해서 아래와 같은 특이한 초기화 (designated initializer) 가 사용 가능하다.
ExampleAggType ex {
  .a = 1,
  .b = 2
};
```

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>