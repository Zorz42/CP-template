import sys
import os
import contextlib

from pygments import highlight
from pygments.lexers.c_cpp import CLexer, CppLexer
from pygments.lexers.jvm import JavaLexer
from pygments.lexers.pascal import DelphiLexer
from pygments.lexers.python import PythonLexer
from pygments.formatters import LatexFormatter

from stil import CodeblocksStyle, GrayscaleStyle, MladiRTKcrnobeloStyle

@contextlib.contextmanager
def pushd(new_dir):
    previous_dir = os.getcwd()
    os.chdir(new_dir)
    try:
        yield
    finally:
        os.chdir(previous_dir)

langs = ['c', 'cpp', 'py', 'java', 'pas']
lexer = {
        'c': CLexer(),
        'cpp': CppLexer(),
        'py': PythonLexer(),
        'java': JavaLexer(),
        'pas': DelphiLexer(),
        }


def generate_latex(source):
    formatter = LatexFormatter(style=MladiRTKcrnobeloStyle, full=False)
    with open('.style_defs.tex', 'w') as fstyles:
        print(formatter.get_style_defs(), file=fstyles)
    ime, lang = source.split('.', maxsplit=1)
    fnout = f'.{ime}.{lang}.tex'
    with open(f'../algos/{source}', 'r') as fin, open(fnout, 'w') as fout:
        highlight(fin.read().replace('\t', '  '), lexer[lang], formatter, fout)

    lines: list[str]
    with open(fnout, 'r') as fin:
        lines = fin.readlines()

    # ugly
    lines[0] = lines[0][:-2] + ",frame=single,fontsize=\\tiny]\n"

    line = "\subsection*{" + ime.replace("_","\\_") + "}\n"
    lines.insert(0, line)

    with open(fnout, 'w') as fout:
        for line in lines:
            fout.write(line)

    with open(f'.include.tex', 'a') as fincl:
        print(f'\\input{{{fnout}}}', file=fincl)


if __name__ == '__main__':
    sources = []
    for file in os.listdir("../algos"):
        if file.endswith(".cpp"):
            sources += [file]
    if os.path.exists('.include.tex'):
        os.remove('.include.tex')

    for source in sources:
        print(f'source {source}')
        generate_latex(source)
