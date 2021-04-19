#include "tacs.h"


TAC * makeIfThen(TAC*code0, TAC*code1); 
TAC*makeBinary(int type, TAC*code[]); 
TAC*makeUnary (int type, TAC*code[]); 

// IMPLEMENTATION

TAC* tacCreate (int type, HASH_NODE*res, HASH_NODE*op1, HASH_NODE*op2)
{
    TAC* newtac =0; 
    newtac = (TAC*)calloc (1,sizeof(TAC)); 
    newtac -> type = type; 
    newtac->res=res; 
    newtac->op1 = op1; 
    newtac->op2 =op2; 
    newtac->prev =0; 
    newtac -> next =0; 
    return newtac; 
}

void tacPrint (TAC* tac)
{
    if (!tac)
    return; 
    if (tac->type == TAC_SYMBOL) return;

    fprintf(stderr, "TAC (");

    switch (tac->type)
    {
        case TAC_SYMBOL: 
        fprintf(stderr, "TAC_SYMBOL");
        break; 
        case TAC_ADD: 
        fprintf(stderr, "TAC_ADD");
        break; 
        case TAC_SUB: 
        fprintf(stderr, "TAC_SUB");
        break; 
        case TAC_MULT: 
        fprintf(stderr, "TAC_MULT");
        break; 
        case TAC_DIV: 
        fprintf(stderr, "TAC_DIV");
        break; 
        case TAC_MINOR: 
        fprintf(stderr, "TAC_MINOR");
        break; 
            case TAC_BIGGER: 
        fprintf(stderr, "TAC_BIGGER");
        break;
        case TAC_OR: 
        fprintf(stderr, "TAC_OR");
        break; 
        case TAC_AND: 
        fprintf(stderr, "TAC_AND");
        break; 
        case TAC_LE: 
        fprintf(stderr, "TAC_LE");
        break; 
        case TAC_GE: 
        fprintf(stderr, "TAC_GE");
        break; 

        case TAC_EQ: 
        fprintf(stderr, "TAC_EQ");
        break;
        case TAC_DIF: 
        fprintf(stderr, "TAC_DIF");
        break;
        case TAC_NOT: 
        fprintf(stderr, "TAC_NOT");
        break;
        case TAC_DOLLAR: 
        fprintf(stderr, "TAC_DOLLAR");
        break;
        case TAC_TAG: 
        fprintf(stderr, "TAC_TAG");
        break;

        case TAC_COPY: 
        fprintf(stderr, "TAC_COPY");
        break; 
        case TAC_JFALSE: 
        fprintf(stderr, "TAC_JFALSE");
        break;
        case TAC_LABEL: 
        fprintf(stderr, "TAC_LABEL");
        break; 
        default: 
        fprintf(stderr, "TAC_UNKNOWN");
        break; 
    }
 //if (tac->res)
    fprintf (stderr, ", %s", (tac->res)?tac->res->text: "0");
    fprintf (stderr, ", %s", (tac->op1)?tac->op1->text: "0");
    fprintf (stderr, ", %s", (tac->op2)?tac->op2->text: "0");

    fprintf (stderr, ");\n");
   
 }

 void tacPrintBackwards (TAC *tac){

    if (!tac) 
    return; 
 else{
    tacPrintBackwards(tac->prev);
    tacPrint (tac); 
}
}

TAC* tacJoin (TAC *l1, TAC*l2)
{
TAC * point;

    if (!l1) return l2;
    if(!l2) return l1; 
    for (point =l2; point->prev != 0; point=point->prev)
    ;
        point->prev = l1; 
        return l2; 
    


}


TAC* generateCode(AST*node)
{
int i; 
TAC * result = 0; 
TAC * code [MAX_SONS]; 

if (!node) return 0;

//PROCESS CHILDREN
for (i=0; i<MAX_SONS; ++i)
code[i] = generateCode(node->son[i]);


//PROCESS THIS NODE
switch(node->type)
{
    case AST_SYMBOL: 
    result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); 
    break;
    case AST_ADD: 
    result = makeBinary(TAC_ADD, code); 
    break; 
    case AST_SUB: 
    result = makeBinary(TAC_SUB, code); 
    break;
    case AST_DIV: 
    result = makeBinary(TAC_DIV, code); 
    break;

    case AST_MULT: 
    result = makeBinary(TAC_MULT, code); 
    break;
    case AST_MINOR:
    result = makeBinary(TAC_MINOR, code); 
    break; 
    case AST_BIGGER: 
    result = makeBinary(TAC_BIGGER, code); 
    break; 
    case AST_OR: 
    result = makeBinary(TAC_OR, code); 
    break; 
    case AST_AND: 
    result = makeBinary(TAC_AND, code); 
    break; 
    case AST_LE: 
    result = makeBinary(TAC_LE, code); 
    break; 
    case AST_GE: 
    result = makeBinary(TAC_GE, code); 
    break; 
    case AST_EQ: 
    result = makeBinary(TAC_EQ, code); 
    break; 
    case AST_DIF: 
    result = makeBinary(TAC_DIF, code); 
    break; 
    case AST_NOT: 
    result = makeUnary(TAC_NOT,code); 
    break;
    case AST_DOLLAR: 
    result = makeUnary(TAC_DOLLAR,code); 
    break;
    case AST_TAG: 
    result = makeUnary(TAC_TAG,code); 
    break;
    case AST_LEFT_ASSGN: 
    result = tacJoin(code[0], tacCreate(TAC_COPY, node->symbol, code[0]?code[0]->res:0, 0)); 
    break;
    case AST_IF:
     result = makeIfThen(code[0], code[1]);
     break;
    default: //return the union of code for all subtrees 
    result = tacJoin (code[0], tacJoin(code[1], tacJoin(code[2], code[3]))); 
    break; 
   
}

return result; 
}

TAC*makeBinary (int type, TAC*code[]){
    return tacJoin(tacJoin(code[0], code[1]), tacCreate(type, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); 
}

TAC*makeUnary(int type, TAC*code[]){
 return tacJoin(code[0], tacCreate(type, makeTemp(), code[0]?code[0]->res:0,0));
}


TAC * makeIfThen(TAC*code0, TAC*code1){
    TAC* jumptac =0; 
    TAC* labeltac=0; 
    HASH_NODE* newlabel =0;

    newlabel = makeLabel(); 

    jumptac = tacCreate(TAC_JFALSE, newlabel, code0?code0->res:0, 0); 
    jumptac->prev = code0;
    labeltac = tacCreate(TAC_LABEL, newlabel, 0, 0); 
    labeltac->prev = code1; 

    return tacJoin(jumptac, labeltac); 
}