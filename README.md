# stupid_file_parser

A stupid file parser. Why is it stupid? Maybe because it's written in plain C.
Maybe because it's terribly written in general. It's also stupidly fast. It
parses a 5.77GB file in 3.6 seconds, while a Python program that does the same
thing takes 1 minute 15 seconds.

The program reads the file line-by-line, assuming every line has the same
structure. It extracts the desired value by startingat a specified key in the
line, and then reading until a specified delimiter. Yup, pretty terrible. But
hey, C is fun.
