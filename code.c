#include <stdio.h>
#include <string.h>

int n;

char prods[50][50];
char firsts[26][50];
int is_first_done[26];
char follows[26][50];
int is_follow_done[26];

int isTerminal(char c)
{
    if (c < 65 || c > 90)
        return 1;
    return 0;
}
void first(char nonterm)
{
    int index = 0;
    char curr_firsts[50];
    for (int i = 0; i < n; i++)
    {
        if (prods[i][0] == nonterm)
        {
            int curr_prod_index = 2;
            int flag = 0;
            while (prods[i][curr_prod_index] != '\0' && flag == 0)
            {
                flag = 1;
                if (isTerminal(prods[i][curr_prod_index]))
                {
                    curr_firsts[index] = prods[i][2];
                    index++;
                    break;
                }
                if (!is_first_done[prods[i][curr_prod_index] - 65])
                    first(prods[i][curr_prod_index]);
                int in = 0;
                while (firsts[prods[i][curr_prod_index] - 65][in] != '\0')
                {
                    curr_firsts[index] = firsts[prods[i][curr_prod_index] - 65][in];
                    if (firsts[prods[i][curr_prod_index] - 65][in] == 'e')
                    {
                        curr_prod_index++;
                        flag = 0;
                    }
                    index++;
                    in++;
                }
            }
        }
    }
    curr_firsts[index] = '\0';
    index++;
    strcpy(firsts[nonterm - 65], curr_firsts);
    is_first_done[nonterm - 65] = 1;
}
void follow(char nonterm)
{
    int index = 0;
    char curr_follows[50];
    if (nonterm == prods[0][0])
    {
        curr_follows[index] = '$';
        index++;
    }
    for (int j = 0; j < n; j++)
    {
        int k = 2;
        int include_lhs_flag;
        while (prods[j][k] != '\0')
        {
            include_lhs_flag = 0;
            if (prods[j][k] == nonterm)
            {
                if (prods[j][k + 1] != '\0')
                {
                    if (isTerminal(prods[j][k + 1]))
                    {
                        curr_follows[index] = prods[j][k + 1];
                        index++;
                        break;
                    }
                    int in = 0;
                    while (firsts[prods[j][k + 1] - 65][in] != '\0')
                    {
                        if (firsts[prods[j][k + 1] - 65][in] == 'e')
                        {
                            include_lhs_flag = 1;
                            in++;
                            continue;
                        }
                        int temp_flag = 0;
                        for (int z = 0; z < index; z++)
                            if (firsts[prods[j][k + 1] - 65][in] == curr_follows[z])
                            {
                                temp_flag = 1;
                                in++;
                                break;
                            }
                        if (temp_flag)
                            continue;
                        curr_follows[index] = firsts[prods[j][k + 1] - 65][in];
                        index++;
                        in++;
                    }
                }
                if (prods[j][k + 1] == '\0' || include_lhs_flag == 1)
                {
                    if (prods[j][0] != nonterm)
                    {
                        if (!is_follow_done[prods[j][0] - 65])
                            follow(prods[j][0]);
                        int x = 0;
                        while (follows[prods[j][0] - 65][x] != '\0')
                        {
                            int temp_flag = 0;
                            for (int z = 0; z < index; z++)
                                if (follows[prods[j][0] - 65][x] == curr_follows[z])
                                {
                                    temp_flag = 1;
                                    x++;
                                    break;
                                }
                            if (temp_flag)
                                continue;
                            curr_follows[index] = follows[prods[j][0] - 65][x];
                            index++;
                            x++;
                        }
                    }
                }
            }
            k++;
        }
    }
    curr_follows[index] = '\0';
    index++;
    strcpy(follows[nonterm - 65], curr_follows);
    is_follow_done[nonterm - 65] = 1;
}
int main()
{
    printf("Enter the number of productions: ");
    scanf("%d", &n);
    printf("Enter the productions: \n");
    for (int i = 0; i < n; i++)
        scanf("%s", prods[i]);
    for (int i = 0; i < 26; i++)
        is_first_done[i] = 0;
    for (int i = 0; i < n; i++)
        if (is_first_done[prods[i][0] - 65] == 0)
            first(prods[i][0]);
    for (int i = 0; i < n; i++)
        if (is_follow_done[prods[i][0] - 65] == 0)
            follow(prods[i][0]);
    printf("Firsts:\n");
    for (int i = 0; i < 26; i++)
        if (is_first_done[i])
            printf("%c : %s\n", i + 65, firsts[i]);
    printf("Follows:\n");
    for (int i = 0; i < 26; i++)
        if (is_follow_done[i])
            printf("%c : %s\n", i + 65, follows[i]);
}



#include <stdio.h>
#include <string.h>

void main() {
    char stack[20], ip[20], opt[10][10][1], ter[10];
    int i, j, k, n, top = 0, col, row;

    for (i = 0; i < 10; i++) {
        stack[i] = 0;
        ip[i] = 0;
        for (j = 0; j < 10; j++) {
            opt[i][j][1] = 0;
        }
    }

    printf("Enter the number of terminals: ");
    scanf("%d", &n);

    printf("\nEnter the terminals: ");
    scanf("%s", ter);

    printf("\nEnter the table values:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter the value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n");
    for (i = 0; i < n; i++) {
        printf("\t%c", ter[i]);
    }

    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%c", ter[i]);
        for (j = 0; j < n; j++) {
            printf("\t%c", opt[i][j][0]);
        }
        printf("\n");
    }

    stack[top] = '$';

    printf("\nEnter the input string: ");
    scanf("%s", ip);

    i = 0;
    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
    printf("\n%s\t\t\t%s\t\t\t", stack, ip);

    while (i <= strlen(ip)) {
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k]) {
                col = k;
            }
            if (ip[i] == ter[k]) {
                row = k;
            }
        }

        if ((stack[top] == '$') && (ip[i] == '$')) {
            printf("String is accepted\n");
            break;
        } else if ((opt[col][row][0] == '<') || (opt[col][row][0] == '=')) {
            stack[++top] = opt[col][row][0];
            stack[++top] = ip[i];
            printf("Shift %c", ip[i]);
            i++;
        } else {
            if (opt[col][row][0] == '>') {
                while (stack[top] != '<') {
                    --top;
                }
                top = top - 1;
                printf("Reduce");
            } else {
                printf("\nString is not accepted");
                break;
            }
        }

        printf("\n");
        for (k = 0; k <= top; k++) {
            printf("%c", stack[k]);
        }
        printf("\t\t\t");
        for (k = i; k < strlen(ip); k++) {
            printf("%c", ip[k]);
        }
        printf("\t\t\t");
    }
}


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

//shift
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char input[100];
char stack[100];
int top=0;
int len=0;

void print_details(int,char[]);
void checkForReduction(int);
void main()
{ int i=0;
  printf("Enter the string to be reduced\n");
  scanf("%s",input);
  len=strlen(input);
  printf("Stack\t\tInput\t\tAction\n");
  for(i=0;i<len;i++)
    {
      print_details(i,"Shift");
      stack[top]=input[i];
      checkForReduction(i);
      top++;
    }
  top--;
  if(top==0 && stack[0]=='S')
  {
    printf("String is accepted\n");
  }
 else{
   printf("String regected\n");
 }
  
}
void checkForReduction(int i)
{
  int flag=1;
  while(flag)
    {
      flag=0;
      if(top >= 2 && stack[top-2]=='S' && stack[top-1]=='+' && stack[top]=='S')
      {
        print_details(i+1,"Reduced");
        stack[top-2]='S';
        top=top-2;
        flag=1;
      }
      else if( top >= 2 && stack[top-2]=='S' && stack[top-1]=='-' && stack[top]=='S')
      {
        print_details(i+1,"Reduced");
        stack[top-2]='S';
        top=top-2;
        flag=1;
      }
      else if(top >= 2 && stack[top-2]=='(' && stack[top-1]=='S' && stack[top]==')')
      {
        print_details(i+1,"Reduced");
        stack[top-2]='S';
        top=top-2;
        flag=1;
        
      }
      else if(stack[top]=='i'){
        print_details(i+1,"Reduce");
        stack[top]='S';
        flag=1;
      }
      
    }
  
}

void print_details(int i,char action[])
{
  for(int j=0;j<=top;j++)
    {
      printf("%c",stack[j]);
    }
  printf("\t\t");
  for(int k=i;k<len;k++)
    {
      printf("%c",input[k]);
    
    }
  printf("\t\t");
  printf("%s",action);
  printf("\n");
}

//dfa min
//Tom George
//Reg No: MDL20CS118
//C7B, Roll No:59
//Program to minimize the DFA

#include <stdio.h>
#include <stdlib.h>

static int ns, na, s, nt, nf, start, finalstate[20], r;
char alphabet[20];
int transition_map[30][30], table[30][30], nonfinalstate[20], partition[20][20];

int findalpha(char a)
{
    int i;
    for (i = 0; i < na; i++)
        if (alphabet[i] == a)
            return i;
    return (-1);
}

int main()
{
    int i, j, p[20], q[20], k;
    char a;
    for (i = 0; i < 30; i++)
    {
        for (j = 0; j < 30; j++)
            transition_map[i][j] = -1;
    }
    printf("Tom George\n");
    printf("\n---------------------------------\n");
    printf("Enter the number of alphabets: ");
    scanf("%d", &na);
    getchar();
    printf("Enter the alphabets: ");
    for (i = 0; i < na; i++)
    {
        alphabet[i] = getchar();
        getchar();
    }
    printf("Enter the number of states: ");
    scanf("%d", &ns);
    printf("Enter the start state: ");
    scanf("%d", &start);
    printf("Enter the number of final states: ");
    scanf("%d", &nf);
    printf("Enter the final state(s): ");
    for (i = 0; i < nf; i++)
        scanf("%d", &finalstate[i]);
    printf("Enter no of transition: ");
    scanf("%d", &nt);
    printf("Enter Transition in the form -> state alphabet next_state\n");
    for (i = 0; i < nt; i++)
    {
        scanf("%d %c %d", &r, &a, &s);
        j = findalpha(a);
        if (j == -1)
        {
            printf("\nerror\n");
            exit(1);
        }
        transition_map[r][j] = s;
    }
    for (i = 0; i < ns; i++)
    {
        for (j = 0; j < i; j++)
        {
            table[i][j] = 0;
        }
    }
    int f = 0;
    k = 0;
    for (i = 0; i < ns; i++)
    {
        f = 0;
        for (j = 0; j < nf; j++)
        {
            if (i == finalstate[j])
            {
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            nonfinalstate[k++] = i;
        }
    }
    for (i = 0; i < nf; i++)
    {
        for (j = 0; j < (ns - nf); j++)
            if (nonfinalstate[j] > finalstate[i])
                table[nonfinalstate[j]][finalstate[i]] = 1;
            else
                table[finalstate[i]][nonfinalstate[j]] = 1;
    }
    int change = 1;
    while (change == 1)
    {
        change = 0;
        for (i = 0; i < ns; i++)
        {
            for (j = 0; j < i; j++)
            {
                if (table[i][j] != 1)
                {
                    for (k = 0; k < na; k++)
                        p[k] = transition_map[i][k];
                    for (k = 0; k < na; k++)
                        q[k] = transition_map[j][k];
                    for (k = 0; k < na; k++)
                    {
                        if (p[k] > q[k])
                        {
                            if (table[p[k]][q[k]] == 1)
                            {
                                change = 1;
                                table[i][j] = 1;
                                break;
                            }
                        }
                        else if (p[k] < q[k])
                        {
                            if (table[q[k]][p[k]] == 1)
                            {
                                change = 1;
                                table[i][j] = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    k = 0;
    for (i = 0; i < ns; i++)
    {
        k = 0;
        partition[i][k++] = i;
        for (j = 0; j < i; j++)
            if (table[i][j] == 0)
            {
                partition[i][k++] = j;
            }
        partition[i][k] = -1;
    }
    int newstate[20] = {0}, m;
    printf("\nStates in minimized DFA");
    printf("\n----------------------------\n");
    for (i = ns - 1; i >= 0; i--)
    {
        k = 0;
        if (newstate[i] == 0)
        {
            printf("{");
            while (partition[i][k] != -1)
            {
                if (newstate[partition[i][k]] == 0)
                {
                    newstate[partition[i][k]] = 1;
                    printf("q%d ", partition[i][k]);
                }
                k++;
            }
            printf("}\n");
        }
    }
    return 0;
}

//enfatonfa
//Tom Geroge cs7b
//Reg No: MDL20CS118
//C7B, Roll No:59
//Program to convert epsilon-NFA to NFA

#include <stdio.h>
#include <stdlib.h>
struct node {
    int st;
    struct node *link;
};

void findclosure(int, int);
void insert_trantbl(int, char, int);
int findalpha(char);
void findfinalstate(void);
void unionclosure(int);
void print_e_closure(int);

static int set[20], nostate, noalpha, s, notransition, nofinal, start,
    finalstate[20], c, r, buffer[20];
char alphabet[20];
static int e_closure[20][20] = {0};
struct node *transition[20][20] = {NULL};

void main() {
    int i, j, k, m, t, n;
    printf("Tom Geroge 59");
    printf("\n----------------------------------------------\n");
    struct node *temp;
    printf("Enter the number of alphabets:\n");
    scanf("%d", &noalpha);
    getchar();
    printf("NOTE:- [ use letter e as epsilon]\n");

    printf("NOTE:- [e must be last character ,if it is present]\n");

    printf("\nEnter alphabets:\n");
    for (i = 0; i < noalpha; i++) {

        alphabet[i] = getchar();
        getchar();
    }
    printf("Enter the number of states:\n");
    scanf("%d", &nostate);
    printf("Enter the start state:\n");
    scanf("%d", &start);
    printf("Enter the number of final states:\n");
    scanf("%d", &nofinal);
    printf("Enter the final states:\n");
    for (i = 0; i < nofinal; i++)
        scanf("%d", &finalstate[i]);
    printf("Enter no of transition:\n");
    scanf("%d", &notransition);
    printf("NOTE:- [Transition is in the form--> qno   alphabet   qno]\n",
           notransition);
    printf("NOTE:- [States number must be greater than zero]\n");
    printf("\nEnter transitions:\n");
    for (i = 0; i < notransition; i++) {

        scanf("%d %c %d", &r, &c, &s);
        insert_trantbl(r, c, s);
    }

    printf("\n");

    for (i = 1; i <= nostate; i++) {
        c = 0;
        for (j = 0; j < 20; j++)

        {
            buffer[j] = 0;
            e_closure[i][j] = 0;
        }
        findclosure(i, i);
    }
    printf("Equivalent NFA without epsilon\n");
    printf("-----------------------------------\n");
    printf("start state:");
    print_e_closure(start);
    printf("\nAlphabets:");
    for (i = 0; i < noalpha; i++)
        printf("%c ", alphabet[i]);
    printf("\nStates :");
    for (i = 1; i <= nostate; i++)
        print_e_closure(i);

    printf("\nTransitions are...:\n");

    for (i = 1; i <= nostate; i++) {

        for (j = 0; j < noalpha - 1; j++) {
            for (m = 1; m <= nostate; m++)
                set[m] = 0;
            for (k = 0; e_closure[i][k] != 0; k++) {

                t = e_closure[i][k];
                temp = transition[t][j];
                while (temp != NULL) {

                    unionclosure(temp->st);
                    temp = temp->link;
                }
            }
            printf("\n");
            printf("q%d",i);
            printf("%c\t", alphabet[j]);
            printf("{");
            for (n = 1; n <= nostate; n++) {
                if (set[n] != 0)
                    printf("q%d,", n);
            }
            printf("}");
        }
    }
    printf("\n Final states:");
    findfinalstate();
}

void findclosure(int x, int sta) {
    struct node *temp;
    int i;
    if (buffer[x])
        return;
    e_closure[sta][c++] = x;
    buffer[x] = 1;
    if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL) {
        temp = transition[x][noalpha - 1];
        while (temp != NULL) {
            findclosure(temp->st, sta);
            temp = temp->link;
        }
    }
}

void insert_trantbl(int r, char c, int s) {
    int j;
    struct node *temp;
    j = findalpha(c);
    if (j == 999) {
        printf("error\n");
        exit(0);
    }
    temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

int findalpha(char c) {
    int i;
    for (i = 0; i < noalpha; i++)
        if (alphabet[i] == c)
            return i;

    return (999);
}

void unionclosure(int i) {
    int j = 0, k;
    while (e_closure[i][j] != 0) {
        k = e_closure[i][j];
        set[k] = 1;
        j++;
    }
}
void findfinalstate() {
    int i, j, k, t;
    for (i = 0; i < nofinal; i++) {
        for (j = 1; j <= nostate; j++) {
            for (k = 0; e_closure[j][k] != 0; k++) {
                if (e_closure[j][k] == finalstate[i]) {

                    print_e_closure(j);
                }
            }
        }
    }
}

void print_e_closure(int i) {
    int j;
    printf("{");
    for (j = 0; e_closure[i][j] != 0; j++)
        printf("q%d,", e_closure[i][j]);
    printf("}\t");
}

//nfatodfa

// Code to convert from NFA to DFA
//Tom George
//Reg No: MDL20CS118
//C7B, Roll No:59
//Program to convert NFA to equivalent DFA

#include <stdio.h>
#include <stdlib.h>
struct node
{
    int st;
    struct node *link;
};
struct node1
{
    int nst[20];
};

void insert(int, char, int);
int findalpha(char);
void findfinalstate(void);
int insertdfastate(struct node1);
int compare(struct node1, struct node1);
void printnewstate(struct node1);

static int set[20], ns, na, s, nt, nf , start, finalstate[20], c, r, buffer[20];
int complete = -1;
char alphabet[20];
static int eclosure[20][20] = {0};
struct node1 hash[20];
struct node *transition[20][20] = {NULL};

void main()
{
    int i, j, k, m, t, n, l;
    struct node *temp;
    struct node1 newstate = {0}, tmpstate = {0};
    printf("Tom George MDL20CS118 Roll No:59");
    printf("\n---------------------------------------\n");
    printf("NOTE: Use letter e as epsilon\n");
    printf("NOTE: e must be last character ,if it is present\n");
    printf("\nEnter the number of alphabets and alphabets: ");
    scanf("%d", &na);
    getchar();
    for (i = 0; i < na; i++)
    {
        alphabet[i] = getchar();
        getchar();
    }
    printf("Enter the number of states: ");
    scanf("%d", &ns);
    printf("Enter the start state: ");
    scanf("%d", &start);
    printf("Enter the number of final states: ");
    scanf("%d", &nf);
    printf("Enter the final state(s): ");
    for (i = 0; i < nf; i++)
        scanf("%d", &finalstate[i]);
    printf("Enter no of transition: ");
    scanf("%d", &nt);
    printf("NOTE: Transition is in the form–> qno alphabet qno\n");
    printf("NOTE: States number must be greater than zero\n");
    printf("\nEnter the transition: \n");
    for (i = 0; i < nt ; i++)
    {
        scanf("%d %lc%d", &r, &c, &s);
        insert(r, c, s);
    }
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
            hash[i].nst[j] = 0;
    }
    complete = -1;
    i = -1;
    printf("\n....Equivalent DFA....\n");
    printf("......................\n");
    printf("Trnsitions of DFA:\n");
    newstate.nst[start] = start;
    insertdfastate(newstate);
    while (i != complete)
    {
        i++;
        newstate = hash[i];
        for (k = 0; k < na; k++)
        {
            c = 0;
            for (j = 1; j <= ns; j++)
                set[j] = 0;
            for (j = 1; j <= ns; j++)
            {
                l = newstate.nst[j];
                if (l != 0)
                {
                    temp = transition[l][k];
                    while (temp != NULL)
                    {
                        if (set[temp->st] == 0)
                        {
                            c++;
                            set[temp->st] = temp->st;
                        }
                        temp = temp->link;
                    }
                }
            }
            printf("\n");
            if (c != 0)
            {
                for (m = 1; m <= ns; m++)
                    tmpstate.nst[m] = set[m];
                insertdfastate(tmpstate);
                printnewstate(newstate);
                printf("%c\t", alphabet[k]);
                printnewstate(tmpstate);
                printf("\n");
            }
            else
            {
                printnewstate(newstate);
                printf("%c\t", alphabet[k]);
                printf("NULL\n");
            }
        }
    }
    printf("\nStates of DFA:\n");
    for (i = 0; i <= complete; i++)
        printnewstate(hash[i]);
    printf("\nAlphabets:\n");
    for (i = 0; i < na; i++)
        printf("%c\t", alphabet[i]);
    printf("\nStart State:\n");
    printf("q%d", start);
    printf("\nFinal states:\n");
    findfinalstate();
}

int insertdfastate(struct node1 newstate)
{
    int i;
    for (i = 0; i <= complete; i++)
    {
        if (compare(hash[i], newstate))
            return 0;
    }
    complete++;
    hash[complete] = newstate;
    return 1;
}

int compare(struct node1 a, struct node1 b)
{
    int i;
    for (i = 1; i <= ns; i++)
    {
        if (a.nst[i] != b.nst[i])
            return 0;
    }
    return 1;
}

void insert(int r, char c, int s)
{
    int j;
    struct node *temp;
    j = findalpha(c);
    if (j == 999)
    {

        printf("error\n");
        exit(0);
    }
    temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

int findalpha(char c)
{
    int i;
    for (i = 0; i < na; i++)
        if (alphabet[i] == c)
            return i;
    return (999);
}

void findfinalstate()
{
    int i, j, k, t;
    for (i = 0; i <= complete; i++)
    {
        for (j = 1; j <= ns; j++)
        {
            for (k = 0; k < nf ; k++)
            {
                if (hash[i].nst[j] == finalstate[k])
                {
                    printnewstate(hash[i]);
                    printf("\t");
                    j = ns;
                    break;
                }
            }
        }
    }
}
void printnewstate(struct node1 state)
{
    int j;
    printf("{");
    for (j = 1; j <= ns; j++)
    {
        if (state.nst[j] != 0)
            printf("q%d,", state.nst[j]);
    }
    printf("}\t");
}


