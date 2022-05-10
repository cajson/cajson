#include <gen_j.c>

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    if (n->type == Global) {
        emit("@");
    } else if (n->type == This) {
        emit("$");
    }
    gen_code(n->array[0]);
}

// term = (@|$)? id ( [expr] | . id | args )*      // pid=(@|$)? id
static void gen_term(node_t *pid, link_t *head) {
    link_t *p;
    gen_code(pid);
    for (p=head; p != NULL; p = p->next) {
        node_t *n = p->node; int op = n->type;
        if (op == '[') {
            emit("[");
            gen_code(n->array[0]);
            emit("]");
        } else if (op == '.') {
            emit(".");
            gen_code(n->array[0]);
        } else if (op == Args) {
            gen_code(n);
        }
    }
}

// assign = pid(:type?)?= expr
static void gen_assign(node_t *pid, node_t *type, node_t *exp) {
    gen_code(pid);
    if (type) {
        emit(":");
        if (type->list != NULL)
            gen_list(type->list->head, "");
    }
    if (exp) {
        emit("=");
        gen_code(exp);
    }
}

// (return|?) expr
static void gen_return(int op, node_t *exp) {
    char name[20];
    id_name(op, name);
    emit("%s ", name);
    gen_code(exp);
}

// params = assign*
static void gen_params(link_t *head) {
    emit("(");
    gen_list(head, ",");
    emit(")");
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

// for id:=expr to expr (step expr) stmt
static void gen_for_to(node_t *id, node_t *from, node_t *to, node_t *step, node_t *stmt) {
    emit("for ");
    gen_code(id);
    emit(":=");
    gen_code(from);
    emit(" to ");
    gen_code(to);
    if (step != NULL) {
        emit(" step ");
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

void gen_cj(node_t *root) {
    emit("// source file: %s\n", ifile);
    gen_code(root);
    emit("\n");
}
