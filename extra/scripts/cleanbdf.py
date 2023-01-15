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
[bits 64]

section .data

global {name}_font
{name}_font:
\tdb 5, 8 ; width and height; deprecated actually
\t{name}_font_data:

{db_contents}
"""

def generate_asm2(name: str, extracted_chars: list[Fontchar]):
    base_fc = extracted_chars[0]
    db_contents = []
    ptr_contents = []
    MOV_TEMPLATE = f"""\
\tmov rbx, __{name}_char_%d
\tmov [{name}_font_data + %d], rbx"""

    for ec in extracted_chars:
        db_contents.append(f"__{name}_char_{ec.encoding}:\n\t{'db ' + ', '.join(ec.bitmap)}")
        ptr_contents.append(MOV_TEMPLATE % (ec.encoding, ec.encoding * 8)) # 8 bytes for 64bit

    ptr_contents = '\n'.join(ptr_contents)
    db_contents = '\n'.join(db_contents)

    return f"""\
; {name} font declaration
; This standard allows c to extern this and reinterpret this as a c-defined struct
[bits 64]
section .text
global init_{name}_font
init_{name}_font:
\tmov qword [{name}_font], {base_fc.dim[0]}
\tmov qword [{name}_font + 8], {base_fc.dim[1]}
{ptr_contents}
ret
section .data
global {name}_font
{name}_font:
\tdq 0, 0 ; width and height
\t{name}_font_data: times 128 dq 0 ; pointer array (64bit)
{db_contents}
"""

def generate_asm3(name: str, extracted_chars: list[Fontchar]):
    """
        Font specs

        uint32_t width
        uint32_t height
        bool[128] is_printable
        byte[8][128] data
    """
    fc_width, fc_height = extracted_chars[0].dim

    char_bmaps: list[list[str]] = [["0x0"] * 8 for _ in range(128)]
    is_printable = ["0x0" for _ in range(128)]

    # the characters that are printable
    for ec in extracted_chars:
        char_bmaps[ec.encoding] = ec.bitmap
        is_printable[ec.encoding] = "0x1"
    
    # create data string
    db_data = ""
    for bmap in char_bmaps:
        db_data += "db " + ", ".join(bmap) + "\n"
    
    return f"""
; {name} font declaration
; This standard allows c to extern this and reinterpret this as a c-defined struct
[bits 64]
section .data
global {name}_font
{name}_font:

dw {fc_width}
dw {fc_height}
db {", ".join(is_printable)}
{db_data}
"""

if __name__ == "__main__":
    fcontents = get_file_contents("../../submodules/spleen/spleen-5x8.bdf")
    extracted_chars = sorted(extract_chars(fcontents), key=Fontchar.get_encoding)
    extracted_chars = list(filter(lambda x: x.encoding <= 127, extracted_chars))

    fname = "../../source/include/fonts/spleendata.asm"

    # generate_hfile("spleen_font", "../../include/fonts/spleen.h", extracted_chars)
    text = generate_asm3("spleen", extracted_chars)

    with open(fname, 'w+') as f:
        f.write(text)
