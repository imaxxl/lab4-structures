"""Тесты для python/stack.py (pytest).

Покрывают: базовые операции, граничные случаи (пустой стек),
смешанные типы, итерацию, масштабирование.
"""

import pytest

from stack import Stack, StackEmptyError


class TestBasic:
    def test_empty_by_default(self):
        s = Stack()
        assert len(s) == 0
        assert not s
        assert list(s) == []

    def test_push_pop_lifo_order(self):
        s = Stack()
        for i in range(1, 6):
            s.push(i)
        assert len(s) == 5
        for i in range(5, 0, -1):
            assert s.pop() == i
        assert not s

    def test_interleaved_operations(self):
        s = Stack()
        s.push(1)
        s.push(2)
        s.pop()  # сняли 2
        s.push(3)
        s.pop()  # сняли 3
        assert s.pop() == 1
        assert not s


class TestEdgeCases:
    def test_pop_empty_raises(self):
        with pytest.raises(StackEmptyError):
            Stack().pop()

    def test_peek_empty_raises(self):
        with pytest.raises(StackEmptyError):
            Stack().peek()

    def test_peek_does_not_remove(self):
        s = Stack()
        s.push("a")
        s.push("b")
        assert s.peek() == "b"
        assert s.peek() == "b"
        assert len(s) == 2

    def test_clear_and_reuse(self):
        s = Stack()
        for i in range(3):
            s.push(i)
        s.clear()
        assert len(s) == 0
        assert not s
        with pytest.raises(StackEmptyError):
            s.pop()
        s.push(99)  # после clear стек снова usable
        assert s.pop() == 99

    def test_contains(self):
        s = Stack()
        for v in [10, 20, 30]:
            s.push(v)
        assert s.contains(20)
        assert not s.contains(99)
        s.pop()
        assert not s.contains(30)


class TestTypesAndProtocol:
    def test_mixed_types(self):
        s = Stack()
        s.push(1)
        s.push("два")
        s.push(3.0)
        assert s.pop() == 3.0
        assert s.pop() == "два"
        assert s.pop() == 1

    def test_iteration_from_top(self):
        s = Stack()
        for v in [1, 2, 3]:
            s.push(v)
        assert list(s) == [3, 2, 1]

    def test_bool_and_len_after_operations(self):
        s = Stack()
        assert not s
        s.push(1)
        assert s
        assert len(s) == 1
        s.pop()
        assert not s

    def test_repr(self):
        s = Stack()
        s.push(1)
        s.push(2)
        assert repr(s) == "Stack(1 2)"


class TestScale:
    def test_large_volume(self):
        s = Stack()
        n = 10_000
        for i in range(n):
            s.push(i)
        assert len(s) == n
        for i in range(n - 1, -1, -1):
            assert s.pop() == i
        assert len(s) == 0
