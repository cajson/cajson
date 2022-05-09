#include <gen_j.c>

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
    if (type) emit("let ");
    gen_code(pid);
    /*
    if (type) {
        emit(":");
        if (type->list != NULL)
            gen_list(type->list->head, "");
    }
    */
    if (exp) {
        emit("=");
        gen_code(exp);
    }
}

// (return|?) expr
static void gen_return(int op, node_t *exp) {
    emit("return ");
    gen_code(exp);
}

// for id=expr to expr (step expr) stmt
static void gen_for_to(node_t *id, node_t *from, node_t *to, node_t *step, node_t *stmt) {
    emit("for (let ");
    gen_code(id);
    emit("=");
    gen_code(from);
    emit(";");
    gen_code(id);
    emit("<=");
    gen_code(to);
    emit(";")
    gen_code(id);
    if (step) {
        emit("+=");
        gen_code(step);
    } else {
        emit("++");
    }
    emit(")");
    gen_code(stmt);
}

// function = fn (params) block
static void gen_function(node_t *params, node_t *block) {
    emit("function");
    gen_code(params);
    gen_code(block);
}

void gen_js(node_t *root) {
    emit("// source file: %s\n", ifile);
    emit("import { print } from '../sys/cj.js'")
    gen_code(root);
    emit("\n");
}
