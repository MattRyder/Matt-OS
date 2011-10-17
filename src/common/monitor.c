/*
 * monitor.c - Monitor writing and clearing
 */

#include "../includes/monitor.h"

int cursor_x = 0; int cursor_y = 0;
u16int* video_memory = (u16int*)0xb8000;

static void move_cursor()
{
  u16int cursor_location = ( cursor_y * 80 + cursor_x );

  outb(0x3D4, 14);
  outb(0x3D5, cursor_location >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, cursor_location);
}

static void scroll()
{
  //Char to fill the scroll with:
  u8int att_byte = (0 << 4) |  (15 & 0x0F);
  u16int blank_char = 0x20 | (att_byte << 8);

  //Trying to go over the 25th line, so let's scroll up:
  if( cursor_y >= 25 )
  {
    int i=0;
    for(i = 0 * 80; i < 24 * 80; i++)
    {
      //Budge everything onscreen a line back
      video_memory[i] = video_memory[i+80];
    }

    int j=0;
    for(j= 24 * 80; j < 25 * 80; j++)
    {
      //Overwrite the last line blank:
      video_memory[j] = blank_char;
    }

    //Put the cursor on the last line:
    cursor_y = 24;
  }
}

void k_putc(char c)
{
  //Now set up the byte's attributes from the above:
  u8int att_byte = (0 << 4) | (15 & 0xF);

  //Stick that in the higher half of the short:
  u16int attribute = att_byte << 8;
  u16int* location;

  //If the char's a backspace, move the cursor back one place:
  if( c == 0x08 && cursor_x )
  {
    cursor_x--;
  }
  else if( c == 0x09 )
  {
    cursor_x = ( cursor_x+8 ) & ~(8-1);
  }
  else if( c == '\r' )
  {
    cursor_x = 0;
  }
  else if( c == '\n' )
  {
    cursor_x = 0;
    cursor_y++;
  }
  else if( c >= ' ' )
  {
    location = video_memory + (cursor_y * 80 + cursor_x);
    *location = attribute | c;
    cursor_x++;
  }

  //Do we need a newline from hitting the EOL?
  if( cursor_x >= 80 )
  {
    cursor_x = 0;
    cursor_y++;
  }

  //Perform any scrolling proceedure:
  scroll();

  //Move the cursor:
  move_cursor();

}

void k_monitorclear()
{
  u8int attrib_byte = (0 << 4) | (15 & 0x0F);
  u16int blankc = (attrib_byte << 8) | 0x20;

  int i=0;
  for(i = 0; i < 80*25; i++)
  {
    video_memory[i] = blankc;
  }

  cursor_x = 0;
  cursor_y = 0;
  move_cursor();
}

void k_puts(char* c)
{
  int i = 0;
  while( c[i] )
  {
    k_putc( c[i++] );
  }
}

void k_colorchar(char c, u8int attribute)
{
  //Stick that in the higher half of the short:
  u16int xattribute = attribute << 8;
  u16int* location;

  //If the char's a backspace, move the cursor back one place:
  if( c == 0x08 && cursor_x )
  {
    cursor_x--;
  }
  else if( c == 0x09 )
  {
    cursor_x = ( cursor_x+8 ) & ~(8-1);
  }
  else if( c == '\r' )
  {
    cursor_x = 0;
  }
  else if( c == '\n' )
  {
    cursor_x = 0;
    cursor_y++;
  }
  else if( c >= ' ' )
  {
    location = video_memory + (cursor_y * 80 + cursor_x);
    *location = xattribute | c;
    cursor_x++;
  }

  //Do we need a newline from hitting the EOL?
  if( cursor_x >= 80 )
  {
    cursor_x = 0;
    cursor_y++;
  }

  //Perform any scrolling proceedure:
  scroll();

  //Move the cursor:
  move_cursor();

}

void k_colorstring(char* s, u8int attribute)
{
  int i = 0;
  while( s[i] )
  {
    k_colorchar(s[i++], attribute);
  }
}
