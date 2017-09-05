%{
    #include<stdio.h>
	#include "y.tab.h"
	void yyerror();
    
	struct tree
	{
  		char ntype;
  		struct tree *left,*right;
	};
	


	struct tree *root;
    	
	struct tree * starttree (char ntype,struct tree* left,struct tree* right);

	void printInorder(struct tree* node);

	void printpostorder(struct tree* root);

	void printpreorder(struct tree* root);

%}

%union {
   struct tree* ast;
   int num;
}

%start line

%token <num> INT

%type <ast> E

%left '+' 
%left '*'


%%

line : E {
			root=$1;
         }
     ;
E    : E '+' E {$$ = starttree ('+', $1, $3); }
	 | E '*' E {$$ = starttree ('*', $1, $3); }
	 | INT { $$ = starttree ('I',NULL,NULL); }
	 ;
	 
%%


struct tree* starttree (char ntype, struct tree* left, struct tree* right)
{
	struct tree* tree = malloc (sizeof (struct tree));
	tree->ntype=ntype;
	tree->left = left;
	tree->right = right;
	return tree;
}




void printInorder(struct tree* root)
{
    if(root!=NULL)
	{
		printInorder(root->left);
		printf("%c ",root->ntype);	
		printInorder(root->right);
	}
}

void printpreorder(struct tree* root)
{
    if(root!=NULL)
	{
		printf("%c ",root->ntype);		
		printpreorder(root->left);
		printpreorder(root->right);
	}
}


void printpostorder(struct tree* root)
{
    if(root!=NULL)
	{
		printpostorder(root->left);
		printpostorder(root->right);
		printf("%c ",root->ntype);	
	}
}


void yyerror()
{
   printf("\nEntered arithmetic expression is valid\n\n");
  
}



void main()
{ 
   printf("\nEnter Any valid Arithmetic Expression \n");
   yyparse();

   printf("\nINorder traversal of tree is \n");
    printInorder(root); 

	printf("\nPREorder traversal of tree is \n");
    printpreorder(root); 


	printf("\nPOSTorder traversal of tree is \n");
    printpostorder(root); 
}