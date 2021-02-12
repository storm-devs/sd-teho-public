import chardet
from pathlib import Path
import argparse
import os


TARGET_ENCODING = "utf-8"
EXTENSIONS = ('*.c', '*.cpp', '*.h', '*.fx', '*.ini', '*.txt', '*.ani')


def predict_encoding(filename):
    with open(filename, 'rb') as f:
        rawdata = f.read()

    return chardet.detect(rawdata)['encoding']


def change_encoding(filename):
    source_encoding = predict_encoding(filename)
    if source_encoding is None:
        return False
            
    print(f'{filename}: {source_encoding}')

    with open(filename, 'r', encoding=source_encoding) as f:
        content = f.read()

    with open(filename, 'w', encoding=TARGET_ENCODING) as f:
        f.write(content)
    
    return True
    
   
def process_directory(path):
    files = []
    for ext in EXTENSIONS:
        files.extend(Path(path).rglob(ext))
        
    errors = []
    for filename in files:
        if not change_encoding(filename):
            errors.append(filename)
            
    return errors


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path", help="root directory for a file search")
    args = parser.parse_args()

    path = os.path.abspath(args.path)
    errors = process_directory(path)
    
    if errors:
        print("errors:")    
        for x in errors:
          print(x)