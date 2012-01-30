#include "../includes/string.h"

void* memset(void *dest, int c, size_t size)
{
  while(size-- != 0)
    dest = &c;
  return dest;
}

void* memcpy(void *dest, void *src, size_t size)
{
  char* d = dest;
  char* s = src;
  while(size-- != 0)
    *d++ = *s++;
  return dest;
}

///Returns the length of the given string
int strlen(const char* str)
{
  const char* s;
  for(s = str; *s; ++s);
  return(s - str);
}

void kitoa(s32int n)
{
  s32int xN, i, j;
  u32int nCharIndex[11];

  if(n == 0) {
    kputc('0'); //Handle basic 0 case.
    return;
  }

  if((xN = n) < 0) {
    n = -n; //invert if neg
  }

  i = 0;
  do {
    nCharIndex[i++] = n % 10 + 48;
  } while((n /= 10) > 0);

  //append neg sign if reqd.
  if(xN < 0) {
    nCharIndex[i] = '-';
  } else {
    i--;
  }

  //output:
  for(j = i; j >= 0; j--) {
    kputc(nCharIndex[j]);
  }
}

char* kitohex(s32int n)
{
  char* dictionary = "0123456789ABCDEF";
  char* hexString = "";
  char hStr[20];
  int i = 0, j = 0, x = 0;

  if(n==0) { hStr[i++] = '0'; }

  do {
    hStr[i++] = dictionary[n % 16];
  } while((n /= 16) > 0);

  for(j = i-1; j >= 0; j--) {
    hexString[x++] = hStr[j];
  } hexString[x++] = '\0'; // Null terminate the string

  return hexString;
}

void kprintf(const s8int *printf_format, ...)
{
  va_list ap;
  va_start(ap, printf_format);

  u16int offset = 0;
  while(offset < strlen(printf_format))
  {
    if(printf_format[offset] == '%')
    {
      switch (printf_format[offset + 1])
      {
	case '%':
	  kputc('%');
	  break;
	case 'c':
	  kputc(va_arg(ap, s8int));
	  break;
	case 's':
	  kputs(va_arg(ap, s8int*));
	  break;
	case 'i':
	  kitoa(va_arg(ap, s32int));
	  break;
	case 'x':
	  kputs(kitohex(va_arg(ap, s32int)));
	  break;
	default:
	  kprintf("printf: Unknown escape char: %c", printf_format[offset+1]);
	  break;
      }
      offset += 2;
    }
    else
    {
      kputc(printf_format[offset]);
      offset++;
    }

  }
  va_end(ap); //End the va_list:
}
