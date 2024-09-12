# Project 3 Grading Criteria

This script is for checking 2 files: `p3.cpp`, `simulation.cpp`.

## Coding style [10 points]

#### clang-check [6 points]
* **Number of Subroutines** [2 point]
  Your program should be split into at least 6 non-main functions.

  1. 6 or more subroutines [2 points]
  2. 3-5 subroutine [1 point]
  3. 0-2 subroutine [0 point]

* **Length of functions** [2 point]

  Your main functions should be no longer than 100 lines and non-main functions should be no more than 100 lines.

  1. No long functions [2 point]
  2. 1 long functions [1 points]
  3. 2 or more long functions [0 points]

* **Body comments** [2 points]

  You should have your functions well commented. The length of function // the number of comments < 50.

  1. All function are well commented [2 points]
  2. 1 function are poorly commented [1 point]
  3. 2 function are poorly commented [0 points]

The total clang-check score will round **down** to the nearest integer, *i.e.* 3.5 will round down to 3.

#### clang-tidy [2 points]
* **Number of warning types** 1 points]
  1. 0-5 types [1 points]
  2. More than 5 types [0 points]

* **Number of warnings** [1 points]
  1. 0-2 warnings [1 points]
  2. 2-5 warnings [0.5 point]
  3. More than 5 warnings [0 points]

#### Header file usage check [2 points]

Deduction is applied for usage of some header files that are not allowed.

- One point deduction for each appearance of a header file that is not allowed
- Allowed header file:  `iostream`, `fstream`, `sstream`, `iomanip`, `string`, `cstdlib`, and `cassert`

See clang-tidy flags in https://github.com/ve280/code-check/blob/master/clang/tidy.py
