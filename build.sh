#!/bin/bash

file="szakdolgozat"

pdflatex $file".tex"
bibtex $file".aux"
pdflatex $file".tex"
pdflatex $file".tex"
