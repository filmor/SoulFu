#ifndef SOULFU_DCODESRC_H
#define SOULFU_DCODESRC_H

// Used for mega_find...  Return pointer to function header
#define SRC_REQUEST_ENTRY       0
// Tells us where a CallFunction should take us
#define SRC_REQUEST_OFFSET      1
// Return pointer to a function's argument/returncode string
#define SRC_REQUEST_ARGUMENTS   2
// Return pointer to the start of the function's run file data
#define SRC_REQUEST_FILESTART   3
#define SRC_HEADERIZE   1   // The first stage of compilation
#define SRC_COMPILERIZE 2   // The second stage of compilation
#define SRC_FUNCTIONIZE 3   // The third stage of compilation

// !!!BAD!!! There are undefined opcodes
#define OPCODE_EQUALS                   0
#define OPCODE_ADD                      1
#define OPCODE_SUBTRACT                 2
#define OPCODE_MULTIPLY                 3
#define OPCODE_DIVIDE                   4
#define OPCODE_INCREMENT                5
#define OPCODE_DECREMENT                6
#define OPCODE_ISEQUAL                  7
#define OPCODE_ISNOTEQUAL               8
#define OPCODE_ISGREATEREQUAL           9
#define OPCODE_ISLESSEREQUAL           10
#define OPCODE_ISGREATER               11
#define OPCODE_ISLESSER                12
#define OPCODE_LOGICALAND              13
#define OPCODE_LOGICALOR               14
#define OPCODE_LOGICALNOT              15
#define OPCODE_NEGATE                  16
#define OPCODE_BITWISEAND              19
#define OPCODE_BITWISEOR               20
#define OPCODE_BITWISELEFT             21
#define OPCODE_BITWISERIGHT            22
#define OPCODE_MODULUS                 23
#define OPCODE_LOCALMESSAGE            24
#define OPCODE_LOGMESSAGE              25
#define OPCODE_FINDSELF                26
#define OPCODE_SYSTEMSET               27
#define OPCODE_SYSTEMGET               28
#define OPCODE_DEBUGMESSAGE            29
#define OPCODE_TOFLOAT                 30
#define OPCODE_TOINT                   31
#define OPCODE_F_EQUALS                32
#define OPCODE_F_ADD                   33
#define OPCODE_F_SUBTRACT              34
#define OPCODE_F_MULTIPLY              35
#define OPCODE_F_DIVIDE                36
#define OPCODE_F_INCREMENT             37
#define OPCODE_F_DECREMENT             38
#define OPCODE_F_ISEQUAL               39
#define OPCODE_F_ISNOTEQUAL            40
#define OPCODE_F_ISGREATEREQUAL        41
#define OPCODE_F_ISLESSEREQUAL         42
#define OPCODE_F_ISGREATER             43
#define OPCODE_F_ISLESSER              44
#define OPCODE_F_LOGICALAND            45
#define OPCODE_F_LOGICALOR             46
#define OPCODE_F_LOGICALNOT            47
#define OPCODE_F_NEGATE                48
#define OPCODE_STRING                  49
#define OPCODE_STRINGGETNUMBER         50
#define OPCODE_STRINGCLEAR             51
#define OPCODE_STRINGCLEARALL          52
#define OPCODE_STRINGAPPEND            53
#define OPCODE_STRINGCOMPARE           54
#define OPCODE_STRINGLENGTH            55
#define OPCODE_STRINGCHOPLEFT          56
#define OPCODE_STRINGCHOPRIGHT         57
#define OPCODE_STRINGRANDOMNAME        58
#define OPCODE_STRINGSANITIZE          59
#define OPCODE_NETWORKMESSAGE          60
#define OPCODE_STRINGLANGUAGE          61
#define OPCODE_STRINGUPPERCASE         62
#define OPCODE_STRINGAPPENDNUMBER      63
#define OPCODE_CALLFUNCTION            64
#define OPCODE_RETURNINT               65
#define OPCODE_RETURNFLOAT             66
#define OPCODE_IFFALSEJUMP             67
#define OPCODE_JUMP                    68
#define OPCODE_SQRT                    69
#define OPCODE_FILEOPEN                70
#define OPCODE_FILEREADBYTE            71
#define OPCODE_FILEWRITEBYTE           72
#define OPCODE_FILEINSERT              73
#define OPCODE_SPAWN                   74
#define OPCODE_GOPOOF                  75
#define OPCODE_DISMOUNT                76
#define OPCODE_ROLLDICE                77
#define OPCODE_PLAYSOUND               78
#define OPCODE_PLAYMEGASOUND           79
#define OPCODE_DISTANCESOUND           80
#define OPCODE_PLAYMUSIC               81
#define OPCODE_UPDATEFILES             82
#define OPCODE_SIN                     83
#define OPCODE_ACQUIRETARGET           84
#define OPCODE_FINDPATH                85
#define OPCODE_BUTTONPRESS             86
#define OPCODE_AUTOAIM                 87
#define OPCODE_ROOMHEIGHTXY            88
#define OPCODE_WINDOWBORDER            96
#define OPCODE_WINDOWSTRING            97
#define OPCODE_WINDOWMINILIST          98
#define OPCODE_WINDOWSLIDER            99
#define OPCODE_WINDOWIMAGE            100
#define OPCODE_WINDOWTRACKER          101
#define OPCODE_WINDOWBOOK             102
#define OPCODE_WINDOWINPUT            103
#define OPCODE_WINDOWEMACS            104
#define OPCODE_WINDOWMEGAIMAGE        105
#define OPCODE_WINDOW3DSTART          106
#define OPCODE_WINDOW3DEND            107
#define OPCODE_WINDOW3DPOSITION       108
#define OPCODE_WINDOW3DMODEL          109
#define OPCODE_MODELASSIGN            110
#define OPCODE_PARTICLEBOUNCE         111
#define OPCODE_WINDOWEDITKANJI        112
#define OPCODE_WINDOW3DROOM           113
#define OPCODE_INDEXISLOCALPLAYER     114
#define OPCODE_FINDBINDING            115
#define OPCODE_FINDTARGET             116
#define OPCODE_FINDOWNER              117
#define OPCODE_FINDINDEX              118
#define OPCODE_FINDBYINDEX            119
#define OPCODE_FINDWINDOW             120
#define OPCODE_FINDPARTICLE           121
#define OPCODE_ATTACHTOTARGET         123
#define OPCODE_GETDIRECTION           124
#define OPCODE_DAMAGETARGET           125
#define OPCODE_EXPERIENCEFUNCTION     126
#define SRC_PERMANENT               0   // Define is permanent
#define SRC_TEMPORARY_FILE          1   // Define goes away when done with file
#define SRC_TEMPORARY_FUNCTION      2   // Define goes away when done with function
#define SRC_MAX_TOKEN              64   // The maximum number of pieces per line of a SRC file
#define SRC_MAX_DEFINE           2048   // The maximum number of defines
#define SRC_MAX_TOKEN_SIZE        128   // The maximum size of each piece
#define SRC_MAX_INDENT            256   // Allow up to 256 indentation levels...
#define SRC_JUMP_INVALID            0   // Marked as unused...
#define SRC_JUMP_IF                 1   // Used when an if is found
#define SRC_JUMP_ELSE               2   // Used when an else is found
#define SRC_JUMP_WHILE              3   // Used when a while is found
#define VAR_INVALID               '?'   // Used a bunch
#define VAR_INT                   'I'   // Used a bunch
#define VAR_FLOAT                 'F'   // Used a bunch
#define VAR_STRING                'S'   // For property extensions only
#define VAR_TEXT                  'T'   // For property extensions only
#define VAR_BYTE                  'B'   // For property extensions only
#define VAR_WORD                  'W'   // For property extensions only
#define MAX_VARIABLE               32   // I00 - I31, F00 - F31...
#define MAX_ARGUMENT               16
#define SRC_BUFFER_SIZE 65550

extern signed char compiler_error;

/* dcodesrc.c */
void src_close_jumps(unsigned char indent, unsigned char last_indent);
void src_add_return_opcode(void);
int src_get_define(char *token);
void src_set_priority(int start, int i, int end, signed char any_type);
void src_find_priority(int start, int end, signed char change_signs, signed char first_check);
signed char src_read_token(unsigned char *buffer);
void src_add_define(char *token, char *value, char temporary_level);
void src_undefine_level(char temporary_level);
signed char src_define_setup(void);
void src_generate_opcodes(int token_count);
void src_figure_variable_types(int token_count);
int src_find_function_entry(unsigned char *filedata, char *functionname);
int src_find_string_entry(unsigned char *filedata, char *stringname);
unsigned char *src_mega_find_function(unsigned char *functionstring, unsigned char *filename, unsigned char request);
void src_make_arrays(int token_count, char *filename);
signed char src_functionize(unsigned char *index, char *filename);
signed char src_stage_compile(unsigned char stage, unsigned char mask);

#endif
