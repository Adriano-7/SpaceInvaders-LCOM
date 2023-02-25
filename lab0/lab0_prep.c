#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for(i = 0; i < 8; i++) {
        binary[i] = n % 2; //Obter o último bit
        n = n / 2; //Equivalente a fazer um right shift
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]);
        
	return binstr;
}

void print_usage(char *name) {
	printf("Usage: %s <action> <byte> <bit no>\n", name);
	printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
		"\t\t <byte> 8-bit integer in hexadecimal\n"
		"\t\t <bit no> of bit to operate on\n");
}

int main(int argc, char *argv[]) {

    //Validation
    if(argc != 4){
        printf("You need to provide at 3 arguments!\n");
        return 1;
    }

    char ch = argv[1][0];
    unsigned long num = strtoul(argv[2], NULL, 16);
    int bit = atoi(argv[3]);

    if(!(ch=='h' || ch=='l' || ch=='s' || ch=='r' || ch=='t')){
        printf("The first argument needs to be one of four: h(high), l(low), s(set), r(reset), t(toggle)");
        return 1;
    }

    if(num>255){
        printf("Byte must be smaller than 256\n");
        return 1;
    }

    if(bit<0 || bit>7){
        printf("Bit must be between 0-7\n");
    }

    //Print the binary representation of the byte before the operation using the function byte2bin
    char binstr[9];
    byte2bin(num, binstr);
    printf("Before: %s\n", binstr);

    if(ch=='h'){
        unsigned long mask = BIT(bit);
        if((num & mask) != 0){
            num = 1;
        }
        else{num=0;}
    }

    if(ch=='l'){
        unsigned long mask = BIT(bit);
        if((num & mask) == 0 ){
            num = 1;
        }
        else{num=0;}
    }

    if(ch=='s'){ //set (Put the given bit 1)
        unsigned long mask = BIT(bit);
        num |= mask;
    }

    if(ch=='r'){ //reset (Put the given bit 0)
        unsigned long mask = ~BIT(bit);
        num &= mask; //Every bit and 0 is 0 (In our mask every bit is 1 except the one we want to change)
    }

    if(ch=='t'){ //toggle (Change bit value - XOR)
        unsigned long mask = BIT(bit);
        num ^= mask;
    }

    byte2bin(num, binstr);
    printf("After: %s\n", binstr);
}