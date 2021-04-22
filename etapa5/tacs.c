#include "tacs.h"


TAC * makeIfThen(TAC*code0, TAC*code1); 
TAC*makeBinary(int type, TAC*code[]); 
TAC*makeUnary (int type, TAC*code[]); 
TAC*makeIfThenElse (TAC*code[]);
TAC*makeWhile(TAC* code[]);
TAC* generatePrint(TAC* code0, TAC* code1);

// IMPLEMENTATION

TAC* tacCreate (int type, HASH_NODE*res, HASH_NODE*op1, HASH_NODE*op2){
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

void tacPrint (TAC* tac){
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
        case TAC_LEFT:
        fprintf(stderr, "TAC_LEFT"); 
        break;
        case TAC_RIGHT:
        fprintf(stderr, "TAC_RIGHT"); 
        break;

        case TAC_IFZ: 
        fprintf (stderr, "TAC_IFZ"); 
        break; 

        case TAC_JUMP: 
        fprintf (stderr, "TAC_JUMP"); 
        break; 
        case TAC_CALL: 
        fprintf (stderr, "TAC_CALL"); 
        break; 
        case TAC_ARG: 
        fprintf(stderr, "TAC_ARG");
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
        case TAC_VEC_COPY: 
        fprintf(stderr, "TAC_VEC_COPY");
        break; 
        
        case TAC_FUNCT: 
        fprintf(stderr, "TAC_FUNCT");
        break; 
        case TAC_BEGIN_FUNCTION: 
        fprintf(stderr, "TAC_BEGIN_FUNCTION");
        break;
        case TAC_END_FUNCTION: 
        fprintf(stderr, "TAC_END_FUNCTION");
        break;
        case TAC_READ: 
        fprintf(stderr, "TAC_READ"); 
        break;
        case TAC_RETURN: 
        fprintf(stderr, "TAC_RETURN"); 
        break;
        
        case TAC_PRINT: 
        fprintf(stderr, "TAC_PRINT"); 
        break;
        case TAC_ELEM_COPY: 
        fprintf(stderr, "TAC_ELEM_COPY");
        break; 
        case TAC_JFALSE: 
        fprintf(stderr, "TAC_JFALSE");
        break;
        case TAC_LABEL: 
        fprintf(stderr, "TAC_LABEL");
        break; 
        case TAC_LEFT_VEC:
        fprintf (stderr, "TAC_LEFT_VEC");
        break;
        case TAC_RIGHT_VEC:
        fprintf(stderr, "TAC_RIGHT_VEC"); 
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

TAC* tacJoin (TAC *l1, TAC*l2){
    TAC * point;

    if (!l1) return l2;
    if(!l2) return l1; 
    for (point =l2; point->prev != 0; point=point->prev)
    ;
        point->prev = l1; 
        return l2; 
    


}


TAC* generateCode(AST*node){
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
    //Declaração de variável
    if (node->son[0]!=0)
    result = tacJoin(code[0], tacCreate(TAC_COPY, node->symbol, code[0]?code[0]->res:0, 0)); 
    break;

    //Binary
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
    //unary
    case AST_NOT: 
    result = makeUnary(TAC_NOT,code); 
    break;
    case AST_DOLLAR: 
    result = makeUnary(TAC_DOLLAR,code); 
    break;
    case AST_TAG: 
    result = makeUnary(TAC_TAG,code); 
    break;

    //attribution 
    case AST_LEFT_ASSGN: 
    result = tacJoin(code[0], tacCreate(TAC_LEFT, node->symbol, code[0]?code[0]->res:0, 0)); 
    break;
    case AST_RIGHT_ASSGN: 
    result = tacJoin(code[0], tacCreate(TAC_RIGHT, node->symbol, code[0]?code[0]->res:0, 0)); 
    break;
    case AST_LEFT_ASSGN_V: 
    result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_LEFT_VEC, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0)));
    break; 
    case AST_RIGHT_ASSGN_V:
    result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_RIGHT_VEC, node->symbol, code[1]?code[1]->res:0, code[0]?code[0]->res:0)));
    break;
   
    //function declaration
    case AST_DEC_FUNCT: 
    result = tacJoin(tacJoin(tacJoin(code[1],tacJoin(code[0],tacCreate(TAC_BEGIN_FUNCTION, tacCreate(TAC_SYMBOL, node->symbol, 0, 0)->res, code[1]?code[1]->res:0, 0))), code[2]), tacCreate(TAC_END_FUNCTION, tacCreate(TAC_SYMBOL, node->symbol, 0, 0)->res, 0, 0));
    break;
    case AST_PARAMETER: 
     result = tacJoin(code[1],(tacCreate(TAC_ARG, makeTemp(), node->symbol, code[1]?code[1]->res:0)));
    break; 

    //call function
    case AST_CALL_FUNCT:
    result = tacJoin( code[0], tacCreate(TAC_CALL,node->symbol, code[0]?code[0]->res:0,0));
    break;
    case AST_LARG: 
    result= tacJoin(tacJoin(code[0],code[1]), tacCreate(TAC_ARG,  makeTemp(),code[0] ? code[0]->res : 0,  code[1] ? code[1]->res : 0));
    break; 
    
    //vector declaration 
    case AST_DEC_VECTOR: 
    result = tacJoin(code[2],tacJoin(code[1],tacCreate(TAC_VEC_COPY, node->symbol, code[1] ? code[1]->res : 0, code[2] ? code[2]->res : 0)));
    break;
    case AST_VECT_VL: 
    result= tacJoin (tacJoin(code[0], code[1]),tacCreate(TAC_ELEM_COPY,  makeTemp(),code[0] ? code[0]->res : 0,  code[1]?code[1]->res:0));
    break;
    case AST_VECTOR: 
    result =  tacJoin(code[0], tacCreate(TAC_VEC_COPY, makeTemp(), node->symbol, code[0]?code[0]->res:0));
    break; 

    //read and return 
    case AST_READ: 
    result = tacCreate(TAC_READ, node->symbol, 0, 0); 
    break; 
    case AST_RETURN: 
    result = makeUnary(TAC_RETURN, code); 
    break;
   
   //print
    case AST_PRINT: 
    result = code[0];
    break;
    case AST_STRING:
    case AST_LPRNT:
    result =  tacJoin(tacJoin(code[0], code[1]),tacCreate(TAC_PRINT,node->symbol, code[0] ? code[0]->res : 0, 0)); 
    break;
    
    //conditions
    case AST_WHILE: 
    result = makeWhile(code); 
    break; 
    case AST_IF:
     result = makeIfThen(code[0], code[1]);
     break;
    case AST_IF_ELSE: 
    result =  makeIfThenElse (code); 
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

TAC * makeIfThenElse (TAC * code[]){
 TAC* jumpIfZTAC = 0;
    TAC* jumpTAC = 0;

    TAC* labelElseTAC = 0;
    TAC* labelEndElseTAC = 0;
    
    HASH_NODE* labelElse = 0;
    HASH_NODE* labelEndElse = 0;

    labelElse = makeLabel();
    labelEndElse = makeLabel();

    jumpIfZTAC = tacCreate(TAC_IFZ, labelElse, code[0] ? code[0]->res : 0, 0);
    jumpIfZTAC->prev = code[0];

    jumpTAC = tacCreate(TAC_JUMP, labelEndElse, 0, 0);
    jumpTAC->prev = code[1];

    labelElseTAC = tacCreate(TAC_LABEL, labelElse, 0, 0);
    labelElseTAC->prev = jumpTAC;

    labelEndElseTAC = tacCreate(TAC_LABEL,labelEndElse, 0, 0);
    labelEndElseTAC->prev = code[2];

    tacJoin(jumpIfZTAC, jumpTAC);

    return tacJoin(labelElseTAC, labelEndElseTAC);
}
TAC* makeWhile(TAC* code[]) {
    HASH_NODE* labelStartWhile = makeLabel();
    HASH_NODE* labelEndWhile = makeLabel();

    TAC* tacWhileStartLabel = tacCreate(TAC_LABEL, labelStartWhile, 0, 0);
    TAC* tacEndWhile = tacCreate(TAC_IFZ, labelEndWhile, code[0]?code[0]->res:0, 0);
    TAC* tacRestart = tacCreate(TAC_JUMP, labelStartWhile, 0, 0);
    TAC* tacEndLabel = tacCreate(TAC_LABEL, labelEndWhile, 0, 0);

    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacWhileStartLabel, code[0]), tacEndWhile), code[1]), tacRestart), tacEndLabel);
}

TAC* generatePrint(TAC* code0, TAC* code1) {
	TAC* printTac0 = 0;
	TAC* printTac1 = 0;
	printTac0 = tacCreate(TAC_PRINT, code0? code0->res : 0, 0, 0);
	printTac0->prev = code0;
	if(code1->type != TAC_PRINT) {
		printTac1 = tacCreate(TAC_PRINT, code1? code1->res : 0, 0, 0);
		printTac1->prev = code1;
		return tacJoin(printTac0, printTac1);
	}
	else {
		return tacJoin(printTac0, code1);
	}
}