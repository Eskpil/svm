#include "./bytecode.h"

void bytecode_read(Svm *svm, const char *file_path) {

    memset(svm, 0, sizeof(*svm));

    fprintf(stdout, "[Info] starting reading process for bytecode file: %s\n", file_path);

    FILE *file = fopen(file_path, "rb");

    if (file == NULL) {
        fprintf(stderr, "[Error] Could not open file because %s\n", strerror(errno));
        exit(1);
    };

    Bytecode_Metadata meta = {0};

    size_t n = fread(&meta, sizeof(meta), 1, file);

    if (n < 1) {
        fprintf(stderr, "[Error] could not read the metadata because %s\n", strerror(errno));
        exit(1);
    };

    if (meta.magic != BYTECODE_MAGIC) {
        fprintf(stderr, "[Error] invalid bytecode magic: %d bytecode magic is: %d\n", meta.magic, BYTECODE_MAGIC);    
        exit(1);
    }

    if (meta.version != BYTECODE_VERSION) {
        fprintf(stderr, "[Error] invalid bytecode version: %d supported versions are: %d\n", meta.version, BYTECODE_VERSION);
        exit(1);
    }

    if (meta.program_size > PROGRAM_CAP) {
        fprintf(stderr, "[Error] programs program size execeds limit set by vm");
        exit(1);
    };

    svm->ip = meta.entry;

    svm->program_size = fread(svm->program, sizeof(svm->program[0]), meta.program_size, file);

    if (svm->program_size != meta.program_size) {
        fprintf(stderr, "[Error] %s: read %lu program instructions but expected %lu", strerror(errno), svm->program_size, meta.program_size);
        exit(1);
    };

    fclose(file);
}
