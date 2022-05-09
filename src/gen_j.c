#include <gen.c>

static void gen_str(node_t *node) {
    gen_token(node);
}

static void gen_num(node_t *node) {
    gen_token(node);
}

static void gen_id(node_t *node) {
    gen_token(node);
}

static void gen_op0(int op) {
    char name[20];
    id_name(op, name);
    emit("%s", name);
}

static void gen_op1(int op, node_t *node) {
    char name[20];
    id_name(op, name);
    emit("%s", name);
    gen_code(node);
}

static void gen_op2(node_t *node1, int op, node_t *node2) {
    emit("(");
    gen_code(node1);
    char name[20];
    id_name(op, name);
    emit("%s", name);
    gen_code(node2);
    emit(")");
}

// array = [ expr* ]
static void gen_array(link_t *head) {
    emit("[");
    gen_list(head, ",");
    emit("]");
}


// params = assign*
static void gen_params(link_t *head) {
    emit("(");
    gen_list(head, ",");
    emit(")");
}

// args = ( expr* )
static void gen_args(link_t *head) {
    emit("(");
    gen_list(head, ",");
    emit(")");
}

static void gen_pair(node_t *n1, node_t *n2) {
    gen_code(n1);
    emit(":");
    gen_code(n2);
}

// map = [ (expr:expr)* ]
static void gen_map(link_t *head) {
    emit("{");
    gen_list(head, ",");
    emit("}");
}


// while expr stmt
static void gen_while(node_t *exp, node_t *stmt) {
    emit("while "); gen_code(exp);
    gen_code(stmt);
}

// if expr stmt (else stmt)?
static void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2) {
    emit("if "); gen_code(exp);
    gen_code(stmt1);
    if (stmt2) {
        emit(" else");
        gen_code(stmt2);
    }
}


// for id op expr stmt
static void gen_for3(char *op, node_t *id, node_t *exp, node_t *stmt) {
    emit("for ");
    gen_code(id);
    emit("%s", op);
    gen_code(exp);
    gen_code(stmt);
}

// for id in expr stmt
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt) {
    gen_for3(" in ", id, exp, stmt);
}

// for id of expr stmt
static void gen_for_of(node_t *id, node_t *exp, node_t *stmt) {
    gen_for3(" of ", id, exp, stmt);
}


// stmt
static void gen_stmt(node_t *stmt) {
    if (top == 0 || peek() == Block) {
        emit("\n");
        line(stmt->ptk->line);
        indent(block_level);
    } else {
        emit(" ");
    }
    gen_code(stmt->node);
}

// stmts = stmt*
static void gen_stmts(node_t *node) {
    link_t *p = node->list->head;
    while (p != NULL) {
        gen_code(p->node);
        p = p->next;
    }
}

// block = { stmts }
static void gen_block(node_t *block) {
    emit("\n");
    line(0);
    indent(block_level-1);
    emit("{");
    gen_stmts(block->node); // stmts
    emit("\n");
    line(0);
    indent(block_level-1); emit("}");
}
