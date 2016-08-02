#!/usr/bin/gnuplot
set term tikz size 9,6 standalone
set out "Coefi_ALPHA.tex"
load "set1.pal"
plot './SLOPE_FLUX.DAT' u 2:($5/$7) w l ls 1 title "\\scriptsize $s/J$"

