# Debug Cleaner
A simple command line tool to remove pesky debug statements from a specified file.

## How to Install
Make sure you have homebrew installed first, then enter the following commands:
```
brew tap jpope15/DebugCleaner
brew install debugcleaner
 ```

You are now able to use the tool!

## How to Use
First, mark any line in a file with `DEBUG_REMOVE`
This will ensure that that line is removed.

Then, open the terminal and type the following command:
`debugcleaner <file>`

A message will appear once the file has been parsed, it will contain the filename, and how many lines were removed.

Thats it!
