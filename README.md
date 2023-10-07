# PDP11 basic emulator

![C](https://img.shields.io/badge/C-89%2F99%2F11%2F17-blue)
![License](https://camo.githubusercontent.com/890acbdcb87868b382af9a4b1fac507b9659d9bf/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6c6963656e73652d4d49542d626c75652e737667)
![Build CI Test](https://github.com/franneck94/CProjectTemplate/workflows/Ubuntu%20CI%20Test/badge.svg)

## Установка

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Примеры

Простая програмка - сложить 2 и 3 с полной трассировкой:

```
> ./PDP11Emulator -T ../tests/01_sum/01_sum.pdp.o

---------------- running --------------
001000: mov     #000002,r0              [001002]=000002
---- 0:000002 1:000000 2:000000 3:000000 4:000000 5:000000 S:000000 P:001004
001004: mov     #000003,r1              [001006]=000003
---- 0:000002 1:000003 2:000000 3:000000 4:000000 5:000000 S:000000 P:001010
001010: add     r0,r1                   R0=000002 R1=000005
---- 0:000002 1:000005 2:000000 3:000000 4:000000 5:000000 S:000000 P:001012
001012: halt
---- 0:000002 1:000005 2:000000 3:000000 4:000000 5:000000 S:000000 P:001014

---------------- halted ---------------
r0=000002 r2=000000 r4=000000 sp=000000
r1=000005 r3=000000 r5=000000 pc=001014
psw=000000                    ----
```

Классика:

```
> ./PDP11Emulator ../tests/08_hello/08_hello.pdp.o

---------------- running --------------
Hello, world!
---------------- halted ---------------
r0=000000 r2=000000 r4=000000 sp=000000
r1=000216 r3=000000 r5=000000 pc=001026
psw=000004                     z
```

## Использование

```
Usage: ./pdp.exe [options] initial-core-file

Options:
        -s N    starting address, octal (default 1000)
        -n      step mode, command is executed after pressing the 'n' key
        -q      quiet, don't show anything except target's output
        -t      show trace to stdout
        -T      show verbose trace to stdout
```

## PDP11

Смотрите подробнее в [ТЗ](https://github.com/VSWeatherfield/PDP11_Emulator/blob/dev/docs/TechnicalTask.md)

## Тестирование

```bash
mkdir testbuild
cd testbuild
cmake ..
make
make test
```

## Полезные ссылки

Doxygen документация: [link](https://vsweatherfield.github.io/PDP11_Emulator/) \
Полный список команд: [link](http://acm.mipt.ru/twiki/bin/view/Cintro/PDPCommandList?sortcol=1&table=1&up=1)