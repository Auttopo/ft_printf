*This project has been created as part of the 42 curriculum by abenabde.*




# `ft_printf`

Project archived library : `ft_printf.a`
Project header : `ft_printf.h`

Prototype : `int ft_printf(const char *input, ...)`




## Description:

`ft_printf` is a reproduction of printf but in a simple way, coded in C.
The function takes an input string with optional format specifiers inside, with their needed references as parameters, and outputs the result to `fd 1` (standard output).

### Return value:
The return value is the number of characters written, or -1 on error.




## Instructions:

The project was developed with a Makefile. You can use the archive `ft_printf.a` created with the command `make`, or use the source files directly. Both ways need to include `ft_printf.h`.


Only the following format specifiers are functional:

• %c Prints a single character: (char)

• %s Prints a string: (char *)

• %p Prints a pointer address in hexadecimal format: (void *)

• %d Prints a decimal (base 10) number: (int)

• %i Prints an integer in base 10: (int)

• %u Prints an unsigned decimal (base 10) number: (unsigned int)

• %x Prints a number in hexadecimal (base 16) lowercase format: (unsigned int)

• %X Prints a number in hexadecimal (base 16) uppercase format: (unsigned int)

• %% Prints a percent sign.


### Example of usage:
`
int main(void)
{
    int num = 8;
    ft_printf("the %d value is stored at %p address\n", num, &num);

    return (0);
}
`
Output:
`the 8 value is stored at 0x7ffc0f11e31c address`




## Algorithm:

`ft_printf` writes the string until it encounters a '%'. When it does, it takes the next character and operates depending on it, then continues through the string the same way. The return value is set to the number of characters written.




## Resources:


### Technical references

Linux manual page for `printf()` `va_arg()` `write()`
GNU C Library documentation
GNU Make documentation
42 subject PDF `ft_printf`


### Libraries used:

- unistd.h
- stdarg.h
- stdlib.h

