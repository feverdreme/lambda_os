from dataclasses import dataclass
import re
from tarfile import ENCODING

@dataclass
class bdf_font_char:
    dim: tuple[int, int]
    encoding: int
    intmap: list[int]
    bitmap: list[list[bool]]

@dataclass
class Bdf_Font:
    numchars: int
    data: list[bdf_font_char]

def retrieve_font(name: str) -> str:
    with open(name, 'r') as f:
        return f.read()
    
def retrieve_numchars(flines: list[str]) -> int:
    for line in flines:
        if line.startswith("CHARS"):
            return int(line.split()[1])

def parse_chars(raw: str):
    groups = re.findall("STARTCHAR (?:[-\w\s])*?ENDCHAR", raw)

    for group in groups:
        cdata, cbitmap = group.split("BITMAP\n")
        cdata = cdata.split('\n')
        cdata = [line.split(sep=' ', maxsplit=1) for line in cdata][:-1]
        cdata = dict(cdata)
        
        if int(cdata["ENCODING"]) > 127: continue

        cw, ch, *_ = map(int, cdata["BBX"].split())
        cbitmap: list[str] = cbitmap.rstrip("\nENDCHAR").split()
        cbitmap = list(map(lambda x: int(x, 16), cbitmap))

        new_bitmap = [
            [
                0 != cbitmap[r_i] & (1 << (cw - 1 - c_i))
            for c_i in range(cw)]
        for r_i in range(ch)]

        yield bdf_font_char((cw, ch), cdata["ENCODING"], cbitmap, new_bitmap)


if __name__ == "__main__":
    file_contents = retrieve_font("../spleen/spleen-5x8.bdf")
    file_lines = file_contents.splitlines(keepends=False)

    # WAIT NO THIS SHOULD JUST SNAITIZE, THE PARSING SHOULD BE DONE WITH THE C PROGRAM, JUST EXPORT THE INTS
    spleen = Bdf_Font(retrieve_numchars(file_lines), list(parse_chars(file_contents)))
    
