/*
*   [ C String Library ]
*   Using the minimum library(s) possible
*
* Length       ( cString->Length(s)                 )   long 	DONE
* Strip        ( cString->Strip(s)                  )   long	DONE
* Trim         ( cString->Trim(s, "")               )   void	DONE
* Contains     ( cString->Contains(s, "Hello")      )   int
* CountChar    ( cString->CountChar(s, 'c')         )   long	DONE
* CountSubstr  ( cString->CountSubstr(s, "")        )   long
* StartsWith   ( cString->StartsWith(s, "Hello")    )   int
* EndsWith     ( cString->EndsWith(s, "World")      )   int
* IsLowercase  ( cString->IsLowercase(s)            )   int
* IsUppercase  ( cString->IsUppercase(s)            )   int
* RmChar       ( cString->RmChar(s, 'c')            )   void
* Replace      ( cString->ReplaceChar(s, 'c')       )   void
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#include "str.h"

String *string(char *data) {
	String *s = (String *)malloc(sizeof(String));
	if(data != NULL)
		s->Data = strdup(data);

	s->Utils		= __edit_str;

	return s;
}

void *__edit_str(String *s, STRING_EDIT_T mode, ...) {
	va_list args;
    switch(mode) {
        case _REPLACE: { va_start(args, 2); }
        default: { va_start(args, 1); }
    }

	switch(mode) {
		case _STRLENGTH:        { return (void *)__length(s); }
		case _STRIP:            { return (void *)__Strip(s); }
		case _TRIM:             { return (void *)__Trim(s, get_va_arg_char(args)); }
		case _COUNTCH:          { return (void *)__CountChar(s, get_va_arg_char(args)); }
		case _COUNTSTR:         { return (void *)__CountSubstr(s, get_va_arg_str(args)); }
		case _STARTSWITH:       { return (void *)__StartsWith(s, get_va_arg_str(args)); }
		case _ENDSWITH:         { return (void *)__EndsWith(s, get_va_arg_str(args)); }
		case _ISLOWERCASE:      { return (void *)__IsLowercase(s); }
        case _SPLIT:            { return (void *)__SplitChar(s, get_va_arg_char(args)); }
        case _REPLACE:          { return (void *)__Replace(s, get_va_arg_str(args), get_va_arg_str(args)); }
	}

	return 0;
}

long __length(String *s) {
	if(s->Data != NULL)
		return (long)strlen(s->Data);

	return (long)0;
}

long __Strip(String *s) {
    int start = 0, end = strlen(s->Data) - 1;
    long found = 0;

    while (isspace(s->Data[start])) {
        start++;
    }

    while (end >= start && isspace(s->Data[end])) {

        end--;
    }

    char *trimmed = strndup(s->Data + start, end - start + 1);
    __updateString(s, trimmed);

    return found;
}

long __Trim(String *s, char ch) {
    char *new = (char *)malloc(strlen(s->Data) + 1);
    memset(new, '\0', (strlen(s->Data) + 1));
    long found = 0;

    for(int i = 0; i < strlen(s->Data); i++) {
        if(s->Data[i] != ch) {
            strncat(new, &s->Data[i], sizeof(char));
        } else {
            found++;
        }
    }

    __updateString(s, new);
   return found;
}



long __CountChar(String *s, char ch) {
    long count = 0;
    for(int i = 0; i < strlen(s->Data); i++)
        if(s->Data[i] == ch)
            count++;

    return count;
}

long __CountSubstr(String *s, char *substr) {
    long count = 0;
    if(strlen(substr) < 2) return 0;

    for(int i = 0; i < strlen(s->Data); i++)
        if(s->Data[i] == substr[0] && s->Data[ i + strlen(substr)-1 ] == substr[strlen(substr) - 1])
            count++;

    return count;
}

long __StartsWith(String *s, const char *str) {
    if(s->Data[0] != str[0] && s->Data[1] != str[1]) return 0;

    for(int i = 0; i < strlen(str); i++)
        if(s->Data[i] == str[i] && i == strlen(str)-1) return 1;

    return 0;
}

long __EndsWith(String *s, const char *str) {
    if(s->Data[strlen(s->Data) - 1] != str[strlen(str) -1] && s->Data[strlen(s->Data) - 2] != str[strlen(str) - 2]) return 0;

    long counter = strlen(s->Data)-1;
    for(int i = strlen(str)-1; i < strlen(str); i--)
        if(s->Data[counter--] == str[i] && i == 0) 
            return (long)1;

    return (long)0;
}

long __IsLowercase(String *s) {
    for(int i = 0; i < strlen(s->Data); i++)
        if(!islower(s->Data[i]) && s->Data[i] != ' ') 
            return 0;

    return 1;
}

int __IsUppercase(String *s) {
    for(int i = 0; i < strlen(s->Data); i++)
        if(!isupper(s->Data[i]) && s->Data[i] != ' ') 
            return 0;

    return 1;
}

int __RmChar(String *s, const char chr) {
    char *new = (char *)malloc(strlen(s->Data) + 1);
    memset(new, '\0', strlen(s->Data) + 1);
    int found = 0;

    for(int i = 0; i < strlen(s->Data); i++) {
        if(s->Data[i] != chr) {
            strncat(new, &s->Data[i], sizeof(char));
	        found++;
	    }
    }
    __updateString(s, new);
    return found;
}

long __Replace(String *s, char *substr, char *replacement) {
    char* data = (char *)malloc(strlen(s->Data) + 1);
    long found = 0;
    if(strlen(replacement) > strlen(substr))
        data = (char *)realloc(data, (strlen(s->Data) - strlen(substr) + strlen(replacement) + 1) );

    memset(data, '\0', strlen(s->Data) + 1);

    for(int i = 0; i < strlen(s->Data); i++) {
        if(substr[0] == s->Data[i] && substr[1] == s->Data[i+1] && substr[strlen(substr) - 1] == s->Data[i + strlen(substr) - 1]) {
            strcat(data, replacement);
            i += strlen(substr);
		    found++;
        }
        strncat(data, &s->Data[i], sizeof(char));
    }

    __updateString(s, data);
    return found;
}

char **__SplitChar(String *s, char delim) {
	long sz = __CountChar(s, delim);
	char **arr = (char **)calloc(sz + 1, sizeof(char *));
	arr[0] = (char *)malloc(sizeof(char *) * (strlen(s->Data) / 4));
	memset(arr[0], '\0', (strlen(s->Data) / 4));

	int idx = 0;
	for(int i = 0; i < strlen(s->Data); i++) {
		if(s->Data[i] == delim) {
			idx++;
			arr[idx] = (char *)malloc(sizeof(char *) * (strlen(s->Data) - i));
			memset(arr[idx], '\0', (strlen(s->Data) - i));
			continue;
		}

		strncat(arr[idx], &s->Data[i], sizeof(char));
	}
	arr[idx+1] = '\0';

	return arr;
}

void __updateString(String *s, char *new_data) {
    if(s->Data != NULL || strlen(s->Data) > 0)
        free(s->Data);

    s->Data = strdup(new_data);
}

char *get_va_arg_str(va_list a) {
	char *arg = (char *)va_arg(a, char*);
	return  arg;
}

char get_va_arg_char(va_list a) {
	char arg = (char)va_arg(a, int);
	return arg;
}