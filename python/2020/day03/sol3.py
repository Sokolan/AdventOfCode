import sys
import os
main_folder_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
sys.path.append(main_folder_path)
import utils.helpers as util

def count_trees_on_the_way(input, steps_right, steps_down):
    pos = 0
    count = 0
    for i in range(steps_down, len(input),steps_down):
        pos += steps_right
        pos %= len(input[0])

        if(input[i][pos] == '#'):
            count += 1
        
    return count

def solve_part_one(input_path):
    input = util.parse_input(input_path)
    util.remove_newline_char(input)
    return count_trees_on_the_way(input, 3, 1)
    

def solve_part_two(input_path):
    input = util.parse_input(input_path)
    util.remove_newline_char(input)
    count = 0
    count += count_trees_on_the_way(input, 1, 1)
    count *= count_trees_on_the_way(input, 3, 1)
    count *= count_trees_on_the_way(input, 5, 1)
    count *= count_trees_on_the_way(input, 7, 1)
    count *= count_trees_on_the_way(input, 1, 2)

    return count


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
