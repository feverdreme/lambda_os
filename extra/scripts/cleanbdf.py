from dataclasses import dataclass
import re

class Fontchar:
    encoding: int
    data: dict[str, str]
    bitmap: list[str]
    dim: tuple[int, int]

    def __init__(self, data: dict[str, str], bitmap: list[str]):
        self.dim = tuple(map(int, data.pop('BBX').split(' ')[:2]))
        self.encoding = int(data.pop('ENCODING'))
        self.data = data
        self.bitmap = list(map(lambda x: f'0x{x}' if x != '00' else '0x0', bitmap))
    
    @staticmethod
    def get_encoding(obj) -> int:
        return obj.encoding

def get_file_contents(fname: str) -> str:
    with open(fname, 'r') as f:
        return f.read()

def extract_chars(raw: str):
    groups = re.findall("STARTCHAR(?:[-\s\w])*?ENDCHAR", raw)
    
    for group in groups:
        cdata, cbmap = group.split("BITMAP\n")

        cdata = cdata.splitlines()
        cdata = [line.split(' ', 1) for line in cdata]
        cdata = dict(cdata)

        cbmap = cbmap.rstrip("ENDCHAR\n").split()

        yield Fontchar(cdata, cbmap)

def generate_asm(name: str, extracted_chars: list[Fontchar]):
    db_contents = []

    ec_map: dict[int, list[str]] = dict()

    for ec in extracted_chars:
        ec_map[ec.encoding] = ec.bitmap

    for i in range(128):
        if i not in ec_map:
            ec_map[i] = ['0xDE', '0xAD', '0xBE', '0xEF'] * 2

    for i in range(128):
        db_contents.append(f"""
__{name}_char_{i}:
\tdb {', '.join(ec_map[i])}""")
    
    db_contents = '\n'.join(db_contents)

    return f"""
; {name} font declaration
; This standard allows c to extern this and reinterpret this as a c-defined struct
[bits 32]

section .data

global _{name}_font
_{name}_font:
\tdb 0, 0 ; width and height
\t{name}_font_data:

{db_contents}
"""
    
if __name__ == "__main__":
    fcontents = get_file_contents("../spleen/spleen-5x8.bdf")
    extracted_chars = sorted(extract_chars(fcontents), key=Fontchar.get_encoding)
    extracted_chars = list(filter(lambda x: x.encoding <= 127, extracted_chars))

    fname = "../../include/fonts/spleen.asm"

    # generate_hfile("spleen_font", "../../include/fonts/spleen.h", extracted_chars)
    text = generate_asm("spleen", extracted_chars)

    with open(fname, 'w+') as f:
        f.write(text)
