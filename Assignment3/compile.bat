g++ -c main1.cpp -o main1.o
g++ -c hw3_p1.cpp -o hw3_p1.o
ar rcs libhw3_p1.a hw3_p1.o
g++ main1.o -L. -lhw3_p1 -o prog1
.\prog1.exe

@REM g++  main2.cpp -o prog2 
@REM g++ -O3 main2.cpp -o prog2 
@REM g++ -ffast-math main2.cpp -o prog2 
g++ -Ofast main2.cpp -o prog2 
.\prog2