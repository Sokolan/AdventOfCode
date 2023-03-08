import sys
import os
import re
main_folder_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
sys.path.append(main_folder_path)
from utils.helpers import parse_input

def is_password_viable(password):
    delimiters = "[-, ,:]"
    password_split = re.split(delimiters, password)
    password_split = [string.strip() for string in password_split if string.strip()]

    count = password_split[3].count(password_split[2])

    if int(password_split[0]) <= count <= int(password_split[1]):
        return True

    return False

def check_positions_in_password(password):
    delimiters = "[-, ,:]"
    password_split = re.split(delimiters, password)
    password_split = [string.strip() for string in password_split if string.strip()]

    pos = (int(password_split[0]) - 1, int(password_split[1]) - 1)
    pass_str = password_split[3]
    pass_char = password_split[2]
    if((pass_str[pos[0]] == pass_char and pass_str[pos[1]] != pass_char) or
        (pass_str[pos[0]] != pass_char and pass_str[pos[1]] == pass_char)):
        return True
    else:
        return False

def solve_part_one(input_path):
    input = parse_input(input_path)
    count = 0
    for line in input:
        if is_password_viable(line):
            count += 1
    return count


def solve_part_two(input_path):
    input = parse_input(input_path)
    count = 0
    for line in input:
        if check_positions_in_password(line):
            count += 1
    return count


input_path = os.path.dirname(__file__)

part_one_expected = "2"
res = solve_part_one(f'{input_path}/test.txt')

if(str(res) == part_one_expected):
    print("PART ONE TEST PASSED")
    res = solve_part_one(f'{input_path}/input.txt')
    print(f"Part one solution: {res}")
else:
    print('Part One test failed:\n'
        f'Expected result: {part_one_expected}\n'
        f'Actual result: {res}')


part_two_expected = "1"
res = solve_part_two(f'{input_path}/test.txt')

print('\n')

if(str(res) == part_two_expected):
    print("PART TWO TEST PASSED")
    res = solve_part_two(f'{input_path}/input.txt')
    print(f"Part two solution: {res}")
else:
    print('Part Two test failed: \n'
        f'Expected result: {part_two_expected}\n'
        f'Actual result: {res}')
