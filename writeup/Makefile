writeup: writeup.tex writeup.bib
	pdflatex writeup.tex
	bibtex writeup.aux
	pdflatex writeup.tex 
	pdflatex writeup.tex 

clean: 
	rm *.bbl
	rm *.blg
	rm *.log
	rm *.pdf
	rm *.dvi
