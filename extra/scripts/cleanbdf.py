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
    
    def get_bmap_string(self) -> str:
        return '{' + ', '.join(
            ['0x0' if c == '0x00' else c.rstrip('0') for c in self.bitmap]
        ) + '}'
    
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

def generate_hfile(name: str, fname: str, extracted_chars: list[Fontchar]):
    base_fc = extracted_chars[0]
    contents = ['{false, {0}}' for _ in range(128)]
    NEWLINE = '\n'

    for ec in extracted_chars:
        contents[ec.encoding] = '{true, ' + ec.get_bmap_string() + '}'
    
    contents = map(lambda x: ' ' * 4 * 2 + x, contents)

    with open(fname, 'w+') as wfile:
        wfile.write(f"""\
#ifndef {name.upper()}_H
#define {name.upper()}_H

#include <libc/fonts.h>

struct font {name} = {{
    {base_fc.dim[0]},
    {base_fc.dim[1]},
    {{
{(',' + NEWLINE).join(contents)}
    }}
}};

#endif""")

def generate_asm(name: str, extracted_chars: list[Fontchar]):
    base_fc = extracted_chars[0]
    db_contents = [f'__{name}_char_{i}: db 0 ; Not printable' for i in range(128)]
    NEWLINE = '\n'
    mov_template = f'\tlea eax, __{name}_char_%d\n\tmov [{name}_font_data + %d], eax'

    for ec in extracted_chars:
        db_contents[ec.encoding] = f"__{name}_char_{ec.encoding}:\n\tdb 0x1\n\t{'db ' + ', '.join(ec.bitmap)}"

    return f"""
; {name} font declaration
; This standard allows c to extern this and reinterpret this as a c-defined struct

init_{name}_font:
\tmov {name}_font, {base_fc.dim[0]}
\tmov [{name}_font + 1], {base_fc.dim[1]}
{NEWLINE.join([mov_template % (i, i) for i in range(128)])}

{name}_font:
\tdb 0, 0 ; width and height
\t\t{name}_font_data: times 128 db 0 ; pointer array

{NEWLINE.join(db_contents)}
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
