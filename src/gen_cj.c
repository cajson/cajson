#include <gen.h>

static void gen_str(node_t *node) {
    gen_sym(node);
}

static void gen_num(node_t *node) {
    gen_sym(node);
}

static void gen_id(node_t *node) {
    gen_sym(node);
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

// term = (@|$)? id ( [expr] | . id | args )*      // pid=(@|$)? id
static void gen_term(node_t *pid, link_t *head) {
    link_t *p;
    gen_code(pid);
    for (p=head; p != NULL; p = p->next) {
        node_t *n = p->node; int op = n->type;
        if (op == '[') {
            emit("[");
            gen_code(n->node);
            emit("]");
        } else if (op == '.') {
            emit(".");
            gen_code(n->node);
        } else if (op == Args) {
            gen_code(n);
        }
    }
}

// param = id (:expr)?
static void gen_param(node_t *id, node_t *exp) {
    gen_code(id);
    if (exp != NULL) {
        emit(":");
        gen_code(exp);
    }
}

// params = param*
static void gen_params(link_t *head) {
    emit("(");
    gen_list(head);
    emit(")");
}

// array = [ expr* ]
static void gen_array(link_t *head) {
    emit("[");
    gen_list(head);
    emit("]");
}

static void gen_pair(node_t *n1, node_t *n2) {
    gen_code(n1);
    emit(":");
    gen_code(n2);
}

// map = [ (expr:expr)* ]
static void gen_map(link_t *head) {
    emit("{");
    gen_list(head);
    emit("}");
}

// args = ( expr* )
static void gen_args(link_t *head) {
    emit("(");
    gen_list(head);
    emit(")");
}

// (id [:=])? expr
static void gen_assign(node_t *id, char op, node_t *exp) {
    gen_code(id);
    emit("%c", op);
    gen_code(exp);
}

// return expr
static void gen_return(node_t *exp) {
    emit("return");
    gen_code(exp);
}

// while expr stmt
static void gen_while(node_t *exp, node_t *stmt) {
    emit("while"); gen_code(exp);
    gen_code(stmt);
}

// if expr stmt (else stmt)?
static void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2) {
    emit("if"); gen_code(exp);
    gen_code(stmt1);
    if (stmt2) {
        emit("else");
        gen_code(stmt2);
    }
}

// for id op expr stmt
static void gen_for3(char *op, node_t *id, node_t *exp, node_t *stmt) {
    emit("for");
    gen_code(id);
    emit("%s", op);
    gen_code(exp);
    gen_code(stmt);
}

// for id in expr stmt
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt) {
    gen_for3("in", id, exp, stmt);
}

// for id of expr stmt
static void gen_for_of(node_t *id, node_t *exp, node_t *stmt) {
    gen_for3("of", id, exp, stmt);
}

// for id=expr to expr (step expr) stmt
static void gen_for_to(node_t *id, node_t *from, node_t *to, node_t *step, node_t *stmt) {
    emit("for");
    gen_code(id);
    emit("=");
    gen_code(from);
    emit("to");
    gen_code(to);
    if (step != NULL) {
        emit("step");
        gen_code(step);
    }
    gen_code(stmt);
}

// function = fn (params) block
static void gen_function(node_t *params, node_t *block) {
    emit("fn");
    gen_code(params);
    gen_code(block);
}

// stmt
static void gen_stmt(node_t *stmt) {
    if (top == 0 || peek() == Block) {
        emit("\n/* %-3d*/\t", stmt->line);
        indent(block_level);
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
    emit("\n/*    */\t"); indent(block_level-1); emit("{");
    gen_stmts(block->node); // stmts
    emit("\n/*    */\t"); indent(block_level-1); emit("}");
}

#include <gen.c>

void gen_cj(node_t *root) {
    emit0("// source file: %s\n", iFile);
    return gen_code(root);
}
