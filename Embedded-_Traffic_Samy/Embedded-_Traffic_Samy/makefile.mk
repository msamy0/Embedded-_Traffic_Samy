avr-gcc -c -mmcu=atmega128 -I. -gdwarf-2 -DF_CPU=8000000UL  -O3 -funsigned-char
-funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -Wa,-
adhlns=eric.lst  -std=gnu99 -MD -MP -MF .dep/eric.o.d eric.c -o eric.o
eric.c:20:2: warning: #warning "hello"