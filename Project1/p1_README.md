# Project 1 Grading Criteria

## Running `codestyle.py`
This script is for checking 1 files: `p1.cpp`. 

## Coding style [10 points]

#### clang-check [4 points]
* **Length of functions** [4 point]

  Your all functions should be no longer than 50 lines.

  1. No long functions [4 point]
  2. 1 long functions [3 points]
  3. 2 long functions [2 points]
  4. 3 long functions [1 point]
  5. 4 or more long functions [0 point]

#### clang-tidy [3 points]
* **Number of warning types** [2 points]
  1. 0-5 types [2 points]
  2. 5-10 types [1.5 points]
  3. 10-25 types [1 point]
  4. More than 25 types [0 points]

* **Number of warnings** [1 points]
  1. 0-2 warnings [1 points]
  2. 2-5 warnings [0.5 point]
  3. More than 5 warnings [0 points]

#### Header file usage check [3 points]

Deduction is applied for usage of some header files that are not allowed.

- One point deduction for each appearance of a header file that is not allowed
- Allowed header file: `iostream`, `cmath`, `string`,`cstdlib` 

See clang-tidy flags in https://github.com/ve280/code-check/blob/master/clang/tidy.py
