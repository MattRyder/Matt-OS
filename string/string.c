#include "../includes/string.h"
#include "../includes/stdargs.h"
#include "../includes/monitor.h"

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
    k_putc('0'); //Handle basic 0 case.
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
    k_putc(nCharIndex[j]);
  }
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
	  k_putc('%');
	  break;
	case 'c':
	  k_putc(va_arg(ap, s8int));
	  break;
	case 's':
	  k_puts(va_arg(ap, s8int*));
	  break;
	case 'i':
	  kitoa(va_arg(ap, s32int));
	  break;
	default:
	  kprintf("printf: Unknown escape char: %c", printf_format[offset+1]);
      }
      offset += 2;
    }
    else
    {
      k_putc(printf_format[offset]);
      offset++;
    }

  }

  va_end(ap); //End the va_list:
}

