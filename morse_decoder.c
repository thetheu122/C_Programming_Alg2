#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETRAS 26

// Letras em código morse 
char alfabeto[MAX_LETRAS] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

char *morse[MAX_LETRAS]= {
    ".-", "-...", "-.-.", "-..", ".", "..-.",
    "--.", "....", "..", ".---", "-.-", ".-..",
    "--", "-.", "---", ".--.", "--.-", ".-.",
    "...", "-", "..-", "...-", ".--", "-..-",
    "-.--", "--.."
};

// morse -> letra exata
char morse_to_char(const char *codigo){
    for (int i=0; i < MAX_LETRAS; i++ ){
        if (strcmp(codigo, morse[i]) == 0){
            return alfabeto[i];
        }
    }
    return '?'; // se não achar, devolve ?
}

// separação: 1 espaço = letras, 2 espaços = palavras
char **separacao_morse(char entrada[], int *qtd) {
    char **tokens = NULL;
    int count = 0;
    int n = (int)strlen(entrada);

    for (int i = 0; i < n; i++) {
        // dois espaços -> espaço entre palavras
        if (entrada[i] == ' ' && i+1 < n && entrada[i+1] == ' ') {
            tokens = (char**)realloc(tokens, (count + 1) * sizeof(char *));
            tokens[count] = (char*)malloc(2);
            strcpy(tokens[count], " ");  // token especial (palavra)
            count++;
            i++; // pula o segundo espaço
            continue;
        }

        if (entrada[i] == ' ') continue; // espaço simples (entre letras)

        // encontrar final do token
        int j = i;
        while (entrada[j] != ' ' && entrada[j] != '\0') j++;

        int len = j - i;
        tokens = (char**)realloc(tokens, (count + 1) * sizeof(char *));
        tokens[count] = (char*)malloc((len + 1) * sizeof(char));
        strncpy(tokens[count], &entrada[i], len);
        tokens[count][len] = '\0';
        count++;

        i = j - 1;
    }

    *qtd = count;
    return tokens;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s \"<entrada>\"\n", argv[0]);
        return 1;
    }

    int qtd;
    char **morse_lista = separacao_morse(argv[1], &qtd);

    // ---- 1ª PASSAGEM: calcula o tamanho total da mensagem ----
    int total = 0;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(morse_lista[i], " ") == 0) {
            total += 1; // espaço entre palavras
        } else {
            int len = (int)strlen(morse_lista[i]);
            if (len > 0 && morse_lista[i][len - 1] == '*') {
                // prefixo antes do '*'
                int prefix_len = len - 1;
                int matches = 0;
                for (int k = 0; k < MAX_LETRAS; k++) {
                    if (strncmp(morse[k], morse_lista[i], prefix_len) == 0) {
                        matches++;
                    }
                }
                // colchetes + quantidade de letras
                total += 2 + matches; // '[' + letras + ']'
            } else {
                total += 1; // letra normal (ou '?')
            }
        }
    }

    char *mensagem = (char*)malloc((total + 1) * sizeof(char));
    int pos = 0;

    // ---- 2ª PASSAGEM: monta a mensagem final ----
    for (int i=0; i < qtd; i++){
        if (strcmp(morse_lista[i], " ") == 0) {
            mensagem[pos++] = ' ';
            continue;
        }

        int len = (int)strlen(morse_lista[i]);
        if (len > 0 && morse_lista[i][len - 1] == '*') {
            // token corrompido: gera colchetes com todas as letras possíveis (ordem alfabética)
            int prefix_len = len - 1;
            mensagem[pos++] = '[';
            int wrote = 0;
            for (int k = 0; k < MAX_LETRAS; k++) {
                if (strncmp(morse[k], morse_lista[i], prefix_len) == 0) {
                    mensagem[pos++] = alfabeto[k];
                    wrote = 1;
                }
            }
            mensagem[pos++] = ']';
            // se nenhuma letra casa com o prefixo, fica "[]"
        } else {
            // conversão normal (A-Z); se não achar, vira '?'
            char c = morse_to_char(morse_lista[i]);
            mensagem[pos++] = c;
        }
    }
    mensagem[pos] = '\0';

    printf("Mensagem decodificada: %s\n", mensagem);

    // limpa memória dos tokens
    for (int i = 0; i < qtd; i++) free(morse_lista[i]);
    free(morse_lista);
    free(mensagem);

    return 0;
}

