# lab-z80

レトロな 8 ビット CPU **Z80（通称ゼッパチ）** を、いまの C ツールチェーン
（[SDCC](https://sdcc.sourceforge.net/) + 同梱の Z80 シミュレータ
`ucsim_z80`）で動かす実験ノートです。リセットベクタから C の `printf` まで、
端から端まで自分の目で追えることを目標にしています。

解説記事（連載）は Zenn に書いています → <https://zenn.dev/logicia32>

## 中身

| パス | 内容 |
|---|---|
| `examples/console.h` / `console.c` | Z80 にコンソールが無いので、`putchar` を 1 関数だけ移植して stdout の出口を作る最小実装 |
| `examples/hello.c` | `printf("Hello, Z80!")` と `%d` 書式変換を Z80 上で動かす |
| `examples/bsearch.c` | 二分探索を C で書き、`printf` で期待値と突き合わせて PASS/FAIL を出す |
| `examples/Makefile` | ビルドと実行（`make` / `make run-hello` / `make run-bsearch`） |

## 前提

SDCC と `ucsim_z80` を各自インストールし、PATH に通してください
（多くのディストリでは SDCC パッケージに `ucsim_z80` が同梱されます）。

動作確認した版:

```text
SDCC      4.5.24 #16530 (Linux)
ucsim_z80 0.9.9
```

別の場所に置いた処理系を使う場合は `make SDCC=/path/to/sdcc UCSIM=/path/to/ucsim_z80`。

## ビルドと実行

```sh
cd examples
make            # hello.ihx / bsearch.ihx を生成
make run-hello  # => Hello, Z80!  /  7 * 6 = 42
make run-bsearch# => bsearch(...) ... : PASS x4
make clean
```

## 設計メモ：コンソールは I/O ポートに置く

`putchar` の出口（ucsim の simif）は**メモリではなく I/O ポート 0x80**に
置いています。SDCC の既定 `crt0` は `LD SP,#0` でスタックを 0xFFFF から
下方向に伸ばすため、メモリ上位（例: 0xFFF0）にデバイスを置くと、再帰や
引数の多い `printf` でスタックがデバイスを踏み潰します。実機の UART と
同じく I/O 空間へ逃がすのが安全側です。詳細は Zenn の記事に書きました。

## ライセンス

[MIT](LICENSE)
