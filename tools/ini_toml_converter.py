import os
import sys
import toml
from os.path import join

try:
    folder_path = sys.argv[1]
except IndexError:
    print("Please specify folder with INI files")
    exit()

for root, dirs, files in os.walk(folder_path):
    for f in files:
        file_name = join(root, f)
        if ".ini" in file_name:
            print(file_name)
            with open(file_name) as reader:
                with open(file_name.replace(".ini", ".toml"), 'w') as w:
                    table = {}
                    currentSectionName = None

                    for line in reader.readlines():
                        line = line.strip(' \n')

                        if not (line.startswith(";") or len(line) == 0):
                            # section start
                            if line.startswith("["):
                                currentSectionName = line.strip(
                                    '[]').replace(' ', '_')
                                table[currentSectionName] = {}
                            else:
                                currentSection = table
                                if currentSectionName is not None:
                                    currentSection = table[currentSectionName]

                                # simple key-value pair
                                kv = line.split(';', 1)[0].split("=", 1)

                                if len(kv) == 1:
                                    k = kv[0].strip()
                                    currentSection[k] = True
                                elif len(kv) == 2:
                                    k = kv[0].strip()
                                    v = kv[1].strip()

                                    k = k.replace(' ', '_')

                                    try:
                                        v = int(v)
                                    except:
                                        try:
                                            v = float(v)
                                        except:
                                            v = v

                                    # array maybe?
                                    if k in currentSection:
                                        cv = currentSection[k]
                                        if isinstance(cv, list):
                                            cv.append(v)
                                        else:
                                            currentSection[k] = [cv, v]
                                    else:
                                        currentSection[k] = v
                                else:
                                    raise "unknown"

                    s = toml.dumps(table, encoder=toml.TomlArraySeparatorEncoder(
                        separator=",\n   "))
                    s = s.replace("= [ ", "= [\n    ").replace("   ]", ']')

                    w.write(s)
