import re

f = open("input.txt", "r")

sum = 0

digits = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
RE_DIGITS = re.compile("|".join(digits))

for line in f:
    first = None
    last = None
    line = line.strip()
    candidate = None
    for i, c in enumerate(line):
        if c.isdigit():
            candidate = int(c)
        else:
            mo = RE_DIGITS.match(line, i)
            if mo:
                candidate = digits.index(mo.group())
        
        if first is None:
            first = candidate
        last = candidate

    sum += first * 10 + last

print(sum)

f.close()