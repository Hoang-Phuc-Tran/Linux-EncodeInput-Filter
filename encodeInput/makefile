#  
#  FILE          : makefile
#  PROJECT       : A-01 - The cryptoMagic Utility
#  By	         : Hoang Phuc Tran
#  FIRST VERSION : Hoang Phuc Tran
#  DESCRIPTION   : This make file will compile the source files
#
./bin/encodeInput : ./obj/encodeInput.o ./obj/s_record.o ./obj/assembly.o
	cc ./obj/encodeInput.o ./obj/s_record.o ./obj/assembly.o  -o ./bin/encodeInput
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/encodeInput.o : ./src/encodeInput.c ./inc/s_record.h ./inc/assembly.h
	cc -c ./src/encodeInput.c -o ./obj/encodeInput.o

./obj/s_record.o : ./src/s_record.c ./inc/s_record.h
	cc -c ./src/s_record.c -o ./obj/s_record.o
	
./obj/assembly.o : ./src/assembly.c ./inc/assembly.h
	cc -c ./src/assembly.c -o ./obj/assembly.o	
	

#
# =======================================================
# Other targets
# =======================================================                     

all : ./bin/encodeInput

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


