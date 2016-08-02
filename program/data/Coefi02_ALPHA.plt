#!/usr/bin/gnuplot
set term tikz size 9,6 standalone
set out "Coefi02_ALPHA.tex"
load "set1.pal"
plot './SLOPE_FLUX.DAT' u 2:($7/$5) w l ls 1 title "\\scriptsize $J/s$"

