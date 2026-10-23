import os
import sys
import shutil
import subprocess

from pygments import highlight
from pygments.formatters import LatexFormatter
from pygments.lexers.c_cpp import CppLexer
from pygments.style import Style
from pygments.token import Keyword, Name, Comment, String, Number, Operator, Punctuation

ALGOS_DIR = "algos"
# all generated files go here
BUILD_DIR = "pdf"
PDF_NAME = "output.pdf"

TEMPLATE = r"""\documentclass[a4paper,12pt]{article}

\usepackage[slovene,english]{babel}
\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}
\usepackage{titling}
\usepackage{hyperref}
\usepackage{titlesec}
\usepackage{tikz}
\usepackage{url}
\usepackage{breakurl}
\usepackage[top=1cm, bottom=1.5cm, inner=1cm, outer=1cm]{geometry}
\usepackage{fancyvrb}

\overfullrule=2cm

\titleformat{\chapter}{\normalfont\huge}{\thechapter.}{20pt}{\huge}

\newenvironment{no_pagebreak} {\par\nobreak\vfil\penalty0\vfilneg
  \vtop\bgroup} {\par\xdef\tpd{\the\prevdepth}\egroup \prevdepth=\tpd}

\usepackage{listings}
\usepackage{color}
\usepackage{DejaVuSansMono}

\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{mauve}{rgb}{0.58,0,0.82}


\lstset{
  frame=single,
  language=C,
  aboveskip=3mm,
  belowskip=3mm,
  showstringspaces=false,
  columns=flexible,
  basicstyle={\small\ttfamily},
  numbers=none,
  numberstyle=\tiny\color{gray},
  keywordstyle=\color{blue},
  commentstyle=\color{dkgreen},
  stringstyle=\color{mauve},
  breaklines=true,
  breakatwhitespace=true,
  tabsize=3
}

\input{style_defs.tex}

\newcommand{\myparagraph}[1]{\paragraph{#1}\mbox{}}

\begin{document}

\input{include.tex}

\end{document}
"""

# black and white, readable when printed
class PrintStyle(Style):
    default_style = ""
    styles = {
        Comment:          '#a0a0a0',
        Comment.Preproc:  '#707070',
        Keyword:          'bold #000',
        Operator:         '#000',
        Operator.Word:    'bold #000',
        Punctuation:      '#000',
        Name:             '#303030',
        String:           '#303030',
        Number:           '#303030',
    }

FORMATTER = LatexFormatter(style=PrintStyle, full=False, verboptions=r"frame=single,fontsize=\tiny")

def write(name: str, text: str):
    with open(os.path.join(BUILD_DIR, name), "w") as file:
        file.write(text)

# latex of one algorithm, titled with its name and never split between pages
def algo_latex(source: str) -> str:
    with open(os.path.join(ALGOS_DIR, source), "r") as file:
        code = file.read().replace("\t", "  ")
    title = source[:-4].replace("_", r"\_")
    return f"\\begin{{no_pagebreak}}\n\\subsection*{{{title}}}\n" + highlight(code, CppLexer(), FORMATTER) + "\\end{no_pagebreak}\n"

def run_latex():
    # run twice so that references are resolved
    for _ in range(2):
        result = subprocess.run(["latex", "-interaction=nonstopmode", "-output-format=pdf", "output.tex"], cwd=BUILD_DIR, capture_output=True, text=True)
        if result.returncode != 0:
            print(result.stdout)
            print(f"LaTeX failed, see {os.path.join(BUILD_DIR, 'output.log')}")
            sys.exit(1)


if __name__ == "__main__":
    os.makedirs(BUILD_DIR, exist_ok=True)
    sources = sorted(file for file in os.listdir(ALGOS_DIR) if file.endswith(".cpp"))

    include = ""
    for source in sources:
        print(f"source {source}")
        write(source + ".tex", algo_latex(source))
        include += f"\\input{{{source}.tex}}\n"

    write("include.tex", include)
    write("style_defs.tex", FORMATTER.get_style_defs())
    write("output.tex", TEMPLATE)

    run_latex()
    shutil.copy(os.path.join(BUILD_DIR, PDF_NAME), PDF_NAME)
    print(f"Created {PDF_NAME}")
