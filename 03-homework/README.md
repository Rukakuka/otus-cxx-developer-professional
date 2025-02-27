### Задание 3
#### Аллокатор
Реализовать свой аллокатор памяти, который позволит выполнять операцию резервирования памяти. Далее использовать этот аллокатор с контейнером `std::map`.

- [x]Аллокатор должен параметризоваться количеством выделяемых за раз элементов. 
- [x] Освобождение конкретного элемента не предполагается - аллокатор должен освобождать всю память самостоятельно.
- [x] Аллокатор работает с фиксированным количеством элементов. Попытку выделить большее число элементов считать ошибкой.
- [x] Опционально реализовать расширяемость аллокатора. При попытке выделить число элементов,которое превышает текущее зарезервированное количество, аллокатор расширяет зарезервированную память.
- [ ] Опционально реализовать поэлементное освобождение.

Цель такого аллокатора – снизить количество операций выделения памяти.

#### Контейнер
Реализовать свой контейнер, который по аналогии с контейнерами stl параметризуется аллокатором. 
- [x] Контейнер должен иметь две возможности - добавить новый элемент и обойти контейнер в одном направлении.
- [x] Опционально реализовать совместимость с контейнерами stl – итераторы, вспомогательные методы size, empty и т.д.

Цель реализации своего контейнера – попробовать использовать `std::allocator``, а также свой аллокатор.

Прикладной код должен содержать следующие вызовы:
- [x] создание экземпляра `std::map<int, int>`
- [x] заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
- [x] создание экземпляра `std::map<int, int>` с новым аллокатором, ограниченным 10
элементами
- [x] заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
- [x] вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
- [x] создание экземпляра своего контейнера для хранения значений типа int
- [x] заполнение 10 элементами от 0 до 9
- [x] создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
ограниченным 10 элементами
- [x] заполнение 10 элементами от 0 до 9
- [x] вывод на экран всех значений, хранящихся в контейнере
---
#### В качестве темплейта проекта использован [cmake-multiplatform-template](https://github.com/CityAplons/cmake-multiplatform-template).