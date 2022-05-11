#include <gen1.c>

// array = [ expr* ]
static void gen_array(link_t *head) {
    emit("{");
    gen_list(head, ",");
    emit("}");
}

static void gen_str(node_t *node) {
    emit("\"%.*s\"", node->ptk->len-2, node->ptk->str+1);
}

static void gen_pair(node_t *n1, node_t *n2) { // ??
    gen_code(n1);
    emit(":");
    gen_code(n2);
}

// map = [ (expr:expr)* ]
static void gen_map(link_t *head) { // ??
    emit("{");
    gen_list(head, ",");
    emit("}");
}


// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    /*
    if (n->type == Global) {
        emit("@");
    } else if (n->type == This) {
        emit("$");
    }
    */
    gen_code(n->array[0]);
}

// c: no change
// term = pid ( [expr] | . id | args )*
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
        // emit(":");
        if (type->list != NULL)
            gen_list(type->list->head, "");
        emit(" ");
    }
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

// for id=expr to expr (step expr) stmt
static void gen_for_to(node_t *id, node_t *from, node_t *to, node_t *step, node_t *stmt) {
    emit("for (int ");
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

// type 沒紀錄，要修改
// function = fn id?(params) block
static void gen_function(node_t *id, node_t *params, node_t *block) {
    emit("void ");
    if (id) gen_code(id);
    gen_code(params);
    gen_code(block);
}

void gen_c(node_t *root) {
    emit("// source file: %s\n", ifile);
    gen_code(root);
    emit("\n");
}

