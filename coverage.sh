#!/usr/bin/env bash
# Сборка с покрытием, запуск тестов и генерация HTML-отчёта (lcov + genhtml).
set -euo pipefail
cd "$(dirname "$0")"

BUILD_DIR=build-coverage

cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_CXX_FLAGS="--coverage -O0 -g" \
      -DLAB4_BUILD_TESTS=ON
cmake --build "$BUILD_DIR" -j"$(nproc)"

# Запускаем приложение на демо-вводе, чтобы покрыть код main.cpp.
./"$BUILD_DIR/lab4_app" < demo_input.txt > /dev/null

# Запускаем тесты (они покрывают структуру данных).
./"$BUILD_DIR/lab4_tests"

lcov --capture --directory "$BUILD_DIR" --output-file coverage.raw.info \
     --rc geninfo_unexecuted_blocks=1 \
     --ignore-errors inconsistent,mismatch
lcov --remove coverage.raw.info '/usr/*' '*/_deps/*' \
     --output-file coverage.info \
     --ignore-errors inconsistent,mismatch
genhtml coverage.info --output-directory coverage

echo "Готово. Отчёт: $(pwd)/coverage/index.html"
