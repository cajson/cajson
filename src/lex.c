token_t tk;   // current token (目前 token)

#define syntax_error() { printf("Error at line=%d, pos=%d. C halt at file=%s line=%d, tk=%d(%c) %.*s\n", line, p-lp, __FILE__, __LINE__, tk.type, (char)tk.type, tk.len, tk.str); exit(1); }

void scan() { // 詞彙解析 lexer
  tk.type = End;
  while (*p) {
    tk.str = p;
    tk.line = line;
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
    } else if (ch == '/' && *p == '/') { // 註解  //... 
        ++p;
        while (*p != 0 && *p != '\n') ++p;
    } else if (ch == '/' && *p == '*') { // 註解 /*...*/
        ++p;
        while (!(*p =='*' && *(p+1) == '/')) {
          if (*p == '\n') line++;
          ++p;
        }
        p+=2;
    } else { // 以下為運算元 =+-!<>|&^%*[?~, ++, --, !=, <=, >=, ||, &&, ~  ;{}()],:
      tk.type = ch;
      if (ch == '=') { if (*p == '=') { ++p; tk.type = Eq; } break; }
      else if (ch == '+') { if (*p == '+') { ++p; tk.type = Inc; } break; }
      else if (ch == '-') { if (*p == '-') { ++p; tk.type = Dec; } break; }
      else if (ch == '!') { if (*p == '=') { ++p; tk.type = Neq; } break; }
      else if (ch == '<') { if (*p == '=') { ++p; tk.type = Le; } else if (*p == '<') { ++p; tk.type = Shl; } break; }
      else if (ch == '>') { if (*p == '=') { ++p; tk.type = Ge; } else if (*p == '>') { ++p; tk.type = Shr; } break; }
      else if (ch == '|') { if (*p == '|') { ++p; tk.type = Lor; } else break; }
      else if (ch == '&') { if (*p == '&') { ++p; tk.type = Land; } else break; }
      else if (strchr(" \n\r\t,;", ch)) {} // 忽略空格與逗點分號，繼續往前讀...
      else { break; } // 其他字元，單一個字即 token
    }
  }
  tk.len = p-tk.str;
  printf("%.*s ", tk.len, tk.str);
}

bool tk_match(token_t t, char *str) {
    int len = strlen(str);
    return len == t.len && memcmp(str, t.str, len)==0;
}

bool match(char *str) {
    return tk_match(tk, str);
}

token_t next() {
  token_t r=tk; 
  scan();
  return r;
}

#define skip(t) ({token_t r=tk; if (tk.type==t) next(); else syntax_error(); r; })
#define skip_str(str) ({token_t r=tk; if (match(str)) next(); else syntax_error(); r; })

token_t tk0; char *p0;
void scan_save() { tk0 = tk; p0=p; }
void scan_restore() { tk = tk0; p=p0; }

int lex(char *source) {
    p = source;
    src = 1;
    next();
    while (true) {
        token_t t = next();
        if (t.type == End) break;
        printf("%d: %.*s\n", t.line, t.len, t.str);
    }
}

