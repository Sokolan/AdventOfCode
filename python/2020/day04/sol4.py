import sys
import os
import re
main_folder_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
sys.path.append(main_folder_path)
import utils.helpers as util


def check_for_fields(passport, fields):
    fields_copy = fields[:]
    for info in passport:
        if info in fields_copy:
            fields_copy.remove(info)
    if(len(fields_copy) == 0):
        return True
    elif(len(fields_copy) == 1 and fields_copy[0] == "cid"):
        return True
    
    return False

def fix_newlines(input):
    fixed_lines = []
    index = 0
    fixed_lines.append("")
    for line in input:
        if not line:
            index += 1
            fixed_lines.append("")
            continue
        fixed_lines[index] += f" {line}"
    
    return fixed_lines

def create_passports(input):
    passports = []
    for line in range(0, len(input)):
        passports.append({})
        
        deliminator = "[ :]"
        line_split = re.split(deliminator, input[line])
        line_split = [ele.strip() for ele in line_split if ele.strip()]

        for i in range(0, len(line_split), 2):
            passports[line][line_split[i]] = line_split[i+1]

    return passports

def solve_part_one(input_path):
    input = util.parse_input(input_path)
    util.remove_newline_char(input)
    input = fix_newlines(input)
    passports = create_passports(input)
    
    fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"]

    count = 0
    for i in range(0, len(passports)):
        if(check_for_fields(passports[i], fields)):
            count +=1

    return count

    check_for_fields(passports, fields)

def solve_part_two(input_path):
    return


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
