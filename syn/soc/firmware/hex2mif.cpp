/*
 * This file is subject to the terms and conditions of the BSD License. See
 * the file "LICENSE" in the main directory of this archive for more details.
 *
 * Copyright (C) 2014 Aleksander Osman
 */

/* This is a very simple converter from a ihex file generated by the GNU
 * toolchain to a Altera MIF file.
 */ 

#include <cstdio>
#include <cstring>
#include <cstdlib>

int main() {
    char line[256];
    
    int depth = 1024;
    
    printf("WIDTH=32;\n");
    printf("DEPTH=%d;\n", depth);
    printf("ADDRESS_RADIX=HEX;\n");
    printf("DATA_RADIX=HEX;\n");
    printf("CONTENT BEGIN\n");
        
    int address = 0;
    while(1) {
        char *ret_ptr = fgets(line, sizeof(line), stdin);
        if(ret_ptr == NULL) break;
        
        int len = strlen(line);
        if(len > 0 && line[0] == ':') { //hex line
            int hex_len, type;
            sscanf(line+1, "%02x", &hex_len);
            sscanf(line+7, "%02x", &type);
                        
            if(type == 0) { //data type
                if((hex_len % 4) != 0) {
                    fprintf(stderr, "Error: data entry size not multiple of 4.\n");
                    return -1;
                }
                for(int i=0; i<hex_len/4; i++) {
                    unsigned int val;
                    sscanf(line+(9+i*8), "%08x", &val);
                    val = ((val >> 24) & 0xFF) | ((val >> 8) & 0xFF00) | ((val << 8) & 0xFF0000) | ((val << 24) & 0xFF000000);
                    printf("%03x : %08x;\n", address++, val);
                }
                while((hex_len/4) < 4) {
                    printf("%03x : %08x;\n", address++, 0);
                    hex_len += 4;
                }
            }
        }
    }
    while(address < depth) printf("%03x : %08x;\n", address++, 0);
    printf("END;\n");
    return 0;
}

