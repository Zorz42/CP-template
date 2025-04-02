# CP-template

Template stvari za na tekmovanja.

## Generiranje pdf-ov:

Za generiganje v `.config.ini` dodaj kot je ze podano se ostala imena programov,
za katere zelis generirati pdf. Nato pojdi v mapo `pdf` in pozeni

```shell
python gen_latex.py
make
```

To naj bi generiralo `pdf/output.pdf`, v katerem so izbrani source file-i. V
njih uporabljaj tabe (ne presledkov) in vrstice naj bodo dolge najvec (ampak res
najvec) 90 znakov. Printas lahko verjetno tudi dve strani tega pdf-a na list
papirja.

### TODO:

 - [ ] Koda siroka vedno najvec N znakov in pdf, ki se generira to uposteva
   tako, da da kodo v vec stolpcev.
