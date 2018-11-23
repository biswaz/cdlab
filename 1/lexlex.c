#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


/*
Tokens in C
* Keywords
* Identifiers
* Constants (eg: 10, 30)
* Strings
* Special symbols (eg: (), {}),
* Operators
*/


int isKeyword(char buffer[]){
    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
                            "do","double","else","enum","extern","float","for","goto",
                            "if","int","long","register","return","short","signed",
                            "sizeof","static","struct","switch","typedef","union",
                            "unsigned","void","volatile","while"};
    int i, flag = 0;

    for(i=0; i<32; ++i) {
        if(strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}

int isOperator(char ch){
    char operators[] = "+-*/=%";
    for(int i = 0; i<6; ++i) {
        if(ch == operators[i])
            return 1;
    }
    return 0;
}

int isConstant(char buffer[]) {
    for(int i=0; buffer[i]!='\0'; i++) {
        if (!isdigit(buffer[i]))
            return 0;
    }
    return 1;
}

int isSpecialSymbol(char ch) {
    char specials[] = "(){},;*#";
    for(int i = 0; i<8; ++i) {
        if(ch == specials[i])
            return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[15], string_buffer[15];
    FILE *fp;
    int i,j = 0, k = 0;
    int inString = 0;

    fp = fopen("exp1_input_program.txt", "r");

    if (fp == NULL) {
        printf("Error while opening the file!\n");
        exit(0);
    }

    while((ch = fgetc(fp)) != EOF) {
        if(isOperator(ch) == 1)
            printf("%c is an operator\n", ch);
        else if((isalnum(ch) || ch=='_' || ch=='$') && inString == 0)
            buffer[j++] = ch;
        else if(isalnum(ch) && inString == 1)
            string_buffer[k++] = ch;
        else if(ch == '"' && inString == 0) {
            inString = 1;
            string_buffer[k++] = ch;
        }
        else if(ch == '"' && inString == 1) {
            inString = 0;
            string_buffer[k++] = ch;
            string_buffer[k] = '\0';
            k = 0;
            printf("%s is a string\n", string_buffer);
        }
        else if((ch == ' ' || ch == '\n') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;
            if (isKeyword(buffer) == 1)
                printf("%s is a keyword\n", buffer);
            else if (isConstant(buffer) == 1)
                printf("%s is a constant\n", buffer);
            else 
                printf("%s is an identifier\n", buffer);
        }
        else if(isSpecialSymbol(ch))
            printf("%c is a special symbol\n", ch);
    }

    if (j!= 0) {
        buffer[j] = '\0';
        j = 0;
        if (isKeyword(buffer) == 1)
            printf("%s is a keyword\n", buffer);
        else if (isConstant(buffer) == 1)
            printf("%s is a constant\n", buffer);
        else 
            printf("%s is an identifier\n", buffer);

    }
    


    fclose(fp);
    return 0;
}
