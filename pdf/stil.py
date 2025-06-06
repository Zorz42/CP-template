#!/usr/bin/env python3

from pygments.style import Style
from pygments.styles import get_style_by_name
from pygments.token import (Keyword, Name, Comment, String,
     Number, Operator, Punctuation)

class CodeblocksStyle(Style):
    default_style = ""
    styles = {
        Comment:          '#a1a1e0',
        Comment.Preproc:  '#31813f',  # Why is this under comments ??
        Keyword:          'bold #00a',
        Operator:         '#ff0505',
        Punctuation:      '#ff0505',
        Name:             '#0e0e0e',
        String:           '#2828ff',
        Number:           '#f007f0',
    }

class MladiRTKcrnobeloStyle(Style):
    default_style = ""
    styles = {
        Comment:          '#a0a0a0',
        Comment.Preproc:  '#707070',  # Why is this under comments ??
        Keyword:          'bold #000',
        Operator:         '#000',
        Operator.Word:    'bold #000',
        Punctuation:      '#000',
        Name:             '#303030',
        String:           '#303030',
        Number:           '#303030',
    }

#   algol, algol_nu
GrayscaleStyle = get_style_by_name('bw')

