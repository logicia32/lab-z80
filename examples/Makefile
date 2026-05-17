# lab-z80 / examples — SDCC + ucsim_z80
#
#   make            ... hello と bsearch をビルド
#   make run-hello  ... hello を ucsim_z80 で実行
#   make run-bsearch... bsearch を ucsim_z80 で実行
#   make clean      ... 生成物を消す
#
# SDCC ドライバが compile -> assemble -> link -> .ihx までを一括で行う。
# simif はメモリではなく I/O ポート 0x80 に出す (-I if=outputs[0x80])。
# メモリに置くと既定 crt0 の LD SP,#0 で降りてくるスタックに踏まれるため。

# SDCC / ucsim_z80 は各自インストールし PATH に通す（既定はそれを使う）。
# 別の場所のものを使う場合: make SDCC=/path/to/sdcc UCSIM=/path/to/ucsim_z80
SDCC   ?= sdcc
UCSIM  ?= ucsim_z80
CFLAGS  = -mz80
SIMIF   = -I if=outputs[0x80]

all: hello.ihx bsearch.ihx

# .c -> .rel (compile + assemble)。-c で「リンクはまだ」を指示。
%.rel: %.c console.h
	$(SDCC) $(CFLAGS) -c $< -o $@

# .rel をまとめて link -> .ihx。putchar の実体は console.rel が供給する。
hello.ihx: hello.rel console.rel
	$(SDCC) $(CFLAGS) hello.rel console.rel -o hello.ihx

bsearch.ihx: bsearch.rel console.rel
	$(SDCC) $(CFLAGS) bsearch.rel console.rel -o bsearch.ihx

run-hello: hello.ihx
	printf 'run\nquit\n' | $(UCSIM) -t Z80 $(SIMIF) hello.ihx

run-bsearch: bsearch.ihx
	printf 'run\nquit\n' | $(UCSIM) -t Z80 $(SIMIF) bsearch.ihx

clean:
	rm -f *.ihx *.asm *.lst *.rel *.sym *.map *.noi *.lk *.bin

.PHONY: all run-hello run-bsearch clean
