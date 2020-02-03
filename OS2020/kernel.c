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
int mod(int, int);
int div(int, int);

void main()
{
   /*char input[256];
   int* n;

   /*
   makeInterrupt21();
   printLogo();
   interrupt(33, 0, "Hello world from Thomas and Geetha.\r\n\0", 1, 0);

   /* run test function for user input */
   /*interrupt(33, 0, "Enter a string: \0", 0, 0);
   interrupt(33, 1, input, 0, 0);
   interrupt(33, 0, "\r\nYou entered: \0", 0, 0);
   interrupt(33, 0, input, 0, 0);*/

   /* run test function for reading and writing ints */
   /*
   interrupt(33, 0, "\r\n\nEnter an integer: \0", 0, 0);
   interrupt(33, 14, n, 0, 0);
   interrupt(33, 0, "\r\nThe integer you entered is \0", 0, 0);
   interrupt(33, 13, *n, 0, 0);
   interrupt(33, 0, "\r\nDouble the integer you entered is \0", 0, 0);
   interrupt(33, 13, *n * 2, 0, 0);

   /*
   while(1); /* stop program by putting in an infinite loop */

   char food[25], adjective[25], color[25], animal[25];
   int temp;
   makeInterrupt21();
   printLogo();
   interrupt(33,0,"\r\nWelcome to the Mad Libs kernel.\r\n\0",0,0);
   interrupt(33,0,"Enter a food: \0",0,0);
   interrupt(33,1,food,0,0);
   temp = 0;
   while ((temp < 100) || (temp > 120)) {
      interrupt(33,0,"Enter a number between 100 and 120: \0",0,0);
      interrupt(33,14,&temp,0,0);
   }
   interrupt(33,0,"Enter an adjective: \0",0,0);
   interrupt(33,1,adjective,0,0);
   interrupt(33,0,"Enter a color: \0",0,0);
   interrupt(33,1,color,0,0);
   interrupt(33,0,"Enter an animal: \0",0,0);
   interrupt(33,1,animal,0,0);
   interrupt(33,0,"Your note is on the printer, go get it.\r\n\0",0,0);
   interrupt(33,0,"Dear Professor O\'Neil,\r\n\0",1,0);
   interrupt(33,0,"\r\nI am so sorry that I am unable to turn in my program at this time.\r\n\0",1,0);
   interrupt(33,0,"First, I ate a rotten \0",1,0);
   interrupt(33,0,food,1,0);
   interrupt(33,0,", which made me turn \0",1,0);
   interrupt(33,0,color,1,0);
   interrupt(33,0," and extremely ill.\r\n\0",1,0);
   interrupt(33,0,"I came down with a fever of \0",1,0);
   interrupt(33,13,temp,1,0);
   interrupt(33,0,". Next my \0",1,0);
   interrupt(33,0,adjective,1,0);
   interrupt(33,0," pet \0",1,0);
   interrupt(33,0,animal,1,0);
   interrupt(33,0," must have\r\nsmelled the remains of the \0",1,0);
   interrupt(33,0,food,1,0);
   interrupt(33,0," on my computer, because he ate it. I am\r\n\0",1,0);
   interrupt(33,0,"currently rewriting the program and hope you will accept it late.\r\n\0",1,0);
   interrupt(33,0,"\r\nSincerely,\r\n\0",1,0);
   interrupt(33,0,"Thomas and Geetha\r\n\0",1,0);
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
/*      case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: */
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
