int stringEquals(char*, char*);
void parseArguments(char*, char*, char**, int);
void handleCommand(char*, char**, int, char*);
void clearBuffer(char*, int);
void boot();
void clrs();
void echo(char*);
void copy(char*, char*);
void ddir();
void exec(char*);
void help();
void prnt(char*);
void remv(char*);
void senv();
void show(char*);
void twet(char*);

void main() {
  char buffer[512];
  char command[5];
  char argv[8][32];
  int *argc;
  char config[2];

  /* read configuration settings */
  interrupt(33, 2, config, 258, 1);
  config[0] += 1;
  config[1] += 1;

  while (1) {
    interrupt(33, 0, "\r\n~(_^> \0", 0, 0);
    interrupt(33, 1, buffer, 0, 0);
    parseArguments(buffer, command, argv, argc);
    handleCommand(command, argv, argc, config);
  }
}

int stringEquals(char* c1, char* c2) {
  /* returns 1 if strings match,
    argv[argStrIndex] = ""; 0 otherwise */
  int index = 0;
  while (c1[index] != '\0' && c2[index] != '\0') {
    /* compare characters until at least one string terminates */
    if (c1[index] != c2[index]) return 0;
    index = index + 1;
  }
  /* if only one string has terminated, they are not considered matching */
  if (c1[index] != '\0' || c2[index] != '\0') return 0;
  return 1;
}

void handleCommand(char* command, char** argv, int* argc, char* config) {
  /* execute system calls based on contents of command and arguments */
  if (stringEquals(command, "boot\0") == 1) {
    boot();
  }
  else if (stringEquals(command, "clrs\0") == 1) {
    clrs(config);
  }
  else if (stringEquals(command, "echo\0") == 1) {
    if (*argc > 0) {
      echo(argv[0]);
    }
  }
  else if (stringEquals(command, "copy\0") == 1) {
    copy(argv[0], argv[1]);
  }
  else if (stringEquals(command, "ddir\0") == 1) {
    ddir();
  }
  else if (stringEquals(command, "exec\0") == 1) {
    exec(argv[0]);
  }
  else if (stringEquals(command, "help\0") == 1) {
    help();
  }
  else if (stringEquals(command, "prnt\0") == 1) {
    prnt(argv[0]);
  }
  else if (stringEquals(command, "remv\0") == 1) {
    remv(argv[0]);
  }
  else if (stringEquals(command, "senv\0") == 1) {
    senv();
  }
  else if (stringEquals(command, "show\0") == 1) {
    show(argv[0]);
  }
  else if (stringEquals(command, "twet\0") == 1) {
    twet(argv[0]);
  }
  else {
    interrupt(33, 0, "bad command or file name\0");
  }
}

void parseArguments(char* buffer, char* command, char** argv, int* argc) {
  /* split input into command and arguments */
  int bufferIndex = 0;
  int argCharIndex = 0;
  int argStrIndex = 0;
  *argc = 0;

  /* copy characters from buffer to command string until encountering whitespace */
  while(buffer[bufferIndex] != ' ' && buffer[bufferIndex] != '\0') {
    command[bufferIndex] = buffer[bufferIndex];
    bufferIndex = bufferIndex + 1;
  }
  command[bufferIndex] = '\0';
  ++bufferIndex;

  while (buffer[bufferIndex] != '\0') {
    /* clear existing contents of argument string */
    clearBuffer(argv[argStrIndex], 32);

    /* copy characters from buffer to argument string until encountering whitespace */
    while (buffer[bufferIndex] != ' ' && buffer[bufferIndex] != '\0') {
      argv[argStrIndex][argCharIndex] = buffer[bufferIndex];
      ++bufferIndex;
      ++argCharIndex;
    }

    /* move to next argument */
    argv[argStrIndex][argCharIndex] = '\0';
    ++bufferIndex;
    ++argStrIndex;
    argCharIndex = 0;
  }

  /* clear input buffer */
  clearBuffer(buffer, 512);
}

void clearBuffer(char* buffer, int length) {
  int index = 0;
  while (index < length) {
    buffer[index] = '\0';
    ++index;
  }
}

void boot() {
  /* reboot system through interrupt 0d25 (0x19) */
  interrupt(25, 0, 0, 0, 0);
}

void clrs(char* config) {
  /* clear screen through interrupt 0d33 (0x21) */
  interrupt(33, 12, config[0], config[1], 0);
}

void echo(char* comment) {
  /* print comment on screen */
  interrupt(33, 0, comment, 0, 0);
}

/* commands that are recognized but aren't implemented yet */

void copy(char* file1, char* file2) {
  interrupt(33, 0, "Recognized command: copy\r\n\0", 0, 0);
  interrupt(33, 0, "Arguments: ", 0, 0);
  interrupt(33, 0, file1, 0, 0);
  interrupt(33, 0, ", ", 0, 0);
  interrupt(33, 0, file2, 0, 0);
}

void ddir() {
  interrupt(33, 0, "Recognized command: ddir\0", 0, 0);
}

void exec(char* filename) {
  interrupt(33, 0, "Recognized command: exec\r\n\0", 0, 0);
  interrupt(33, 0, "Arguments: ", 0, 0);
  interrupt(33, 0, filename, 0, 0);
}

void help() {
  interrupt(33, 0, "Recognized command: help\0", 0, 0);
}

void prnt(char* filename) {
  interrupt(33, 0, "Recognized command: prnt\r\n\0", 0, 0);
  interrupt(33, 0, "Arguments: ", 0, 0);
  interrupt(33, 0, filename, 0, 0);
}

void remv(char* filename) {
  interrupt(33, 0, "Recognized command: remv\r\n\0", 0, 0);
  interrupt(33, 0, "Arguments: ", 0, 0);
  interrupt(33, 0, filename, 0, 0);
}

void senv() {
  interrupt(33, 0, "Recognized command: senv\0", 0, 0);
}

void show(char* filename) {
  interrupt(33, 0, "Recognized command: show\r\n\0", 0, 0);
  interrupt(33, 0, "Arguments: ", 0, 0);
  interrupt(33, 0, filename, 0, 0);
}

void twet(char* filename) {
  interrupt(33, 0, "Recognized command: twet\r\n\0", 0, 0);
  interrupt(33, 0, "Arguments: ", 0, 0);
  interrupt(33, 0, filename, 0, 0);
}
