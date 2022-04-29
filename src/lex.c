typedef struct token_t {
    char type;
    char *str;  // token 的字串
    int len;    // token 的字串長度
    sym_t *sym; // 指向 symbol
} token_t;

token_t tk;   // current token (目前 token)

void next() { // 詞彙解析 lexer
  tk.type = None;
  while (*p) {
    tk.str = p;
    char ch = *p++;
    if (ch == '\n') { // 換行
      if (src) {
        printf("// %d: %.*s", line, p - lp, lp); // 印出該行
        lp = p;     // lp = p  = 新一行的原始碼開頭
        printf(le); // 印出上一行的所有目的碼
        le = e;
      }
      ++line;
    }
    // else if (ch == '#') { // 取得 #include <stdio.h> 這類的一整行
    //   while (*p != 0 && *p != '\n') ++p;
    // }
    else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_') { // 取得變數名稱
      while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_')
          *p++;
      tk.type = Id;
      tk.sym = sym_add(tk.str, p-tk.str);
      break;
    }
    else if (ch >= '0' && ch <= '9') { // 取得數字串
      while ((*p>='0' && *p<='9') || (*p=='.')) p++;
      // sscanf(tk.str, "%lf", &tk_float);
      tk.sym = sym_add(tk.str, p-tk.str);
      tk.type = Num;
      break;
    }
    else if (ch == '\'') { // 字元或字串
      while (*p != '\'') p++;
      p++;
      tk.sym = sym_add(tk.str, p-tk.str);
      tk.type = Str;
      break;
    } // 以下為運算元 =+-!<>|&^%*[?~, ++, --, !=, <=, >=, ||, &&, ~  ;{}()],:
    else {
      tk.type = ch;
      if (ch == '/' && *p == '/') { // 註解
          ++p;
          while (*p != 0 && *p != '\n') ++p; // 略過註解
      }
      else if (ch == '=') { if (*p == '=') { ++p; tk.type = Eq; } break; }
      else if (ch == '+') { if (*p == '+') { ++p; tk.type = Inc; } break; }
      else if (ch == '-') { if (*p == '-') { ++p; tk.type = Dec; } break; }
      else if (ch == '!') { if (*p == '=') { ++p; tk.type = Neq; } break; }
      else if (ch == '<') { if (*p == '=') { ++p; tk.type = Le; } else if (*p == '<') { ++p; tk.type = Shl; } break; }
      else if (ch == '>') { if (*p == '=') { ++p; tk.type = Ge; } else if (*p == '>') { ++p; tk.type = Shr; } break; }
      else if (ch == '|') { if (*p == '|') { ++p; tk.type = Lor; } else break; }
      else if (ch == '&') { if (*p == '&') { ++p; tk.type = Land; } else break; }
      else if (strchr(" \n\r\t", ch)) {} // 空格，繼續往前讀...
      else { break; } // 其他字元，單一個字即 token
    }
  }
  tk.len = p-tk.str;
}

int lex(char *source) {
    p = source;
    while (true) {
        next();
        if (tk.type == None) break;
        printf("%2d:%d %.*s\n", tk, tk.len, tk.len, tk.str);
    }
}