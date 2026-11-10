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
    // TODO: Return a pointer to the most recently saved message.
    //   - Which index holds the most recent message? Messages are saved in
    //     order, so the most recent one is the last one saved.
    //   - This function returns an ADDRESS, not a message. How do you get
    //     the address of an array element?
    //   - What should you return if nothing has been saved yet? What is
    //     count in that case?
    (void)history; (void)count;   // delete this line when you start
    return NULL;
}

// ---- PART 3: the emoji table ----

char *find_emoji(char *word) {
    // TODO: Look through the EMOJIS table (below) for the entry whose code
    //       matches word, and return that entry's emoji.
    //   - EMOJIS is an array of NUM_EMOJIS structs, one per shortcode, and
    //     you may need to check every one. How do you reach one member of
    //     the struct at index i?
    //   - What should you return if no entry matches? (echo.h says.)
    //
    //   Note: to compare two strings, use strcmp(a, b). It returns 0 when
    //   a and b hold the same text. (== would compare their addresses.)
    (void)word;   // delete this line when you start
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
