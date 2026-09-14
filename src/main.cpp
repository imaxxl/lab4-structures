// Консольное приложение: интерактивное меню для
// стека, очереди и двоичного дерева поиска.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "binary_tree.h"
#include "queue.h"
#include "stack.h"

namespace {

using lab4::BinarySearchTree;
using lab4::Queue;
using lab4::Stack;

// Читает один токен как целое число. false, если токена нет или это не число.
bool read_int(std::istringstream& in, long long& out) {
    std::string token;
    if (!(in >> token)) {
        return false;
    }
    try {
        std::size_t pos = 0;
        out = std::stoll(token, &pos);
        return pos == token.size();
    } catch (const std::exception&) {
        return false;
    }
}

int stack_menu(Stack<int>& stack) {
    for (;;) {
        std::cout <<
            "\n[Стек]     1) push <x>   2) pop        3) top         4) contains <x>\n"
            "           5) size       6) clear      7) show        0) назад\n"
            "stack> ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            return 0;
        }
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        long long x = 0;

        try {
            if (cmd == "1") {
                if (!read_int(iss, x)) {
                    std::cout << "нужно целое число\n";
                } else {
                    stack.push(static_cast<int>(x));
                    std::cout << "стек: " << stack.to_string() << "\n";
                }
            } else if (cmd == "2") {
                stack.pop();
                std::cout << "элемент снят, стек: " << stack.to_string() << "\n";
            } else if (cmd == "3") {
                std::cout << "top = " << stack.top() << "\n";
            } else if (cmd == "4") {
                if (!read_int(iss, x)) {
                    std::cout << "нужно целое число\n";
                } else {
                    std::cout << "contains(" << x << ") = "
                              << (stack.contains(x) ? "да" : "нет") << "\n";
                }
            } else if (cmd == "5") {
                std::cout << "size = " << stack.size() << "\n";
            } else if (cmd == "6") {
                stack.clear();
                std::cout << "стек: " << stack.to_string() << "\n";
            } else if (cmd == "7") {
                std::cout << "стек: " << stack.to_string() << "\n";
            } else if (cmd == "0") {
                return 0;
            } else {
                std::cout << "неизвестная команда\n";
            }
        } catch (const lab4::StackEmptyError& e) {
            std::cout << "ошибка: " << e.what() << "\n";
        }
    }
}

int queue_menu(Queue<int>& queue) {
    for (;;) {
        std::cout <<
            "\n[Очередь]  1) enqueue <x>  2) dequeue    3) front     4) back\n"
            "           5) contains <x> 6) size       7) clear     8) show   0) назад\n"
            "queue> ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            return 0;
        }
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        long long x = 0;

        try {
            if (cmd == "1") {
                if (!read_int(iss, x)) {
                    std::cout << "нужно целое число\n";
                } else {
                    queue.enqueue(static_cast<int>(x));
                    std::cout << "очередь: " << queue.to_string() << "\n";
                }
            } else if (cmd == "2") {
                int value = queue.dequeue();
                std::cout << "снята: " << value
                          << ", очередь: " << queue.to_string() << "\n";
            } else if (cmd == "3") {
                std::cout << "front = " << queue.front() << "\n";
            } else if (cmd == "4") {
                std::cout << "back = " << queue.back() << "\n";
            } else if (cmd == "5") {
                if (!read_int(iss, x)) {
                    std::cout << "нужно целое число\n";
                } else {
                    std::cout << "contains(" << x << ") = "
                              << (queue.contains(x) ? "да" : "нет") << "\n";
                }
            } else if (cmd == "6") {
                std::cout << "size = " << queue.size() << "\n";
            } else if (cmd == "7") {
                queue.clear();
                std::cout << "очередь: " << queue.to_string() << "\n";
            } else if (cmd == "8") {
                std::cout << "очередь: " << queue.to_string() << "\n";
            } else if (cmd == "0") {
                return 0;
            } else {
                std::cout << "неизвестная команда\n";
            }
        } catch (const lab4::QueueEmptyError& e) {
            std::cout << "ошибка: " << e.what() << "\n";
        }
    }
}

int tree_menu(BinarySearchTree<int>& tree) {
    for (;;) {
        std::cout <<
            "\n[Дерево]   1) insert <x>   2) erase <x>    3) contains <x>\n"
            "           4) min          5) max          6) height\n"
            "           7) size         8) inorder      9) clear\n"
            "           0) назад\n"
            "tree> ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            return 0;
        }
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        long long x = 0;

        try {
            if (cmd == "1") {
                if (!read_int(iss, x)) {
                    std::cout << "нужно целое число\n";
                } else {
                    bool added = tree.insert(static_cast<int>(x));
                    std::cout << (added ? "добавлено" : "уже есть") << ": "
                              << tree.to_string() << "\n";
                }
            } else if (cmd == "2") {
                if (!read_int(iss, x)) {
                    std::cout << "нужно целое число\n";
                } else {
                    bool removed = tree.erase(static_cast<int>(x));
                    std::cout << (removed ? "удалено" : "не найдено") << ": "
                              << tree.to_string() << "\n";
                }
            } else if (cmd == "3") {
                if (!read_int(iss, x)) {
                    std::cout << "нужно целое число\n";
                } else {
                    std::cout << "contains(" << x << ") = "
                              << (tree.contains(x) ? "да" : "нет") << "\n";
                }
            } else if (cmd == "4") {
                std::cout << "min = " << tree.minimum() << "\n";
            } else if (cmd == "5") {
                std::cout << "max = " << tree.maximum() << "\n";
            } else if (cmd == "6") {
                std::cout << "height = " << tree.height() << "\n";
            } else if (cmd == "7") {
                std::cout << "size = " << tree.size() << "\n";
            } else if (cmd == "8") {
                std::vector<int> keys;
                tree.inorder(keys);
                for (std::size_t i = 0; i < keys.size(); ++i) {
                    if (i != 0) {
                        std::cout << ' ';
                    }
                    std::cout << keys[i];
                }
                std::cout << "\n";
            } else if (cmd == "9") {
                tree.clear();
                std::cout << "дерево: " << tree.to_string() << "\n";
            } else if (cmd == "0") {
                return 0;
            } else {
                std::cout << "неизвестная команда\n";
            }
        } catch (const lab4::TreeEmptyError& e) {
            std::cout << "ошибка: " << e.what() << "\n";
        }
    }
}

}  // namespace

int main() {
    std::cout << "Лабораторная работа №4. Структуры данных (C++)\n"
              << "Реализованы: стек, очередь, двоичное дерево поиска.\n";

    Stack<int> stack;
    Queue<int> queue;
    BinarySearchTree<int> tree;

    for (;;) {
        std::cout <<
            "\n[Главное меню]\n"
            " 1) Стек (LIFO)\n"
            " 2) Очередь (FIFO)\n"
            " 3) Двоичное дерево поиска\n"
            " 0) Выход\n"
            "main> ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "1") {
            stack_menu(stack);
        } else if (cmd == "2") {
            queue_menu(queue);
        } else if (cmd == "3") {
            tree_menu(tree);
        } else if (cmd == "0" || cmd == "exit" || cmd == "q") {
            break;
        } else {
            std::cout << "неизвестная команда\n";
        }
    }

    std::cout << "Программа завершена.\n";
    return 0;
}
