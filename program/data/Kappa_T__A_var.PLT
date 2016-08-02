#!/usr/bin/gnuplot

#set term epslatex size 8cm,7cm standalone color dl 3 header '\newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
OUTFILENAME="Kappa_T__A_var.tex"
#set out OUTFILENAME
set print "-"
print OUTFILENAME
load "set1.pal"

set logscale y
set logscale x
set yrange [0.001:100]
set xrange [0.01:2.1]
set xlabel "\\Large $T$"
set ylabel "\\Large $\\kappa$"
set label "$N=100$" at 0.2, 50
func(x)=(x)**(-3.2)
plot \
'Kappa_T__A_var.DAT' i 0 u (0.5*($3+$4)):10 w lp ls 1 pt 66 t "\\scriptsize $\\alpha=0.00$" ,\
'Kappa_T__A_var.DAT' i 1 u (0.5*($3+$4)):10 w lp ls 2 pt 67 t "\\scriptsize $1.00$" ,\
'Kappa_T__A_var.DAT' i 2 u (0.5*($3+$4)):10 w lp ls 3 pt 67 t "\\scriptsize $2.00$" ,\
'Kappa_T__A_var.DAT' i 3 u (0.5*($3+$4)):10 w lp ls 4 pt 67 t "\\scriptsize $3.00$" ,\
'Kappa_T__A_var.DAT' i 4 u (0.5*($3+$4)):10 w lp ls 5 pt 67 t "\\scriptsize $\\infty$" ,\
func(x) w l ls 8 lw 3 t "\\scriptsize $T^{-3.2}$"

