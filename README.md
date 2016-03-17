# Лабораторая №1. Работа с сигналами.

Компиляция: make.
Очистка проекта: make clean.
Запуск:
Переходим в папку bin и выполняем одно из следующих действий:
- в режиме std: ./lab --mode=std;
- в режиме pipe: ./lab --mode=pipe;
- в режиме child: ./lab --mode=child;
- в режиме posix: ./lab --mode=posix --amount=<число сигналов>;
- в режиме kill: ./lab --mode=kill --signal=<номер сигнала> --pid=<PID сигнала>.
