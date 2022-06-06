#include <stdio.h>
 
#define MAXCHAR 1000
int main() {
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "c:\\temp\\test.txt";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);
    return 0;
}


#define MAXCHAR 1000

void parseFile(pointer to ){
    file *fp;
    char str[MAXCHAR];
    char *filename = "c:\\input.txt";

    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Failed to Open input file");
        return;
    }
    while(read = getLine(&line)) 


    }


 decodeLine(String line){
     line
    
}







int parseInput(pointer to the current node)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

   fp = fopen("c:\\input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

   while ((read = getline(&line, &len, fp)) != -1) {
        thisLine = read;
        
        
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

   free(line);
    exit(EXIT_SUCCESS);
}








}
