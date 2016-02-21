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
%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(AS_FLAGS) $< -o $@



# ----------------------------------
# Specific Rules
SOUL.x: $(SOUL_OBJS)
	$(LD) $^ -o $@ $(LD_FLAGS) --section-start=.iv=0x778005e0 -Ttext=0x77800700 -Tdata=0x77801800 -e 0x778005e0

# Trocar segue-parede por ronda para a logica de controle da ronda
LOCO.x: ronda.o bico.o 
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

run_gdb_flags: disk.img
	armsim_player --rom=/home/specg12-1/mc404/simulador/simulador_player/bin/dumboot.bin --sd=disk.img -g --debug=core,gpt,tzic,cp15,sd

run_gdb: disk.img
	armsim_player --rom=/home/specg12-1/mc404/simulador/simulador_player/bin/dumboot.bin --sd=disk.img -g

# Roda com suporte ao gdb
gdb: disk.img
	arm-eabi-gdb SOUL.x --command=gdb_initialization
gdb_loco: disk.img
	arm-eabi-gdb LOCO.x --command=gdb_loco

# Abre a sessao do player
player:
	player /home/specg12-1/mc404/simulador/simulador_player/worlds_mc404/simple.cfg