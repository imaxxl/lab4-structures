# Лабораторная работа №4 — структуры данных и тестирование

Дисциплина: «Основы безопасной разработки».

Что внутри:
- три структуры данных на C++: стек, очередь, двоичное дерево поиска;
- консольное приложение с меню, управление из командной строки;
- 41 тест на GoogleTest;
- отчёт покрытия кода (lcov + genhtml) — 94.1%;
- доп. задание: стек на Python, 13 тестов на pytest, покрытие 87% (pytest-cov).

## Структуры

| Структура | Как реализовано | Операции |
|---|---|---|
| `Stack<T>` | на `std::vector` | push, pop, top + contains, size, clear, to_string |
| `Queue<T>` | кольцевой буфер | enqueue, dequeue, front, back + contains, size, clear, to_string |
| `BinarySearchTree<T>` | указатели на узлы | insert, erase, contains + min, max, height, inorder, preorder |

Очередь сделана на кольцевом буфере — при переполнении буфер расширяется,
а «голова» сдвигается без переноса всех элементов. Удаление из дерева работает
в трёх случаях: лист, один потомок, два потомка (замена на инордер-продолжателя).

Граничные случаи (pop из пустого стека, dequeue из пустой очереди, min/max из
пустого дерева) бросают исключения StackEmptyError, QueueEmptyError, TreeEmptyError.

## Сборка

Нужны: g++ (C++17), CMake, make. Для тестов нужен интернет — gtest скачивается
сам через FetchContent.

```bash
cmake -B build
cmake --build build -j
./build/lab4_app
```

В приложении: главное меню → 1/2/3 выбрать структуру → команды вида
`1 42`, `pop`, `top`, `contains 42`, `size`, `clear`, `show`; `0` — назад в
главное меню. Есть готовый прогон для демо:

```bash
./build/lab4_app < demo_input.txt
```

## Тесты

```bash
./build/lab4_tests
```

41 тест, все проходят:

```
[==========] 41 tests from 3 test suites ran.
[  PASSED  ] 41 tests.
```

## Покрытие кода

```bash
./coverage.sh
```

Скрипт собирает проект с флагом --coverage, запускает тесты и демо, а потом
делает HTML-отчёт: `coverage/index.html`.

| Файл | Строки |
|---|---|
| src/stack.cpp | 100% |
| src/queue.cpp | 100% |
| src/binary_tree.cpp | 98.4% |
| src/main.cpp | 75.8% |
| tests/ | ~99% |
| **Итого** | **94.1%** (нужно было 70+) |

## Python (доп. задание)

`python/stack.py` — стек на односвязном списке, операции те же, что в C++:
push, pop, peek, contains, clear, len, итерация.

```bash
cd python
python3 -m pytest tests -v --cov=stack --cov-report=term-missing --cov-report=html:htmlcov
```

Результат: 13 passed, покрытие 87%. Отчёт: `python/htmlcov/index.html`.
Единственное непокрытое — блок `if __name__ == "__main__"` (демо, намеренно
не покрывается).

## Для отчёта

- скриншот тестов C++: `./build/lab4_tests`
- скриншот тестов Python: `python3 -m pytest` в каталоге `python/`
- скриншот покрытия: `coverage/index.html` и `python/htmlcov/index.html`
