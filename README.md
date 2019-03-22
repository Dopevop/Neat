## Compiling

To compile `neat.cpp` into the runnable `neat`, use the
command:

```g++ -o neat neat.cpp```

## Running

The resulting program `neat` takes either 2 or 3 arguments.
Giving it any other number of arguments will result in the
following Usage statement:

```Usage: ./neat <file> [max width]```

Call neat by typing `./neat` and giving it as an argument
the path to a text file:

```./neat mytext.txt```

## Output

The formatted solution, aligned ever so perfectly, will be
written to a file called "output.txt" in the same directory
as the program.

## Options

You can pass a second, integer parameter to specify the max
line width (default=60):

```./neat mytext.txt 10```

