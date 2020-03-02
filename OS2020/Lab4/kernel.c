/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:_________Thomas Li________________ Date:___1/22/2020____        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.03, Fall 2019.               */

void handleInterrupt21(int,int,int,int);
void printLogo();
void clearScreen(int, int);
int mod(int, int);
int div(int, int);
void runProgram(int, int, int);

void main()
{
  char buffer[512];
  makeInterrupt21();
  interrupt(33, 2, buffer, 258, 1);
  interrupt(33, 12, buffer[0] + 1, buffer[1] + 1, 0);
  printLogo();
  runProgram(30, 4, 2);
  interrupt(33, 0, "Error if this executes.\r\n\0", 0, 0);
  while (1);
}

void printString(char* c, int d)
{
   /* calling interrupt 16 with AH set to the value 14 prints the character stored in AL */
   /* alternatively, calling interrupt 23 with AH set to 0 sends the character in AL to the printer */

   /* the interrupt used in this function depends on the value of d */
   /* interrupt 23 with function 0 is called if d is 1, interrupt 16 with function 14 is called otherwise */
   char ah = (d == 1 ? 0 : 14);

   /* repeat for each character in c to print the full string
   terminate upon encountering null character without printing it */
   int i = 0;
   while (c[i] != '\0') {
     char al = c[i];
     int ax = ah * 256 + al; /* set full value of ax register */

     if (d == 1) {
       /* call interrupt 23 if d set to 1 */
       interrupt(23, ax, 0, 0, 0);
     }
     else {
       /* call interrupt 16 otherwise */
       interrupt(16, ax, 0, 0, 0);
     }

     i = i + 1; /* move to next character */
   }

   return;
}

void printLogo()
{
   interrupt(33, 0, "       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0, 0);
   interrupt(33, 0, "      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0, 0);
   interrupt(33, 0, "     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0, 0);
   interrupt(33, 0, "    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0, 0);
   interrupt(33, 0, "   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0, 0);
   interrupt(33, 0, "._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0, 0);
   interrupt(33, 0, " BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0",0, 0);
   interrupt(33, 0, " Author(s): Thomas Li, Geetha Malempati.\r\n\r\n\0",0, 0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */
void clearScreen(int bx, int cx) {
  /* do a carriage return on 24 line */
  int i = 0;
  while (i < 24) {
    interrupt(33, 0, "\r\n\0", 0, 0); /* clear line */
    i = i + 1; /* move to next line */
  }
  interrupt(16, 512, 0, 0, 0); /* reposition cursor to coordinates (0, 0) */
  if (cx > 0 && bx > 0) {
    /* change color scheme based on bx and cx */
    interrupt(16, 1536, 4096 * (bx - 1) + 256 * (cx - 1), 0, 6223);
  }
}

void readString(char* c) {
  int i = 0; /* index to store character */
  char enter = 13; /* ascii code of enter character */
  char backspace = 8; /* ascii code of backspace character */

  /* record input */
  char input;

  while (1) {
    /* take and print character from keyboard input */
    input = interrupt(22, 0, 0, 0, 0);
    if (!(input == backspace && i <= 0)) {
      interrupt(16, (14 * 256) + input, 0, 0, 0);
    }

    /* terminate input loop if enter is pressed */
    if (input == enter) {
      /* append null character to string */
      c[i] = '\0';
      /* print carriage return and line feed */
      interrupt(16, (14 * 256) + '\r', 0, 0, 0);
      interrupt(16, (14 * 256) + '\n', 0, 0, 0);

      break;
    }
    else {
      /* record character to string otherwise and move to next index unless backspace is pressed */
      if (input == backspace) {
        /* decrement index if backspace is pressed unless index is 0 */
        if (i > 0) i = i - 1;
      }
      else {
        c[i] = input;
        i = i + 1;
      }
    }
  }

  return;
}

int mod(int a, int b) {
  /* compute the value of x % y */
  int result = a;
  while (result >= b) result = result - b;
  return result;
}

int div(int a, int b) {
  /* compute the value of a / b */
  int result = 0;
  if (b > 0) {
    while (result * b <= a) result = result + 1;
    if (result * b > a) result = result - 1;
  }
  return result;
}

void readInt(int* n) {
  char c[256];
  int i = 0;
  *n = 0;

  /* read a string and convert it to an int */
  interrupt(33, 1, c, 0, 0);
  while (c[i] != '\0') {
    *n = *n * 10; /* shift current digits to the left by 1 */
    *n = *n + (c[i] - '0'); /* convert character to digit and add */
    i = i + 1;
  }

  return;
}

void writeInt(int x, int d) {
  /* convert x to string and print */
  char c[6];
  int divisor = 1000;
  int modulo = 10000;
  int i = 0;

  if (x != 0) {
    /* each digit can be extracted by taking (x % 10^k) / 10^(k-1) for k in range (log(x) + 1, 1)*/
    /* assuming x does not equal 0*/

    /* account for x exceeding highest possible value of 10^k */
    if (x >= modulo) {
      c[i] = div(x, modulo) + '0';
      i = i + 1;
    }
    else {
      /* account for x being lower than initial value of 10^(k-1) */
      while (modulo > x * 10) {
        modulo = div(modulo, 10);
      }
      divisor = div(modulo, 10);
    }

    while (modulo >= 10) {
      c[i] = div(mod(x, modulo), divisor) + '0';
      i = i + 1;
      divisor = div(divisor, 10);
      modulo = div(modulo, 10);
    }
  }
  else {
    c[i] = '0';
    i = i + 1;
  }

  /* append null character */
  c[i] = '\0';
  interrupt(33, 0, c, d, 0);

  return;
}

void readSectors(char* buffer, int sector, int sectorCount) {
  /* calling interrupt 0d19 (0x13) with function 2 reads sectors from the floppy disk */
  int ah = 2;
  /* al holds number of sectors to read */
  int ax = (ah * 256) + sectorCount;

  int bx = buffer; /* bx holds address for storing read data */

  /* ch holds track number of starting point, cl holds relative sector number of starting point */
  int relSecNo = mod(sector, 18) + 1;
  int trackNo = div(sector, 36);
  int cx = (trackNo * 256 + relSecNo);

  /* dh holds head number of starting point, dl holds device number (0 in this case)*/
  int headNo = mod(div(sector, 18), 2);
  int dx = headNo * 256;

  interrupt(19, ax, bx, cx, dx);
}

void writeSectors(char* buffer, int sector, int sectorCount) {
  /* calling interrupt 0d19 (0x13) with function 3 writes sectors to the floppy disk */
  int ah = 3;
  /* al holds number of sectors to read */
  int ax = (ah * 256) + sectorCount;

  int bx = buffer; /* bx holds address for the data being written */

  /* ch holds track number of starting point, cl holds relative sector number of starting point */
  int relSecNo = mod(sector, 18) + 1;
  int trackNo = div(sector, 36);
  int cx = (trackNo * 256 + relSecNo);

  /* dh holds head number of starting point, dl holds device number (0 in this case)*/
  int headNo = mod(div(sector, 18), 2);
  int dx = headNo * 256;

  interrupt(19, ax, bx, cx, dx);
}

void runProgram(int start, int size, int segment) {
  int i = 0;

  /* load file from disk to buffer */
  char buffer[13312];
  interrupt(33, 2, buffer, start, size);

  /* get base location of segment */
  segment = segment * 4096;

  /* transfer file byte-by-byte from buffer to memory based on segment location */
  while (i < 13312) {
    putInMemory(segment, i, buffer[i]);
    ++i;
  }

  /* launch program file from memory */
  launchProgram(segment);
}

void stop() {
  while(1);
}
/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
/*   return; */
   /* handle calls of interrupt 0x21 (0d33) based on values in general-purpose registers */
   switch(ax) {
      case 0:
        /* if ax is 0, bx gets printed with cx determining if the output goes to the screen or the printer */
        printString(bx, cx);
        break;
      case 1:
        /* if ax is 1, a string is read from keyboard input and gets stored in bx */
        readString(bx);
        break;
      case 2:
        /* if ax is 2, dx sectors starting from sector cx are read into bx from the floppy disk */
        readSectors(bx, cx, dx);
        break;
      /*case 3: case 4: */
      case 5:
        /* if ax is 5, the program stops */
        stop();
        break;
      case 6:
        /* if ax is 6, dx sectors are read from bx to the floppy disk starting from sector number cx */
        writeSectors(bx, cx, dx);
        break;
      /*case 7: case 8: case 9: case 10: */
/*      case 11: */
      case 12:
        /* if ax is 12, the screen is cleared and the color scheme is changed based on the codes stored in bx and cx */
        clearScreen(bx, cx);
        break;
      case 13:
        /* if ax is 13, the bx gets printed as an integer with cx determining if the output goes to the screen or the printer */
        writeInt(bx, cx);
        break;
      case 14:
        /* if ax is 14, a string is read of keyboard input before being converted to an integer and stored in bx */
        readInt(bx);
        break;
      /*case 15: */
      default: interrupt(33, 0, "General BlackDOS error.\r\n\0", 0, 0);
   }
}
