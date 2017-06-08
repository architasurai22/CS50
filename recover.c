#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 
 
 
 int main(int argc, char *argv[])
 {
    if(argc!=2)
    {
        fprintf(stderr,"./recover image\n");
        return 1;
    }
    char* infile;
    infile = argv[1];
    
    
    FILE* file1;
    
    char filename[10];
    file1 = fopen(infile, "r");
    
    if (file1 == NULL)
    {
        fprintf(stderr,"Error opening the input file\n");
        return 1;
    }
    
    uint8_t buffer[512];
    uint8_t jpeg1[4] = {0xff, 0xd8, 0xff, 0xe0};
	uint8_t jpeg2[4] = {0xff, 0xd8, 0xff, 0xe1};
    uint8_t jpeg3[4];
    int count = 0;
    FILE *file2 = NULL;
    
    // Iterate over file contents
    while (fread(buffer,512, 1, file1))
    {
        jpeg3[0] = buffer[0];
        jpeg3[1] = buffer[1];
        jpeg3[2] = buffer[2];
        jpeg3[3] = buffer[3];
        if((memcmp(jpeg1, jpeg3, sizeof(jpeg3)) == 0 ) || (memcmp(jpeg2, jpeg3, sizeof(jpeg3)) == 0))
        {
            if (file2 != NULL)
                fclose(file2);
            
            
            sprintf(filename, "%03d.jpg", count);
            count++;
            file2 = fopen(filename, "w");
        }
        
        if (file2 != NULL)
            fwrite(buffer,512, 1, file2);
    }
    
    if (file2 != NULL)
        fclose(file2);
    
    fclose(file1);
 
    return 0;
 } 
