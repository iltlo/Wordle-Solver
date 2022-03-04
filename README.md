# Wordle Solver
### Feature
- C++ program to help you solve [WORDLE](https://www.powerlanguage.co.uk/wordle/) puzzles.
- Suggest possible words based on your attempt-result history in the current game.

### How to use the program?
- Your word attempt and the corresponding result are the inputs of this WORDLE solver.
- Result 🟩:g   🟨:y  ⬛:b
- For example after attempt, if the result shown is: 🟨⬛⬛🟩⬛, your input would be: ybbgb (without spacing).
- Suggestion words will be immediately shown.
- You will be repeatedly prompted for attempt-result input until result: "ggggg" is input, which idicates the WORDLE puzzle is solved with 🟩🟩🟩🟩🟩.

### Word List
- In advance, a shell script powered by linux `spell` command is used to generate a dictionary of all possible 5-character words. 
- There are in total of 5390 words in this dictionary. It is then implanted into the program.

### Note
- Compiler: C++11 or version above.