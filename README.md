# Pima CC CIS265 Week #3 Project A
## Decimal to Octal Conversion

Write a program that reads an integer entered by the user and displays it in octal (base 8):
```text
  Enter a number between 0 and 32767: 1953
  In Octal, your number is: 03641
```
The output should be displayed using 5 digits, even if fewer digits are sufficient. Hint: To convert the number to octal, first divide it by 8; the remainder is the last digit of the octal number (1, in this case). Then divide the original number by 8 and repeat the process to arrive at the next-to-last digit. (printf is capable of displaying numbers in base 8, as we’ll see in Chapter 7, so there’s actually an easier way to write this program).

The program uses a recursive version of the following decimal-to-octal conversion algorithm:
```C
  int octal(int d) 
  {
    int remainder, n = 0;
    
    while (d > 0) 
    {
      remainder = d % 8;
      n = n*10 + remainder;
      d /= 8;
    }
    
    return n;
  }
```

Notes:
*  Beware, the conversion function uses a recursive algorithm!
