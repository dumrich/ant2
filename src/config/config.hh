#ifndef CONFIG_H
#define CONFIG_H

/* Edit at your own risk */
#define NUM_THREADS 3
#define GAP_SIZE 128

/* Edit at your comfort */
#define SYNTAX_HIGHLIGHTING 1
#define PROJECT_ROOT "git"

// Anything less than this will be slurped
#define SLURP_LENGTH 500000

enum BufferType {
    PYTHON,
    CPP,
    C,
    JAVA,
    RUST,
    TEXT,
};

struct BufferAssociation {
    const char* ext;
    BufferType type;
};

const BufferAssociation buffer_associations[] = {
    {".py", PYTHON},
    {".cpp", CPP},
    {".cc", CPP},
    {".hpp", CPP},
    {".hh", CPP},
    {".c", C},
    {".h", C},
    {".java", JAVA},
    {".rs", RUST},
    {"*", TEXT},
};

#endif
