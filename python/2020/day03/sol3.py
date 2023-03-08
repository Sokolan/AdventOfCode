import sys
import os
main_folder_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
sys.path.append(main_folder_path)
import utils.helpers as util

def count_trees_on_the_way(input, steps):
    pos = 0
    count = 0
    for i in range(1, len(input)):
        pos += 3
        pos %= len(input[0])

        if(input[i][pos] == '#'):
            count += 1
        
    return count

def solve_part_one(input_path):
    input = util.parse_input(input_path)
    util.remove_newline_char(input)
    return count_trees_on_the_way(input, 3)
    

def solve_part_two(input_path):
    return


input_path = os.path.dirname(__file__)

part_one_expected = "7"
res = solve_part_one(f'{input_path}/test.txt')

if(str(res) == part_one_expected):
    print("PART ONE TEST PASSED")
    res = solve_part_one(f'{input_path}/input.txt')
    print(f"Part one solution: {res}")
else:
    print('Part One test failed:\n'
        f'Expected result: {part_one_expected}\n'
        f'Actual result: {res}')


part_two_expected = "336"
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
