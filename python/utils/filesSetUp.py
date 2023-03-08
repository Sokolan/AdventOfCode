import os

def set_up_folders(year):
    for day in range(1,26):
        try:
            script_dir = os.path.dirname(__file__)
            new_path = os.path.join(script_dir, f"../{year}/day{day:02}")
            os.mkdir(new_path)

        except Exception as e:
            print(f"ERROR: {e}")

def set_up_files(year):
    for day in range(1,26):
        try:
            script_dr = os.path.dirname(__file__)
            path = os.path.join(script_dr, f'../{year}/day{day:02}')
            with open(f'{path}/sol{day}.py', 'w') as file:
                curr_folder = os.path.dirname(__file__)
                with open(f'{curr_folder}/template.py', 'r') as template:
                    for line in template:
                        file.write(line)
                open(f'{path}/test.txt', 'x').close()
                open(f'{path}/input.txt', 'x').close()
            

        except Exception as e:
            print(f'Error: {e}')

set_up_folders('2020')
set_up_files('2020')
