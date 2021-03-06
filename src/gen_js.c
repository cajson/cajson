#include <gen_j.c>

// class = 'class' id map
static void gen_class(node_t *nid, node_t *nmap) {
    emit("class ");
    gen_code(nid);
    emit(" {\n"); block_level++;
    for (link_t *p = nmap->list->head; p != NULL; p = p->next) {
        ok(p->node->type == Pair);
        node_t *nkey = p->node->array[0];
        node_t *nval = p->node->array[1];
        if (nval->type == Function) {
            char *name = nkey->ptk->str; int len=nkey->ptk->len;
            line(nkey->ptk->line); indent(block_level); 
            if (head_eq(name, len, "__init")) {
                emit("constructor");
            } else {
                gen_code(nkey);
            }
            node_t *params = nval->array[1], *block=nval->array[2];
            gen_code(params);
            gen_code(block);
        }
        emit("\n");
    }
    block_level --;
    line(0); indent(block_level); emit("}");
}

// map = [ (expr:expr)* ]
static void gen_map(node_t *nmap) {
    emit("{");
    link_t *head = nmap->list->head;
    gen_list(head, ",");
    emit("}");
}

static void gen_import(node_t *str1, node_t *id2) {
    emit("import * as ");
    gen_code(id2);
    emit(" from ");
    gen_code(str1);
}

// pid = (@|$)? id
static void gen_pid(node_t *pid) {
    node_t *n = pid->node;
    if (n->type == Global) {
        emit("global.");
    } else if (n->type == This) {
        emit("this.");
    }
    gen_code(n->array[0]);
}

// (await|new)? pid ( [expr] | . id | args )*
static void gen_term(node_t *key, node_t *pid, link_t *head) {
    if (key) {
        gen_code(key);
        emit(" ");
    }
    gen_code(pid);
    for (link_t *p=head; p != NULL; p = p->next) {
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
    if (exp) {
        emit("=");
        gen_code(exp);
    }
}

// params = assign*
static void gen_params(link_t *head) {
    emit("(");
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node->array[0]); // id 
        if (p->next != NULL) emit(",");
    }
    emit(")");
}

// (return|?) expr
static void gen_return(int op, node_t *exp) {
    emit("return ");
    gen_code(exp);
}

// for id op expr stmt
static void gen_for3(char *op, node_t *id, node_t *exp, node_t *stmt) {
    emit("for (let ");
    gen_code(id);
    emit("%s", op);
    gen_code(exp);
    emit(")");
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

// function = fn id?(params) block
static void gen_function(node_t *id, node_t *params, node_t *block) {
    emit("function ");
    if (id) gen_code(id);
    gen_code(params);
    gen_code(block);
}

void gen_js(node_t *root) {
    emit("// source file: %s\n", ifile);
    emit("import '../sys/cj.js'")
    gen_code(root);
    emit("\n");
}
