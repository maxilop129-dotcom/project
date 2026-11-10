// echo.h: the echo server's struct and the logic functions.
//
// The project has two layers:
//   LOGIC (you work here):   echo.h, echo_logic.c
//                            structs, arrays and pointers
//   NETWORK (provided):      server.c, client.c, net.c
//                            sockets
//
// PART 1 (you write this): define struct User and struct Message below.

#ifndef ECHO_H
#define ECHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define NAME_LEN     32     // longest name, including the '\0'
#define TEXT_LEN    256     // longest message, including the '\0'
#define MAX_HISTORY 100     // most messages the server remembers

// ---------------------------------------------------------------------
// TODO (Part 1a): define struct User: the person using the program.
// It must have exactly these two members, with these names and types:
//
//   name : an array of NAME_LEN chars   (the person's name)
//   fd   : an int                       (a number for their connection)
// ---------------------------------------------------------------------



// ---------------------------------------------------------------------
// TODO (Part 1b): define struct Message: one message.
// It must have exactly these two members, in this order, with these
// names and types:
//
//   sender : an array of NAME_LEN chars  (who sent it)
//   text   : an array of TEXT_LEN chars  (what they typed)
// ---------------------------------------------------------------------



// Emoji shortcodes the server understands. The table is in echo_logic.c.
struct Emoji {
    char *code;     // what people type, like ":fire:"
    char *emoji;    // what it becomes, like "🔥"
};
extern struct Emoji EMOJIS[];
extern int NUM_EMOJIS;

// ---- PART 2 (you write these in echo_logic.c): the message history ----
// The saved messages are history[0] .. history[count - 1].

// Copy the message that msg points to into the next free slot of history,
// and add 1 to *count. Returns 0, or -1 if history already holds
// MAX_HISTORY messages.
int add_to_history(struct Message history[], int *count,
                   struct Message *msg);

// Return a pointer to the most recent message in history, or NULL if
// there are no messages yet.
struct Message *last_message(struct Message history[], int count);

// ---- PART 3 (you write this in echo_logic.c): the emoji table ----

// If word is exactly one of the shortcodes in EMOJIS, return a pointer to
// its emoji. Otherwise return NULL.
char *find_emoji(char *word);

// ---- Provided ----

// Fill in *msg with sender and text (without a trailing newline).
void make_message(struct Message *msg, char *sender, char *text);

// Replace every shortcode word in text with its emoji, using find_emoji().
// Returns how many were replaced.
int add_emojis(char *text, size_t text_size);

// =====================================================================
// net.c (provided)
// =====================================================================

// Send or receive one whole struct Message over a socket.
int send_message(int fd, struct Message *msg);   // 0, or -1 on error
int recv_message(int fd, struct Message *msg);         // 1, or 0 on hang-up

#endif
