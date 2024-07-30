---
title: SOLID
layout: default
parent: Topic dive
permalink: /docs/topic-dive/08-solid
---

# SOLID

**Keywords:** `SOLID`{: .label }, `Single Responsibility Principle`{: .label }, `Open/Close Princicple`{: .label}, `Liskov Substitution Principle`{: .label}, `Interface Segregation Principle`{: .label }, `Dependency Inversion Principle`{: .label }

## I. What is SOLID?

흔히들 Design Pattern을 처음 공부하면, `SOLID principles`이라는 단어를 접하게 된다.
이게 뭔지를 간단하게 설명하면, software를 개발할 때 지키면 좋은 5개의 principle을 앞 글자만 따서 한 단어로 만들어 놓은 것인데, 각 principle은 아래와 같다.

- `S`: Single Responsibility Principle
- `O`: Open/Close Princicple
- `L`: Liskov Substitution Principle
- `I`: Interface Segregation Principle
- `D`: Dependency Inversion Principle

Robert Martin이라는 사람이 `Agile Software Development, Principles, Patterns, and Practices`라는 저서에서 처음 도입한 개념인데, 모든 원칙을 다 지켜야 한다는 강박으로 받아들이기보다는 좋은 software란 무엇인가를 평가하는 척도 정도로만 생각하면 족하다.
실제로 모든 원칙을 다 지키려는 노력은 대부분의 경우 실제로 필요한 것보다 software를 더 복잡하게 만들게 된다.
이제 각 원칙에 대해 한 개씩 설명해보도록 하겠다.

## II. Single Responsibility Principle

한 줄 요약하면, `하나의 class를 수정할 이유는 단 하나뿐이어야 한다.`로 요약할 수 있다.
구체적인 설명을 위하여 아래 예제의 `Employee` class를 잘 살펴보자.
아래 `Employee` class는 2가지 역할을 하고 있는 것으로 볼 수 있는데, 하나는 `salary_`, `schedule_`과 같은 **(1)**정보를 관리하는 것, 다른 하나는 관리하고 있는 **(2)**정보들을 출력하는 것이다.
따라서, (1)관리하는 정보가 추가/삭제/변경될 때 또는 (2)출력해야하는 정보의 포맷(행정 서식으로 이해하자)이 바뀔 때 2가지 이유에 의해 `Employee` class가 수정될 여지가 있다.

```c++
class Employee
{
private:
  Salary salary_;
  Schedule schedule_;
public:
  void printSalary() const;
  void printSchedule() const;
};
```

반면, 아래와 같이 출력해야할 각 정보에 따라서 출력 기능을 별도의 class로 분리해 준다면, 보다 single responsibility에 부합하는 설계가 된다.
아래의 구현에서는 직원에 대해 관리할 정보가 추가/삭제/변경될 때는 `Employee` class를, 출력할 서식이 바뀔 때는 해당하는 `*Printer` class를 수정해주면 된다.

```c++
class Employee
{
private:
  Salary salary_;
  Schedule schedule_;
};

class SalaryPrinter
{
public:
  static void Print(const Salary& salary);
};

class SchedulePrinter
{
public:
  static void Print(const Schedule& salary);
};
```

## III. Open/Close Principle

한 줄 요약하면 `class는 수정에 대해서는 닫혀있고, 확장에 대해서는 열려있어야 한다.`로 요약할 수 있다.
개인적으로 가장 추상적으로 느껴져서 여러 책을 찾아보았고, 그나마 그 중에 아래의 재해석이 가장 마음에 들었다.

- `기존의 코드를 변경하지 않으면서 새 기능을 추가할 수 있어야 한다.`

예를 들어, 아래와 같이 주문(order)에 대하여 배송 방법에 따른 배송비를 합한 전체 금액(total price)을 반환하는 method를 지닌 class를 만들었다고 해보자.
모종의 사유로, 이제 비행기나 육로를 통한 배송이 아닌 배를 통한 배송 방법이 추가된다고 해보자.
이때, 아래 코드로 이 새로운 기능(배로 운송)을 대응하려면 `double GetTotalPrice()` method의 수정이 불가피하다.

```c++
class Order
{
private:
  size_t price_;
  size_t weight_;
  string shipping_;

public:
  double GetTotalPrice() const
  {
    if (shipping_ == "airplane")
    {
      return price_ + weight_ * 2.0;
    }
    else if (shipping == "ground")
    {
      return price_ + weight_ * 1.0;
    }
  }
};
```

반면, 아래와 같이 설계해놓았더라면(다른 챕터에서 언급할테지만 이는 stragedy pattern이다) 배로 배송하는 경우에 대하여 신규로 class 하나만 새로 만들어주면 될 뿐, `Order` class에는 아무런 수정이 필요하지 않게 된다.
이와 같이 신규 기능 추가 시 기존 코드의 수정을 줄이도록 하는 원칙이 open/close principle의 핵심이라고 볼 수 있다.

```c++
class Order
{
private:
  size_t price_;
  size_t weight_;
  Shipping* shipping_;

public:
  double GetTotalPrice() const
  {
    return shipping_->GetCost(price_, weight_);
  }
}

class Shipping
{
public:
  virtual double GetCost(size_t price, size_t weight) const = 0;
};

class Airplane : public Shipping
{
public:
  double GetCost(size_t price, size_t weight) const
  {
    return price + weight * 2.0;
  }
};

class Ground : public Shipping
{
public:
  double GetCost(size_t price, size_t weight) const
  {
    return price + weight * 1.0;
  }
};

class Ship : public Shipping
{
public:
  double GetCost(size_t price, size_t weight) const
  {
    return price + weight * 1.5;
  }
};
```

## IV. Liskov Substitution Principle

한 줄 요약하면, `코드에서 super class의 object가 있을 자리에 derived class의 object를 가져다 놓아도 문제가 없어야 한다.`이다.
상술한 문장 그 자체로 이해가 쉽지만, 다른 원칙들에 비해 비교적 formal하게 rule이 정의가 되어있으므로 지난하더라도 하나하나 살펴보도록 하자.
참고로, 후술에서 표현의 간결함을 위해 아래와 같이 용어를 사용하도록 하겠다.

- **super method**: super class의 method
- **derived method**: derived class의 method
- **super_obj**: super class의 instance
- **derived_obj**: derived class의 instance

### IV.1. Seven Rules for Liskov Substitution

- **Rule 1)** derived method의 parameter type은 super method와 정확하게 일치하거나, 더 추상화 되어 있어야 한다.
  - 조금만 생각해보면 지당하기 그지 없는 말씀이다.
  - super method가 `feed(Cat c)`과 같이 정의되어 있고, 코드의 어느 곳엔가 `super_obj.feed(cat)`과 같은 코드가 존재한다고 해보자.
  - Rule 1은 `super_obj.feed(cat)`을 `derived_obj.feed(cat)`와 같이 치환했을 때, 문제 없이 동작하도록 만들라는 것이다.
  - 이러려면 당연히, `derived_obj.feed` method의 parameter type은 똑같이 `Cat`을 인자로 받거나(i.e. `feed(Cat c)`) 더 추상화된 object를 인자로 받아야 한다(i.e. `feed(Animal a)`).

- **Rule 2)** derived method의 return type은 super method와 정확하게 일치하거나, 덜 추상화 되어 있어야 한다.
  - Rule 1의 역산(?)에 대응되는 말로, 역시 생각해보면 지극히 지당한 말씀이다.
  - super method가 `Cat GetOldest()`과 같이 정의되어 있고, 코드의 어느 곳엔가 `Cat oldest_cat = super_obj.GetOldest()`와 같은 코드가 존재한다고 해보자.
  - `super_obj`를 `derived_obj`로 치환해도 문제가 없으려면 derived method는 정확히 일치하는 return type을 갖거나(i.e. `Cat GetOldest()`) 보다 덜 추상화가 된 return type을 가져야 한다(i.e. `BengalCat GetOldest()`).

- **Rule 3)** derived method는 super method가 throw하지 않을 exception을 throw하면 안된다.
  - 큰 설명이 필요 없을 정도로 간단하다.
  - 만약, derived method가 super method가 throw하지 않던(따라서, 이를 catch하는 구현이 되어 있지 않은 상태) exception을 throw하면, 이는 handling되지 못하고 Software의 중단을 야기한다.
  - 따라서, derived method는 super method가 throw하는 exception만을 throw하여야 한다.

- **Rule 4)** derived method는 super method의 pre-condition을 강화하면 안된다.
  - 코드 내에 존재하는 `super_obj`를 `derived_obj`로 치환했을 때의 문제점을 떠올려보면 이해가 편하다.
  - 예를 들어 `DoSomething(int x)`와 같은 양수/음수를 모두 받을 수 있는 method를 derived method에서 음수를 받으면 exception을 throw하는 식으로 상속하지 말라는 이야기이다.
  - formal한 정의이기에 별도의 Rule로 정리하지만 사실 다른 Rule들과 그닥 orthogonal하게 정돈되지는 않는 듯 하다.

- **Rule 5)** derived method는 super method의 post-condition을 약화하면 안된다.
  - `super_obj.DoSomething()`을 호출한 후의 상황과 `derived_obj.DoSomething()`을 호출한 후의 상황을 동일하게 만들어주어야 한다는 이야기이다.
  - 만약, `super_obj.DoSomething()`가 모든 TCP/IP connection을 disconnect하는 일을 수행한다고 해보자.
  - 그렇다면, 이를 overriding한 `derived_obj.DoSomething()` 역시 모든 TCP/IP connection을 끊어야지, 뭔가를 남겨두면 안된다.

- **Rule 6)** derived method는 super method의 invariant를 보존해야 한다.
  - `super_obj.DoSomething()`을 호출한 후에 바뀌지 않는 것이 보장되었던 것들을 `derived_obj.DoSomething()`을 호출 후에도 보장해주어야 한다는 이야기이다.
  - formal한 정의이기에 별도의 Rule로 정의하지만 사실 Rule 4/5와 큰 차이가 없지 않나 싶다.

- **Rule 7)** derived method는 super method의 private field를 변경해서는 안된다.
  - Rule 7은 매우 명시적인 규칙인데, C++을 사용한다면 syntax적으로 금지되어 있어 크게 고려할 것이 없다.

## V. Interface Segregation Principle

한 줄 요약하면, `필요 없는 기능까지 구현하도록 강제하지 말라.` 정도가 될 수 있다.
예를 들어, 어떤 센서 `X`가 데이터를 요청 (request) 하면, 응답 (response) 로 데이터를 준다고 하자.
이제, 일련의 센서 데이터 수신을 위하여 아래와 같은 interface와 class를 정의하였다.
아래 설계를 마친 뒤에, 이제 센서 `Y`가 시스템에 추가되는 상황을 가정해보자.
그런데, 애석하게도 이번에 추가된 센서 `Y`는 요청을 하지 않아도 계속 응답을 뿌리고 있는 유형의 센서라서, `Request`를 굳이 구현해줄 필요가 없다.
그럼에도 불구하고 interface 역할을 하는 `Sensor`에 `Request`가 존재하기 때문에 우리는 `Y`에 대해서도 아무 일을 하지 않을 `Request` stub를 만들어주어야 한다.

```c++
class Sensor
{
public:
  virtual void Request(const RequestFrame& req) const = 0;
  virtual void ReadResponse(ResponseFrame& res) const = 0;
};

class SensorX
{
  void Request(const RequestFrame& req) const;
  void ReadResponse(ResponseFrame& res) const;
};
```

반면, 아래와 같이 애시 당초 interface를 세분화 시켜 놓는다면 우리는 필요 없는 구현을 강제하지 않을 수 있다.
이와 같이 interface를 세분화해서 필요 없는 구현을 강제하지 않는 것이 Interface Segreagation의 핵심이다.

```c++
class Requester
{
public:
  virtual void Request(const RequestFrame& req) const = 0;
};

class Reader
{
public:
  virtual void ReadResponse(ResponseFrame& res) const = 0;
};

class SensorX : public Requester, Reader
{
public:
  void Request(const RequestFrame& req) const;
  void ReadResponse(ResponseFrame& res) const;  
};

class SensorY : public Reader
{
public:
  void ReadResponse(ResponseFrame& res) const;  
};
```

## VI. Dependency Inversion Principle

한 줄 요약하면, `High-level class가 Low-level class에 의존하지 않도록 하라.` 정도가 될 수 있다.
여기에서 high/low-level class는 상속 관계를 의미한다기 보다 아래와 같이 정말 정성적인 의미로 사용된다.

- Low-level class: disk를 읽고 쓰는 등의 기본 동작들을 관장하는 class
- High-level class: low-level class를 활용하는 비즈니스 로직 등과 같은 class

예를 들어, 예산을 관리하는 software를 아래와 같이 설계하였다고 가장해보자.
아래 구현은 필연적으로 `BudgetManager`의 `AddBudget` method가 `MySQLDB` class에 의존적일 수 밖에 없다.
이는 MySQL 대신 MongoDB를 도입해야 하는 상황이 닥치는 경우를 생각해보면 쉽게 떠올릴 수 있다.

```c++
class MySQLDB
{
public:
  void Insert(const Record& record);
  void Update(const Record& record);
};

class BudgetManager
{
private:
  MySQLDB mysql_db_;

public:
  void AddBudget(const Budget& budget);
};
```

반면, 아래와 같이 high-level class가 low-level class가 아닌 abstraction에 의존하도록 설계해준다면, DB가 변경되는 상황에서도 코드는 재사용성과 확장성을 유지할 수 있다.
이와 같이 high-level class가 low-level class에 의존하지 않고 abstraction에만 의존하도록 하는 것이 dependency inversion의 핵심이다.

```c++
class DB
{
public:
  virtual void Insert(const Record& record) = 0;
  virtual void Update(const Record& record) = 0;
};

class MySQLDB : public DB
{
public:
  void Insert(const Record& record);
  void Update(const Record& record);
};

class MongoDB : public DB
{
public:
  void Insert(const Record& record);
  void Update(const Record& record);
};

class BudgetManager
{
private:
  DB* db_;

public:
  void AddBudget(const Budget& budget);
};
```

<script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
</script>
