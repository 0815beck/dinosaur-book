#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {

    if (argc != 3) {
        perror("Error: You need to provide one input and one output file");
    }

    size_t MAX = 1024;
    char * sourceFileName = argv[1];
    char * targetFileName = argv[2];

    FILE * sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) {
        perror("Souce file could not be opened.\n");
        exit(1);
    }

    FILE * targetFile = fopen(targetFileName, "w");
    if (targetFile == NULL) {
        perror("Target file could not be opened.\n");
        fclose(sourceFile);
        exit(1);
    }

    int c;
    while ((c = fgetc(sourceFile)) != EOF) {
        if (fputc(c, targetFile) == EOF) {
            perror("Error while writing to target file.\n");
            fclose(targetFile);
            fclose(sourceFile);
            if (remove(targetFileName) != 0) {
                perror("Unable to delete the incomplete target file.\n");
            }
            exit(1);
        }
    }

    printf("[Info] File has been successfully copied.\n");
    fclose(targetFile); 
    fclose(sourceFile);
    exit(1);

}