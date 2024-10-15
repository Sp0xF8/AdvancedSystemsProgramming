# Worksheet 0: Advanced Systems Programming

## Content
This worksheet involved setting up the c++ envrioment and creating a basic hello world, and expermineting by creating a tic-tac-toe game: allowing users to select a position on a square and the move will be placed. After each placement, Win conditions should be checked. 

## Hello World: Intro
### Everyones first program.

```cpp
#include <iostream>

int main() {
    std::cout << "This is a simple hello world program! " << std::endl;
    return 0;
}
```

This simple program serves as an example as to the most simple execution of a test application. In c++, it demonstrates a working compiler, successful execution and correctly functioning input-output.

### Breaking it down

Including a libary:
C++ comes pre-packed with tons of libraries: referred to as the Standard Includes. These are libraries which are not needed to be manually linked to the compiler.

```cpp
#include <iostream>
```

IOStream is one of these libraries. This library in particular allows the developer to interact with the console input and output functions:

```cpp

std::cin; //taking input from user

std::cout; //display output

std::endl; //ending the current line, similar to pressing enter in word

```


The **main** function:

```cpp
int main();
```
This is the function which is recognised by the compiler as the standard "Entry point" for an executable file. 

All functions in C++ must be defined with a type. The **main** function is no exception. Here, the declaration states that it is an Interger function: meaning it returns an Integer, also known as a whole number. Given the way C++ records standard **Int***s*, this is a signed number. This means it can return **ratonal positive** *and* **negative** values.

Example definition can be seen below:
```cpp
int main()
{
    return 0; //exit code 0 commonly referring to a successful execution
}
```

finally, putting it together we have a "**Hello world**" program. 

```cpp
#include <iostream> //include the std input output stream libary

int main() { //begin int main definition

    std::cout << "This is a simple hello world program! " << std::endl; // displaying message, then ending the line

    return 0; // return 0 to indicate a successful indication.
}
```


## Tic-Tac-Toe: Minigame

### Declarations

#### Moves Enum

In tic-tac-toe, the moves are one of two. Placing an **X** or an **O** in an empty square. Defining our ***Enum*** structure, **Move**, we can easily keep track of possible values using constant expressions.

```cpp
enum class Move : char {
    EMPTY = ' ',
    X = 'X',
    O = 'O', 
};
```

Reading through this line-by-line, we are setting creating an enum class named **Move**: using a char as the base value type. An enum is a special type of structure allowing developers to hold multiple options for a variable.

Inside this structure, there are three options: *empty*, *X*, or *O*. As the structure only accepts char elements, these are refernced as
```cpp
EMPTY = ' ',
X = 'X',
O = 'O',
```

#### Board Structure

Next up, the playing board. 

```cpp
struct Board {

    Move possibleMoves[3][3];

    Board();

};
```

Lets break this down. A struct is a developer designed data structure, similar to an Enum. This allows the developer to hold multiple variables and functions relating to these variables.

The only variable stored inside this structure is a 4x4, 2-Dimensional array. It also only has one function, the constructor.

```cpp
Board::Board(){

    for (int y = 0; y <3; y++ ){
        for (int x = 0; x <3; x++ ){

            this->possibleMoves[x][y] = Move::EMPTY;
        }
    }
}
```
Looking at the definition, we can see that this simply just initialises the array to hold only empty moves.




## Conclusion
Summarize the key takeaways and any additional resources.