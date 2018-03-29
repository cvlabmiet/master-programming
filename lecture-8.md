---
title: Master programming
subtitle: Лекция №8 (Методики программирования на C++)
author: Игорь Шаронов
date: 2018-03-28
---

# Различия наследований {#inheritance}

* Наследование -- компилятор по типу класса определяет таблицу функций
* Наследование в полиморфизме:
    * Справедливо только для указателей или ссылок на базовый класс
    * Работает в рантайме
    * Компилятор не может по типу указателя базового класса определить тип объекта
    * Каждый объект содержит указатель на таблицу функций (методов)
        * таблицы функций используются одни и те же для одинаковых типов

# Перегрузка {#override}

* Перегрузка функций возможна только в сигнатуре
    * Возвращаемое значение не входим в сигнатуру (в C++)
* Специализация класса -- это тоже вид перегрузки
* Частичная специализация класса
    * Частичной специализации функции не бывает (не отличимо от обычной перегрузки)
* Можно делать только специализации
    * Более общий шаблонный класс останется пустым
    * Сигнализация об ошибке будет только в том случае, если не подойдёт ни одна специализация

# SFINAE {#sfinae}

* [Substitution Failure Is Not A Error](http://en.cppreference.com/w/cpp/language/sfinae)
* Если вывод специализации приводит к ошибке, то
    * данная специализация отбрасывается
    * переходим к следующей специализации

```cxx
template <class T> int f(typename T::B*);
template <class T> int f(T);
int i = f<int>(0); // uses second overload
```

# Проектирование интерфейсов {#interface-design}

<https://ru.wikipedia.org/wiki/SOLID_(объектно-ориентированное_программирование)>

* SOLID:
    * Принцип единственной ответственности (The Single Responsibility Principle)
    * Принцип открытости/закрытости (The Open Closed Principle)
    * Принцип подстановки Барбары Лисков (The Liskov Substitution Principle)
    * Принцип разделения интерфейса (The Interface Segregation Principle)
    * Принцип инверсии зависимостей (The Dependency Inversion Principle)
* Критерии SOLID:
    * Закрепощённость
    * Неустойчивость
    * Неподвижность
    * Вязкость
    * Неоправданная сложность
    * Неопределённость

---

## Шаблоны {#templates}

* Уровень компиляции
* `template<class T> int func();`, где `T` -- шаблонный параметр
* `func<int>();`, где `int` -- аргумент шаблона
* Параметр шаблона может быть не-типовым (int, char, auto)
    * Исключение: это не указатель и не тип `double|float`
* `template<class... Ts> class myclass;` -- пакет шаблонных параметров
* `template<class T> constexpr T pi = T(3.1415926535897932385L);` -- шаблонная переменная
* `template<class... Ts, size_t N = sizeof...(Ts)> class my;`

## Операции над шаблонными пакетами {#template-parameter-pack}

```cxx
template <typename... bases>
struct X : bases... {
    using bases::g...;
};
X<B, D> x;
```

Свёртки

* `( pack op ... )` -- свёртка слева
    * `( pack op ... op init )` -- свёртка слева с начальным значением
* `( ... op pack )` -- свёртка справа
    * `( init op ... op pack )` -- свёртка справа с начальным значением

```cxx
template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args)
{
    (v.push_back(args), ...);
}
```

---

# Концепты и ограничители {#concepts}

```cxx
template<typename T>
concept EqualityComparable = requires(T a, T b)
{
    { a == b } -> bool;
}; // концепт

template<EqualityComparable T> void f(T&&); // ограничитель

EqualityComparable{T} void f(T&&); // укороченная форма
```
