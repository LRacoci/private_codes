# Cria a imagem de cartao SD que contem o executavel e o DummyOS
disk.img: api_robot.s api_robot.o robot_ctrl
	mksd.sh --so /home/specg12-1/mc404/simulador/simulador_player/bin/knrl --user robot_ctrl

# Usa o linker para criar o executavel
robot_ctrl: api_robot.o main.o
	arm-eabi-ld main.o api_robot.o -g -o robot_ctrl -Ttext=0x77802000

# Cria o arquivo.o
api_robot.o: api_robot.s
	arm-eabi-as -g api_robot.s -o api_robot.o

# Cria o arquivo main.o
main.o: main.s
	arm-eabi-as -g main.s -o main.o

# Cria o arquivo main.s
main.s: main.c api_robot.h
	arm-eabi-gcc -g main.c -S -o main.s

# Limpa os arquivos
clean:
	rm -f api_robot api_robot.o disk.img main.s main.o

# Roda o programa com o simulador ARM
run: disk.img
	armsim_player --rom=/home/specg12-1/mc404/simulador/simulador_player/bin/dumboot.bin --sd=disk.img

# Roda com suporte ao gdb
gdb: disk.img
	armsim_player --rom=/home/specg12-1/mc404/simulador/simulador_player/bin/dumboot.bin --sd=disk.img -g

# Abre a sessao do player
player:
	player /home/specg12-1/mc404/simulador/simulador_player/worlds_mc404/simple.cfg