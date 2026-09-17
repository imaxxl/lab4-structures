"""Стек (LIFO) на односвязном списке.

Дополнительное задание лабораторной работы №4: реализация структуры
данных на Python с набором операций, аналогичным C++-версии:
push, pop, peek, contains, clear, len, итерация.
"""

from __future__ import annotations

from typing import Any, Iterator, Optional


class StackEmptyError(Exception):
    """Поп или peek из пустого стека."""


class _Node:
    """Внутренний узел односвязного списка."""

    __slots__ = ("value", "next")

    def __init__(self, value: Any, next_node: Optional["_Node"] = None) -> None:
        self.value = value
        self.next = next_node


class Stack:
    """Стек: последний добавленный элемент снимается первым (LIFO)."""

    def __init__(self) -> None:
        self._top: Optional[_Node] = None
        self._size: int = 0

    def push(self, value: Any) -> None:
        """Положить значение на вершину стека."""
        self._top = _Node(value, self._top)
        self._size += 1

    def pop(self) -> Any:
        """Снять и вернуть верхний элемент."""
        if self._top is None:
            raise StackEmptyError("стек пуст: pop невозможен")
        value = self._top.value
        self._top = self._top.next
        self._size -= 1
        return value

    def peek(self) -> Any:
        """Вернуть верхний элемент без удаления."""
        if self._top is None:
            raise StackEmptyError("стек пуст: peek невозможен")
        return self._top.value

    def contains(self, value: Any) -> bool:
        """Есть ли значение в стеке (линейный поиск)."""
        for item in self:
            if item == value:
                return True
        return False

    def clear(self) -> None:
        """Удалить все элементы."""
        self._top = None
        self._size = 0

    def __len__(self) -> int:
        return self._size

    def __bool__(self) -> bool:
        return self._size > 0

    def __iter__(self) -> Iterator[Any]:
        """Перебор элементов сверху вниз."""
        node = self._top
        while node is not None:
            yield node.value
            node = node.next

    def __repr__(self) -> str:
        inner = " ".join(repr(v) for v in reversed(list(self)))
        return f"Stack({inner})"


if __name__ == "__main__":
    # Мини-демо при запуске: python3 stack.py
    demo = Stack()
    for v in [10, 20, 30]:
        demo.push(v)
    print(f"стек: {demo!r}")
    print(f"peek: {demo.peek()}")
    print(f"pop:  {demo.pop()}")
    print(f"стек: {demo!r}")
