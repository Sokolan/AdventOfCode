import sys
import os
main_folder_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
sys.path.append(main_folder_path)
from utils.helpers import parse_input

def solve_part_one(input_path):
    return

def solve_part_two(input_path):
    return


input_path = os.path.dirname(__file__)

part_one_expected = ""
res = solve_part_one(f'{input_path}/test.txt')

if(str(res) == part_one_expected):
    print("PART ONE TEST PASSED")
    res = solve_part_one(f'{input_path}/input.txt')
    print(f"Part one solution: {res}")
else:
    print('Part One test failed:\n'
        f'Expected result: {part_one_expected}\n'
        f'Actual result: {res}')


part_two_expected = ""
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
