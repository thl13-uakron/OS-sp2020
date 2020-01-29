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
void clearScreen();
void readString(char*);
int mod(int, int);
int div(int, int);

void main()
{
   char input[256];

   makeInterrupt21();
   printLogo();
   interrupt(33, 0, "Hello world from Thomas.\r\n\0", 1, 0);

   /* run test function for user input */
   interrupt(33, 0, "Enter a string: \0", 0, 0);
   readString(input);
   interrupt(33, 0, "\nYou entered: \0", 0, 0);
   interrupt(33, 0, input, 0, 0);

   while(1); /* stop program by putting in an infinite loop */
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
   interrupt(33, 0, " Author(s): Thomas Li.\r\n\r\n\0",0, 0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */
void clearScreen() {
  /* do a carriage return on 24 lines to clear them */
  int i = 0;
  while (i < 24) {
    interrupt(33, 0, "\r\n\0", 0, 0); /* clear line */
    i = i + 1; /* move to next line */
  }
}

void readString(char* c) {
  int i = 0; /* index to store character */
  char enter = 13; /* ascii code of enter character */
  char backspace = 8; /* ascii code of backspace character */

  /* record input */
  char* input;
  input[1] = '\0';

  while (1) {
    /* take and print character from keyboard input */
    input[0] = interrupt(22, 0, 0, 0, 0);
    interrupt(33, 0, input, 0, 0);

    /* terminate input loop if enter is pressed */
    if (input[0] == enter) {
      /* append null character to string */
      c[i] = '\0';
      break;
    }
    else {
      /* record character to string otherwise */
      c[i] = input[0];

      /* move to next index unless backspace is pressed */
      if (c[i] == backspace) {
        /* decrement index if backspace is pressed unless index is 0 */
        if (i > 0) i = i - 1;
      }
      else {
        i = i + 1;
      }
    }
  }

  return;
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
        break;
/*      case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: case 13: case 14: case 15: */
      default: interrupt(33, 0, "General BlackDOS error.\r\n\0", 0, 0);
   }
}
