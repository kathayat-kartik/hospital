#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
  #define CLEAR "cls"
  #define STRCASE_CMP _stricmp
#else
  #include <unistd.h>
  #define CLEAR "clear"
  #define STRCASE_CMP strcasecmp
#endif

// ----- STANDARD COLORS -----
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

// ------------------ STRUCTURES ------------------
typedef struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    char diseases[200]; // comma-separated
    struct Doctor *next;
} Doctor;

typedef struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    int emergency;
    int severity;
    char assignedDoctor[50];
    struct Patient *next;
} Patient;

// ------------------ GLOBALS ------------------
Doctor *doctor_head = NULL;
Patient *patient_head = NULL;
int next_pid = 1;

// ------------------ UTIL ------------------
void clear_screen() { system(CLEAR); }

void draw_title() {
    printf("%s", COLOR_CYAN);
    printf("==========================================================================\n");
    printf("||                                                                      ||\n");
    printf("||    MEDI ASSIST HOSPITAL QUEUE MANAGEMENT SYSTEM                      ||\n");
    printf("||                                                                      ||\n");
    printf("==========================================================================\n\n");
    printf("%s", COLOR_RESET);
}

void wait_for_key() {
    printf("%s\nPress Enter to return to menu...%s", COLOR_YELLOW, COLOR_RESET);
    getchar();
}

// trim leading/trailing spaces
static void trim(char *s) {
    char *p = s;
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;
    if (p != s) memmove(s, p, strlen(p) + 1);
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == ' ' || s[n-1] == '\t' || s[n-1] == '\r' || s[n-1] == '\n')) {
        s[n-1] = '\0'; n--;
    }
}

// case-insensitive substring search portable
char *strcasestr_portable(const char *haystack, const char *needle) {
    if (!haystack || !needle) return NULL;
    size_t nl = strlen(needle);
    if (nl == 0) return (char *)haystack;
    for (; *haystack != '\0'; haystack++) {
        if (STRCASE_CMP(haystack, needle) == 0) return (char*)haystack;
        if (strlen(haystack) < nl) return NULL;
        char tmp[256];
        if (nl < sizeof(tmp)) {
            strncpy(tmp, haystack, nl);
            tmp[nl] = '\0';
            if (STRCASE_CMP(tmp, needle) == 0) return (char*)haystack;
        }
    }
    return NULL;
}

