"""Подстановка каталога python/ в sys.path, чтобы pytest видел stack.py."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
