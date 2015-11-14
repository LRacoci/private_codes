# ----------------------------------------
# Disciplina: MC404 - 1o semestre de 2015
# Professor: Edson Borin
#
# Descricao: Makefile para o segundo trabalho 
# ----------------------------------------

# ----------------------------------
# SOUL object files -- Add your SOUL object files here 
SOUL_OBJS=soul.o 

# ----------------------------------
# Compiling/Assembling/Linking Tools and flags
AS=arm-eabi-as
AS_FLAGS=-g

CC=arm-eabi-gcc
CC_FLAGS=-g

LD=arm-eabi-ld
LD_FLAGS=-g

# ----------------------------------
# Default rule
all: disk.img

# ----------------------------------
# Generic Rules
%.o: %.s
	$(AS) $(AS_FLAGS) $< -o $@

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

# ----------------------------------
# Specific Rules
LOCO.x: loco.o bico.o
	$(LD) $^ -o $@ $(LD_FLAGS) -Ttext=0x77802000

disk.img: SOUL.x LOCO.x
	mksd.sh --so SOUL.x --user LOCO.x

clean:
	rm -f SOUL.x LOCO.x disk.img *.o


# Roda o programa com o simulador ARM
run_flags: disk.img
	armsim_player --rom=/home/specg12-1/mc404/simulador/simulador_player/bin/dumboot.bin --sd=disk.img --debug=core,bus,gpt,tzic,uart,ram,rom,cp15,mmu,sd,esdhc,dpllc,ccm

run: disk.img
	armsim_player --rom=/home/specg12-1/mc404/simulador/simulador_player/bin/dumboot.bin --sd=disk.img


# Roda com suporte ao gdb
gdb: disk.img
	arm-eabi-gdb SOUL.x

# Abre a sessao do player
player:
	player /home/specg12-1/mc404/simulador/simulador_player/worlds_mc404/simple.cfg