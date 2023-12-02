import re

f = open("input.txt", "r")

MAX_ALLOWED = {
    "red": 12,
    "green": 13,
    "blue": 14,
}

id_sum = 0


def get_possible_game_id(line):
    """
    Returns None if the game is impossible or else return the game ID.
    """
    mo = re.match(fr"Game (\d+): ", line)
    game_id = int(mo.group(1))
    sets = mo.string[mo.end():]
    for set_ in sets.split("; "):
        for num_color in set_.split(", "):
            num, color = num_color.split()
            num = int(num.strip())
            if num > MAX_ALLOWED[color.strip()]:
                return None
    return game_id


for line in f:
    game_id = get_possible_game_id(line)
    if game_id is not None:
        id_sum += game_id

print(id_sum)


f.close()