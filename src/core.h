#ifndef CORE_H
#define CORE_H

/* IC's Built-in */
#include "global.h"
#include "types.h"
#include "../iclibs/file/file.h"
#include "../iclibs/ic/string/str.h"

/* Parser Lib */
#include "parser/structs.h"
#include "parser/variables.h"
#include "parser/functions.h"

typedef struct ImprovedC {
	char 	*Filepath;
	char 	**src_files;

	/* Current Settings/Check Values */
	File 	*src_file;
} ImprovedC;

ImprovedC *parse();

#endif