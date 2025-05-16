#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumerations for AST node types (some examples)
typedef enum {
    NODE_PROGRAM,
    NODE_BLOCK,
    NODE_VARDEF,
    NODE_VARDL,
    NODE_ASSIGN,
    NODE_IF,
    NODE_WHILE,
    NODE_PRINT,
    NODE_EXPR,
    NODE_TERM,
    NODE_FACTOR,
    NODE_CONST,
    NODE_ID,
    // ... others as needed
} NodeType;

// Forward declaration
typedef struct ASTNode ASTNode;

// AST Node structure
struct ASTNode {
    NodeType type;
    union {
        // For variable definitions
        struct {
            char **varNames;
            int *arraySizes;  // 0 if not an array
            int count;
        } varDef;

        // For assignment: left and right nodes
        struct {
            ASTNode *left;
            ASTNode *right;
            int isArray;   // 1 if left is an array element
            ASTNode *index; // expression for index if array
        } assignment;

        // For if statement
        struct {
            ASTNode *cond;
            ASTNode *thenPart;
            ASTNode *elsePart; // NULL if no else
        } ifStmt;

        // For while
        struct {
            ASTNode *cond;
            ASTNode *body;
        } whileStmt;

        // For print
        struct {
            ASTNode *expr;
        } printStmt;

        // For expressions: left op right, or single value
        struct {
            ASTNode *left;
            ASTNode *right;
            char op;  // '+', '-', '*', '/', '<', '>', etc.
        } expr;

        // For constants
        int intValue;

        // For identifiers
        char *idName;

    } data;

    ASTNode *next; // for linked lists like statement lists, var lists
};

// Global variable address mapping (simplified)
typedef struct VarEntry {
    char *name;
    int address;
    int size; // size > 1 for arrays
    struct VarEntry *next;
} VarEntry;

VarEntry *varTable = NULL;
int nextVarAddr = 0; // next available memory address

// Function to add variable to symbol table
void addVariable(char *name, int size) {
    VarEntry *v = malloc(sizeof(VarEntry));
    v->name = strdup(name);
    v->size = size;
    v->address = nextVarAddr;
    nextVarAddr += size;
    v->next = varTable;
    varTable = v;
}

// Lookup variable address
int getVarAddress(char *name) {
    VarEntry *cur = varTable;
    while(cur) {
        if(strcmp(cur->name, name) == 0) return cur->address;
        cur = cur->next;
    }
    printf("Error: Variable %s not found\n", name);
    exit(1);
}

// Code generation functions declarations
void genProgram(ASTNode *node);
void genBlock(ASTNode *node);
void genVarDef(ASTNode *node);
void genStmtList(ASTNode *node);
void genStatement(ASTNode *node);
void genAssignment(ASTNode *node);
void genIf(ASTNode *node);
void genWhile(ASTNode *node);
void genPrint(ASTNode *node);
void genExpr(ASTNode *node);
void genFactor(ASTNode *node);

int labelCount = 0;

char* newLabel() {
    static char buf[20];
    sprintf(buf, "L%d", labelCount++);
    return strdup(buf);
}

// Generate code for expressions and place result in a register or on stack
void genExpr(ASTNode *node) {
    if (!node) return;
    if(node->type == NODE_CONST) {
        printf("  PUSH %d\n", node->data.intValue);
    } else if(node->type == NODE_ID) {
        int addr = getVarAddress(node->data.idName);
        printf("  LOAD %d\n", addr);
    } else if(node->type == NODE_EXPR) {
        genExpr(node->data.expr.left);
        genExpr(node->data.expr.right);
        switch(node->data.expr.op) {
            case '+': printf("  ADD\n"); break;
            case '-': printf("  SUB\n"); break;
            case '*': printf("  MUL\n"); break;
            case '/': printf("  DIV\n"); break;
            // Add relational operators if needed
        }
    }
    // Add more cases for arrays, parentheses, unary ops etc.
}

// Generate code for assignment
void genAssignment(ASTNode *node) {
    if(node->data.assignment.isArray) {
        // Handle array element assignment (simplified)
        // Assume index expression evaluated and stored somewhere
        printf("  ;; array element assignment not fully implemented\n");
    } else {
        // Simple variable assignment
        genExpr(node->data.assignment.right);
        int addr = getVarAddress(node->data.assignment.left->data.idName);
        printf("  STORE %d\n", addr);
    }
}

// Generate code for if statement
void genIf(ASTNode *node) {
    char *labelElse = newLabel();
    char *labelEnd = newLabel();

    genExpr(node->data.ifStmt.cond);
    printf("  JZ %s\n", labelElse);
    genStmtList(node->data.ifStmt.thenPart);
    printf("  JMP %s\n", labelEnd);
    printf("%s:\n", labelElse);

    if(node->data.ifStmt.elsePart)
        genStmtList(node->data.ifStmt.elsePart);

    printf("%s:\n", labelEnd);
}

// Generate code for while loop
void genWhile(ASTNode *node) {
    char *labelStart = newLabel();
    char *labelEnd = newLabel();

    printf("%s:\n", labelStart);
    genExpr(node->data.whileStmt.cond);
    printf("  JZ %s\n", labelEnd);
    genStmtList(node->data.whileStmt.body);
    printf("  JMP %s\n", labelStart);
    printf("%s:\n", labelEnd);
}

// Generate code for print statement
void genPrint(ASTNode *node) {
    genExpr(node->data.printStmt.expr);
    printf("  PRINT\n");
}

// Generate code for statements
void genStatement(ASTNode *node) {
    if (!node) return;
    switch(node->type) {
        case NODE_ASSIGN:
            genAssignment(node);
            break;
        case NODE_IF:
            genIf(node);
            break;
        case NODE_WHILE:
            genWhile(node);
            break;
        case NODE_PRINT:
            genPrint(node);
            break;
        case NODE_BLOCK:
            genBlock(node);
            break;
        default:
            break;
    }
}

// Generate code for statement list
void genStmtList(ASTNode *node) {
    while(node) {
        genStatement(node);
        node = node->next;
    }
}

// Generate code for variable definitions
void genVarDef(ASTNode *node) {
    for(int i=0; i<node->data.varDef.count; i++) {
        addVariable(node->data.varDef.varNames[i], node->data.varDef.arraySizes[i]);
    }
}

// Generate code for block
void genBlock(ASTNode *node) {
    if(node->data.varDef.count > 0)
        genVarDef(node);

    genStmtList(node->next);
}

// Generate code for the whole program
void genProgram(ASTNode *node) {
    genBlock(node);
    printf("  HALT\n");
}

// Main (example usage - assumes AST already built)
int main() {
    // Normally, parser generates AST.
    // Here you would call genProgram(rootAST);
    // For demonstration, no actual AST building is shown.
    return 0;
}