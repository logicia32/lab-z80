#include <stdio.h>
#include "console.h"

/*
 * 40 年前の命令セットの上で、いまの C の printf を動かす。
 * 文字列も書式変換 (%d) も標準ライブラリ任せ。最後の出口だけ
 * console.c の putchar が握っている。
 */
void main(void)
{
    printf("Hello, Z80!\n");
    printf("7 * 6 = %d\n", 7 * 6);
    sim_exit();
}
