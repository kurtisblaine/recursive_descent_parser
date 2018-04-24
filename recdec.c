#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

void program();
void block();
void stmtlist();
void stmt(); 
void morestmts();
void stmtlist();
void assign();
int variable();
void expr();
void ifstmt();
void whilestmt();
void testexpr();
void testexpr();
int variable();
int digit();
void error(int t);
void match();

char input[1000];
char lookahead;
int assignn;
int reference; 
int loop;
int conditional; 
int i;
bool build = true;

int main(){
	assignn = 0;
	reference = 0;
	conditional = 0;
	loop = 0;

	program();

	if(build == true){
		printf("\nbuild success!\n");
		printf("\n*************** parse statistics *****************\n");
		printf("\t%d ::: assignment statements\n", assignn);
		printf("\t%d ::: variable references\n", reference);
		printf("\t%d ::: loop statements\n", loop);
		printf("\t%d ::: conditional statements\n\n", conditional);
	}
	else  printf("build failed...\n");
	return 0;
}

void program(){
	match();
	if (strcmp(input, "program") == 0){ match(); block(); match(); 
		if (strcmp(input, ".") != 0) error(11);
	}
	else error(11);
}

void block(){
	if(strcmp(input, "begin") == 0){
		stmtlist();
		if(strcmp(input, "end") != 0) error(1);
	}
	else error(1);
}

void stmtlist(){
	stmt();
	morestmts();
}

void stmt(){
	match();
	if (variable()) assign();
	else if(strcmp(input, "if") == 0) ifstmt();
	else if(strcmp(input, "while") == 0) whilestmt();
	else if(strcmp(input, "begin") == 0) block();
	else error(10);
}

void morestmts(){
	match();
	if(strcmp(input, ";") == 0) stmtlist();
	
}

void assign(){
	match();
	if(strcmp(input, "=") == 0){ assignn++; expr(); }
	else error(3);  
}

void ifstmt(){
	testexpr();
	match();
	if(strcmp(input, "then") == 0){ stmt(); match(); conditional++;
		if(strcmp(input, "else") == 0) stmt();
	}
	else error(4);
}

void whilestmt(){
	loop++;
	testexpr();
	match();
	if(strcmp(input, "do") == 0) stmt();
	else error(5);
}

void testexpr(){
	match();
	if( variable() ){ 
		match();
		if(strcmp(input, "<=") == 0) expr();
		else error(6);
	}
	else error(6);
}

void expr(){
	match();
	if(strcmp(input, "+") == 0){ expr(); expr();}
	else if(strcmp(input, "*") == 0){ expr(); expr();}
	else if(variable());
	else if(digit());
	else error (9);
}

int variable(){
	if(strcmp(input, "a") == 0){ reference++; return 1; }
	else if(strcmp(input, "b") == 0){ reference++; return 1; }
	else if(strcmp(input, "c") == 0){ reference++ ; return 1; }
	else { return 0; }
}

int digit(){
	if(strcmp(input, "0") == 0) return 1;
	else if(strcmp(input, "1") == 0) return 1;
	else if(strcmp(input, "2") == 0) return 1;
	else{ return 0; }
}

void error(int t){
	build = false;
	switch(t){
		case 1: printf("block parse error:::\n"); break;
		case 2: printf("morestmts parse error:::\n"); break;
		case 3: printf("assign parse error:::\n"); break;
		case 4: printf("ifstmt parse error:::\n"); break;
		case 5: printf("whilestmt parse error:::\n"); break;
		case 6: printf("testexpr parse error:::\n"); break;
		case 7: printf("variable parse error:::\n"); break;
		case 8: printf("digit parse error:::\n"); break;
		case 9: printf("expr parse error:::\n"); break;
		case 10: printf("stmt parse error:::\n"); break;
		case 11: printf("program parse error:::\n"); break;
	}
}

void match(){
	char nextchar;

	if(lookahead == ';' || lookahead == '.'){ nextchar = lookahead; lookahead = '0';}
	else nextchar = getchar();


	if(nextchar == ';' || nextchar == '.'){ 
		memset(input, 0, sizeof(input)); 
		input[0] = nextchar;
	}
	else if(nextchar == '<' ){
		 memset(input, 0, sizeof(input));
		 input[0] = nextchar;
		 nextchar = getchar();
		 if(nextchar == '=') input[1] = nextchar;
		 else error(3);
	}
	else if(nextchar == '='){
		memset(input, 0, sizeof(input)); 
		input[0] = nextchar;
	}
	else if(nextchar == '+'){
		memset(input, 0, sizeof(input)); 
		input[0] = nextchar;
	}
	else if(nextchar == '*'){
		memset(input, 0, sizeof(input)); 
		input[0] = nextchar;
	}
	else if(nextchar == '0'){
		memset(input, 0, sizeof(input)); 
		input[0] = nextchar;
	}
	else if(nextchar == '1'){
		memset(input, 0, sizeof(input)); 
		input[0] = nextchar;
	}
	else if(nextchar == '2'){
		memset(input, 0, sizeof(input)); 
		input[0] = nextchar;
	}
	else if(isalpha(nextchar)){
	//while the next character is alphabetical then consume them
		i = 0;
		memset(input, 0, sizeof(input));
		while(isalpha(nextchar)){
			input[i] = nextchar;
			i++;
			nextchar = getchar();
		}
		if (nextchar == '.' || nextchar == ';' || nextchar == '=' || nextchar == '<') lookahead = nextchar;
	}
	else {         //ignore whitespace
		if(isspace(nextchar)) match(); 
	}
	
}


