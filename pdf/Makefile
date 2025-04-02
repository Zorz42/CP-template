default: output.pdf

output.pdf: output.tex .include.tex
	latex -interaction=nonstopmode -output-format=pdf $^
	latex -interaction=nonstopmode -output-format=pdf $^

%.pdf: %.tex
	latex -interaction=nonstopmode -output-format=pdf $^
	latex -interaction=nonstopmode -output-format=pdf $^
