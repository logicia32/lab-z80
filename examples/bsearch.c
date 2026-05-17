#include <stdio.h>
#include "console.h"

/*
 * 二分探索を Z80 で動かし、結果を printf で検証する。
 * 「動いた」と「正しく動いた」は別物なので、期待値と突き合わせて
 * PASS/FAIL まで出す。
 */
static const unsigned char a[8] = {2, 5, 8, 12, 20, 33, 41, 57};

static unsigned char bsearch8(unsigned char key)
{
    unsigned char lo = 0, hi = 7, mid;
    while (lo <= hi) {
        mid = (unsigned char)((lo + hi) >> 1);
        if (a[mid] == key) return mid;
        if (a[mid] < key) {
            lo = (unsigned char)(mid + 1);
        } else {
            if (mid == 0) break;
            hi = (unsigned char)(mid - 1);
        }
    }
    return 0xFF;               /* not found */
}

static void check(unsigned char key, unsigned char expect)
{
    unsigned char got = bsearch8(key);
    /* 可変長引数の char は int 昇格されるが、明示キャストで 16bit 渡し
       を保証しておくのが安全(高位バイトのゴミを防ぐ)。 */
    printf("bsearch(%u) -> %u (expect %u) : %s\n",
           (unsigned)key, (unsigned)got, (unsigned)expect,
           (got == expect) ? "PASS" : "FAIL");
}

void main(void)
{
    check(33, 5);              /* a[5] == 33     */
    check(2,  0);              /* 先頭           */
    check(57, 7);              /* 末尾           */
    check(7,  0xFF);           /* 配列に無い     */
    sim_exit();
}
