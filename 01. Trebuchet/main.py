import re

f = open("input.txt", "r")

sum = 0

for line in f:
    digits = re.findall(r"\d", line.strip())
    sum += int(digits[0] + digits[-1])

print(sum)

f.close()