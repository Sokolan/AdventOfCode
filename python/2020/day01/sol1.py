import sys
import os
main_folder_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
sys.path.append(main_folder_path)

from utils.helpers import parse_input

def find_two_sum(lis, sum):
    left = 0
    right = len(lis) - 1
    while left != right:
        curr_sum = lis[left] + lis[right]
        if(curr_sum == sum):
            return (left, right)
        elif(curr_sum < sum):
            left += 1
        else:
            right -= 1
    return (-1,-1)

    

def solve_part_one(input_path):
    input = parse_input(input_path)
    int_input = list(map(int, input))
    int_input.sort()
    SUM = 2020
    two_sum_indexes = find_two_sum(int_input, SUM)
    if two_sum_indexes == (-1,-1):
        return f"NO TWO NUMBERS THAT EQUAL {SUM}"
    return int_input[two_sum_indexes[0]] * int_input[two_sum_indexes[1]]
    

def solve_part_two(input_path):
    input = parse_input(input_path)
    int_input = list(map(int, input))
    int_input.sort()
    SUM = 2020
    for i in range(0, len(int_input)):
        SUM -= int_input[i]
        
        two_sum_indexes = find_two_sum(int_input, SUM)
        if(two_sum_indexes == (-1,-1) or
            two_sum_indexes[0] == i or
            two_sum_indexes[1] == i):
            SUM += int_input[i]
            continue
        
        # otherwise we got SUM - num1 = num2 + num3
        # SUM = num1 + num2 + num 3
        return int_input[i] * int_input[two_sum_indexes[0]] * int_input[two_sum_indexes[1]] 
    return "ERROR"


input_path = os.path.dirname(__file__)

part_one_excepted = "514579"
res = solve_part_one(f'{input_path}/test.txt')

if(str(res) == part_one_excepted):
    print("PART ONE TEST PASSED")
    res = solve_part_one(f'{input_path}/input.txt')
    print(f"Part one solution: {res}")
else:
    print('Part One test failed:\n'
        f'Expected result: {part_one_excepted}\n'
        f'Actual result: {res}')


part_two_expected = "241861950"
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