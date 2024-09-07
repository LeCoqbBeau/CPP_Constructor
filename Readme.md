# CPP_Constructor
#### by LeCoqBeau

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

> uh yhea sure...

debian : `apt-get install binutils g++ make`

arch : `pacman -Su binutils g++ make`

---
## Usage

> 1. **Build** the **program** using `make`
>    - If you'd like, you can `make install PREFIX=<wanted path>`
>    to make it runnable from everywhere on your pc
> 2. **Acknowledge** all the **options** before **running** the **program**:
> ```
>   -i          | --invert          : will write private/protected attributes first in header files
>   -p <prefix> | --prefix <prefix> : set custom prefix for variable names
>   -d          | --pragma          : set header protection to use pragma instead of ifndef
>   -l          | --lib             : add common CPP libraries into all headers
>   -c          | --color           : exports an color library, and makes '-a' statements colored
>   -a          | --announce        : add announcement statement to constructors, operators, and destructor
> ```
> 3. ???
> 4. **_Profit!_**

---