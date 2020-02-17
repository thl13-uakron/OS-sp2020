int stringEquals(char*, char*);
void parseArguments(char*, char*, char**);
void handleCommand(char*, char**);
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
  char args[8][24];
  while (1) {
    interrupt(33, 0, "~(_^> \0", 0, 0);
    interrupt(33, 1, buffer, 0, 0);
    parseArguments(buffer, command, args);
    handleCommand(command, args);
  }
}

int stringEquals(char* c1, char* c2) {
  /* returns 1 if strings match, 0 otherwise */
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

void handleCommand(char* command, char** args) {
  /* execute system calls based on contents of command and arguments */
  if (stringEquals(command, "boot\0") == 1) {
    boot();
  }
  else if (stringEquals(command, "clrs\0") == 1) {
    clrs();
  }
  else {
    interrupt(33, 0, "bad command or file name\r\n\0");
  }
}

void parseArguments(char* buffer, char* command, char** args) {
  /* split input into command and arguments */
  int bufferIndex = 0;
  int argCharIndex = 0;
  int argStrIndex = 0;

  /* copy characters from buffer to argument until encountering whitespace */
  while(buffer[bufferIndex] != ' ' && buffer[bufferIndex] != '\0') {
    command[bufferIndex] = buffer[bufferIndex];
    bufferIndex = bufferIndex + 1;
  }
  command[bufferIndex] = '\0';

  while (buffer[bufferIndex] != '\0') {
    /* copy characters from buffer to argument until encountering whitespace */
    while (buffer[bufferIndex] != ' ' && buffer[bufferIndex] != '\0') {
      args[argStrIndex][argCharIndex] = buffer[bufferIndex];
      ++bufferIndex;
      ++argCharIndex;
    }
    /* move to next argument */
    args[argStrIndex][argCharIndex] = '\0';
    ++argStrIndex;
    argCharIndex = 0;
  }
}

void boot() {
  /* reboot system through interrupt 0d25 (0x19) */
  interrupt(25, 0, 0, 0, 0);
}

void clrs() {
  /* clear screen through interrupt 0d33 (0x21) */
  interrupt(33, 12, 0, 0, 0);
}
