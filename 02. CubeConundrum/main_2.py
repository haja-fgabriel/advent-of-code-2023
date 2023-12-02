import re

f = open("input.txt", "r")

sum_power = 0


def get_power(line):
    """
    Returns None if the game is impossible or else return the game ID.
    """
    max_color = {}
    mo = re.match(fr"Game (\d+): ", line)
    sets = mo.string[mo.end():]

    for set_ in sets.split("; "):
        for num_color in set_.split(", "):
            num, color = num_color.split()
            num = int(num.strip())
            color = color.strip()
            try:
                if num > max_color.get(color, -1):
                    max_color[color] = num
            except:
                import pdb; pdb.set_trace()
                pass
    
    return max_color.get("red", 1) * max_color.get("green", 1) * max_color.get("blue", 1)

for line in f:
    x = get_power(line)
    sum_power += x

print(sum_power)


f.close()