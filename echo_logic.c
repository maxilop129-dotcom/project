// echo_logic.c: the echo server's history and emoji functions (LOGIC layer).
//
// PART 2 and PART 3 are yours: the three functions marked TODO. Each one is
// only a few lines long. The questions in each TODO point you to what you
// need to figure out. The rest of this file is provided; read it if you're
// curious, but you don't need to change it.
//
// Run `make test` to check your work.

#include "echo.h"

// ---- PART 2: the message history ----

int add_to_history(struct Message history[], int *count,
                   struct Message *msg) {
    if (*count >= MAX_HISTORY) {
        return -1;             
    }
    history[*count] = *msg;    
    (*count)++;                 
    return 0;
}
    
struct Message *last_message(struct Message history[], int count) {
    if (count == 0) {
        return NULL;              // nothing saved yet
    }
    return &history[count - 1];   // address of the most recent message
}


// ---- PART 3: the emoji table ----

char *find_emoji(char *word) {
    int i;

   
    for (i = 0; i < NUM_EMOJIS; i++) {
    
        if (strcmp(word, EMOJIS[i].code) == 0) {
            return EMOJIS[i].emoji;  
        }
    }

    
    return NULL;
}

// =====================================================================
// Provided: you do not need to change anything below this line.
// =====================================================================

struct Emoji EMOJIS[] = {
    { ":)",          "🙂" },
    { ":(",          "🙁" },
    { ":D",          "😄" },
    { ":laugh:",     "😂" },
    { ":heart:",     "❤️" },
    { ":fire:",      "🔥" },
    { ":thumbsup:",  "👍" },
    { ":party:",     "🎉" },
};
int NUM_EMOJIS = sizeof EMOJIS / sizeof EMOJIS[0];

void make_message(struct Message *msg, char *sender, char *text) {
    memset(msg, 0, sizeof *msg);                    // no leftover junk
    snprintf(msg->sender, sizeof msg->sender, "%s", sender);
    snprintf(msg->text, sizeof msg->text, "%s", text);
    msg->text[strcspn(msg->text, "\n")] = '\0';     // drop a trailing newline
}

int add_emojis(char *text, size_t text_size) {
    char out[TEXT_LEN];
    size_t limit = text_size < sizeof out ? text_size : sizeof out;
    size_t used = 0;
    int replaced = 0;
    char *p = text;

    while (*p != '\0') {
        if (*p == ' ') {                         // copy spaces as they are
            if (used + 1 > limit - 1) break;
            out[used++] = ' ';
            p++;
            continue;
        }

        // Copy the next word into its own string.
        size_t len = strcspn(p, " ");
        char word[TEXT_LEN];
        size_t copy = len < sizeof word ? len : sizeof word - 1;
        memcpy(word, p, copy);
        word[copy] = '\0';

        // Swap in the emoji if the word is a shortcode.
        char *emoji = find_emoji(word);
        char *piece = (emoji != NULL) ? emoji : word;
        size_t piece_len = strlen(piece);        // bytes, not characters

        if (used + piece_len > limit - 1) break; // keep room for '\0'
        memcpy(out + used, piece, piece_len);
        used += piece_len;
        if (emoji != NULL) replaced++;
        p += len;
    }

    out[used] = '\0';
    memcpy(text, out, used + 1);
    return replaced;
}
