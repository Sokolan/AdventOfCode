def parse_input(input_path):
    try:
        with open(input_path, 'r') as file:
            return file.readlines()
    except Exception as e:
        print(f'ERROR: {e}')

def remove_newline_char(input):
    for i in range(0,len(input)):
        input[i] = input[i].rstrip()
    