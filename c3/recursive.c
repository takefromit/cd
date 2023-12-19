#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char input[100];
int ptr = 0;

int E();
int Eprime();
int T();
int Tprime();
int F();

int E() {
    int res = T();
    if (res == -1)
        return -1;
    res = Eprime();
    return res;
}

int Eprime() {
    if (input[ptr] == '+' && input[ptr+1] != '\0') {
        ptr++;
        int res = T();
        if (res == -1)
            return -1;
        res = Eprime();
        return res;
    }
    return 1; // Successful parse
}

int T() {
    int res = F();
    if (res == -1)
        return -1;
    res=Tprime();
    return res;
}

int Tprime() {
    if (input[ptr] == '*' && input[ptr+1] != '\0') {
        ptr++;
        int res = F();
        if (res == -1)
            return -1;
        res=Tprime();
        return res;
    }
    return 1; // Successful parse
}

int F() {
    if (input[ptr] == '(') {
        ptr++;
        int res = E();
        if(res==-1)
        {
            return -1;
        }
        if (input[ptr] == ')')
            ptr++;
        if (res == -1)
            return -1;
        return 1; // Successful parse
    } else {
        if (input[ptr] == 'i') {
            ptr++;
            return 1; // Successful parse
        }
    }
    return -1; // Parsing failed
}

int main() {
    printf("Enter the string to be parsed\n");
    scanf("%s", input);
    int res = E();
    if (res == 1 && input[ptr] == '\0')
        printf("String is accepted\n");
    else
        printf("String is not accepted\n");
    return 0;
}









/ Construct a recursive descent parser for an expression
// Grammar:  E-> TE'
//           E'->+TE'|e
//           T->FT'
//           T'->*FT'|E
//           F->(E)|i

// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// char inp[50];
// int E(int);
// int E_(int);
// int T(int);
// int T_(int);
// int F(int);
// void error()
// {
//     printf("Error in parsing ");
//     exit(0);
// }

// int E(int index)
// {
//     index=T(index);
//     index=E_(index);
//     return index;
// }

// int E_(int index)
// {
//     if(inp[index]=='+')
//     {
//         index=T(++index);
//         index=E_(index);
//     }
//     return index;
// } 

// int T(int index)
// {
//     index=F(index);
//     index=T_(index);
//     return index;
// }

// int T_(int index)
// {
//     if(inp[index]=='*')
//     {
//         index=F(++index);
//         index=T_(index);
//     }
//     return index;
// }

// int F(int index)
// {
//     //F->(E)
//     if(inp[index]=='(')
//     {   
//         index=E(++index); 
//         if(inp[index]==')')
//             return ++index;
//     }

//     //F->id
//     if(inp[index]=='i')
//         return ++index;

//     error();
// }

// void main()
// {
//     //printf("Grammar\nS-> cAd\nA-> ab|a");
//     printf("\nEnter input for the grammar: ");
//     scanf("%s",inp);
//     int len=strlen(inp);

//     int ans=E(0);
//     printf("\n%d %d\n",len,ans);

//     if(ans==len)
//         printf("Valid syntax for grammar");
//     else
//         error();
// }

//Construct a recursive descent parser for an expression
//Grammar:  S-> cAd
//          A-> ab|a    




// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// char inp[50];

// void error()
// {
//     printf("Invalid syntax");
//     exit(0);
// }

// int A(int index)
// {   
//     int temp=index;

//     ab://A-> ab
//     index=temp;
//     if(inp[index]=='a')
//         ++index;
//     else 
//         goto a;
//     if(inp[index]=='b')
//         return ++index;
//     else goto a;

//     a://A->a
//     index=temp;
//     if(inp[index]=='a')
//         return ++index;

//     error(); 
// }

// int S(int index)
// {
//     if(inp[index]=='c')
//         ++index;
//     else
//         error();
//     index=A(index);
//     if(inp[index]=='d')
//         ++index;
//     else
//         error();
//     return index;
// }

// void main()
// {
//     printf("Grammar\nS-> cAd\nA-> ab|a");
//     printf("\nEnter input for the grammar: ");
//     scanf("%s",inp);
//     int ans=S(0);
//     int len=strlen(inp);
//     if(ans==len)
//         printf("Valid syntax for grammar");
//     else
//         error();
// }