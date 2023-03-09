import sys
import os
import re
main_folder_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../..'))
sys.path.append(main_folder_path)
import utils.helpers as util


def check_for_fields_existence(passport):
    fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"]
    for info in passport:
        if info in fields:
            fields.remove(info)
    if(len(fields) == 0):
        return True
    elif(len(fields) == 1 and fields[0] == "cid"):
        return True
    
    return False

def check_if_fields_valid(passport):
    if not (1920 <= int(passport["byr"]) <= 2002):
        return False
    if not (2010 <= int(passport["iyr"]) <= 2020):
        return False
    if not (2020 <= int(passport["eyr"]) <= 2030):
        return False
    cm = passport["hgt"].find("cm")
    inc = passport["hgt"].find("in")
    if (cm == -1 and inc == -1):
        return False
    if (cm != -1):
        if not (150 <= int(passport["hgt"][0:cm]) <= 193):
            return False
    else: # inch != -1       
        if not (59 <= int(passport["hgt"][0:inc]) <= 76):
            return False
    hlc = passport["hcl"]
    if not (hlc[0] == '#' and len(hlc) == 7):
        return False
    for char in hlc[1:7]:
        if not ('a' <= char <= 'f' or '0' <= char <= '9'):
            return False
    valic_eyc = ("amb", "blu", "brn", "gry", "grn", "hzl", "oth")
    if not (passport["ecl"] in valic_eyc):
        return False
    pid = passport["pid"]
    if not (len(pid) == 9):
        return False
    return True

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
    
    count = 0
    for i in range(0, len(passports)):
        if(check_for_fields_existence(passports[i])):
            count +=1

    return count


def solve_part_two(input_path):
    input = util.parse_input(input_path)
    util.remove_newline_char(input)
    input = fix_newlines(input)
    passports = create_passports(input)
    
    count = 0
    for i in range(0, len(passports)):
        if(check_for_fields_existence(passports[i])):
            if(check_if_fields_valid(passports[i])):
                count +=1  


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


part_two_expected = "2"
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
