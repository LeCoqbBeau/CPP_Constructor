# CPP_Constructor
#### by LeCoqBeau _& Palsfreniers_

---

## Brief Presentation

> CPP_Constructor automatize the creations of Canonical Orthodox Classes.

---

## Why CPP_Constructor exists

> CPP_Constructor is a project I made because it is really annoying to write
> dozens of Canonical Orthodox Classes.
> 
> This **programs** allows you to **create** both .h and .cpp files at any moment.
> 
> You can choose the Classes **attributes**, if it should be **protected** or **private**, if you want
> constructors **call statements**, what **libraries** to include...
> 
> **Mostly, you can creates multiples classes at the same time!!!**

---
## Installation

> to install this to your prefix:

debian : 
```Bash
$ apt-get install binutils g++ make
```

arch :
```Bash
pacman -Su binutils g++ make
```

> then to install CPP_constructor

```Bash
$ git clone https://github.com/LeCoqbBeau/CPP_Constructor
$ cd CPP_Constructor
$ make install PREFIX=<prefix> # default prefix is /usr/bin
```

---
## Launching CPP_Constructor

> 1. **Build** the **program** using `make`
>    - If you'd like, you can `make install PREFIX=<wanted path>`
>    to make it runnable from everywhere on your pc
> 2. **Acknowledge** all the **options** before **running** the **program**:
> ```Bash
>   -i          | --invert          : will write private/protected attributes first in header files
>   -p <prefix> | --prefix <prefix> : set custom prefix for variable names
>   -d          | --pragma          : set header protection to use pragma instead of ifndef
>   -l          | --lib             : add common CPP libraries into all headers
>   -c          | --color           : exports an color library, and makes '-a' statements colored
>   -a          | --announce        : add announcement statement to constructors, operators, and destructor
>   -o <dir>    | --output <dir>    : changes the output directory
> ```
> 3. **_Profit!_**

---
## Usage

> Once **CPP_Constructor** has been ran, a shell will be started.
> 
> **Please take note that no command takes parameters.**

> Here is the list of all commands for the **Main-Shell**:
>  - `help`: Prints a list of all available commands with a brief description
>  - `exit`: Exits the program
>  - `create`: Creates a Class
>    - Display a prompt asking for a class name to create a class.
>    - The inputted name will be automatically formatted to CamelCase
>  - `print`: Display all classes with their attributes name
>  - `edit`: Starts an other shell to edit a Class
>    - Display a prompt asking for a class name to edit
>    - It will start an other shell editing the class
>    - The inputted name will not be formatted to CamelCase
>  - `cne`: Creates and Edit a Class
>    - Display a prompt asking for a class name to create a class.
>    - Edits the last **created** class.
>    - **Failing** to create the class will still edit the **last created class**
>  - `export`: Creates an ___output___ directory and creates all files for all loaded classes.

> Here is the list of all commands for the **Class-Shell**:
>  - `help`: Prints a list of all available commands with a brief description
>  - `exit`: Returns to the **Main-Shell**
>  - `add`: Creates a new attribute for the currently edited class
>    - Display a prompt asking for the new attribute's type
>    - Display a prompt asking for the new attribute's name
>  - `print`: Prints the current class and all of its attribute in a cleaner way
>  - `edit`: Edit one attribute of the currently edited class
>    - Display a prompt asking for the attribute's name
>    - Then asks for if the user wants to modify the Name or the Type
>    - Display a prompt asking for the modified value.
>  - `prot`: Makes all the class attributes protected instead of private
>  - `include`: Adds libraries to be included in the Class's header file
>    - Display a prompt asking for the library name.
>    - Asks the user if the library is global (<global.h>) or local ("local.h")
