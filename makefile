rm -f *.o
rm -f allium/*.o
git submodule update --init
clang -I. -I./allium -I./secp256k1 allium/*.c *.c -o tester -lpthread -lm
