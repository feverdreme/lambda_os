# Development notes

## 8/1

Merged fontdriver branch. Will keep it when I inevitably have to change more stuff.

- Typecheck other helping funcs
- It's annoying to have to supply the spleen_font everytime you run putc. Make this a seperate func like foputc. Make putc use default spleen. Then use a #define directive or something to do env vars
- Optimize data and hopefully when filesystem
- Linkerscript is needed. I don't want to have to probe memory with gdb every time the kernel size changes
- Remove hyphens from GDT
- Fix > and < appearances. Make them less tall in font. Manually edit and do changes with git submodules if possible

## 7/11

- Create a doxygen branch
- Provision time correctly and restructure timeline + checklist
  - estimates for how long each mini task will take
  - respond to mentor
  - time management
    - microsoft planner
    - gh projects
- Research c unit testing
  - gh actions also i think
  - <https://stackoverflow.com/questions/65820/unit-testing-c-code>
- .vscode configs
- GDT code from 
  <http://www.osdever.net/bkerndev/Docs/gdt.htm>
  