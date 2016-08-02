#!/usr/bin/gnuplot
OUTFILENAME="TempProf__N_var__T1_0.90__T2_0.70__A_0.00.tex"
set term epslatex size 8.6cm,7cm standalone color dl 3 header '\usepackage{grffile}  \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
load "TempProf.pal"

set tmargin at screen 0.95
set bmargin at screen 0.20
set rmargin at screen 0.95
set lmargin at screen 0.20


set xlabel "\\Large $i/N$" offset 0
set ylabel "\\Large $T_i$" offset 2
titulo01(A)=sprintf("\\scriptsize $%s$",A)
T1=0.90
T2=0.70
T=0.5*(T1+T2)
DelT=T1-T2

set ytics (T2,T,T1)

set xrange [-0.02:1.02]
set yrange [T2-0.05*DelT:T1+0.05*DelT]

set label "\\scriptsize $\\alpha=0.00$" at 0.2,T1

set out OUTFILENAME
plot \
'TempFluxProfile__N_200__T1_0.90__T2_0.70__A_0.00.DAT' u 1:2 w l ls 1 t titulo01("200") ,\
'TempFluxProfile__N_100__T1_0.90__T2_0.70__A_0.00.DAT' u 1:2 w l ls 2 t titulo01("100") ,\
 'TempFluxProfile__N_50__T1_0.90__T2_0.70__A_0.00.DAT' u 1:2 w l ls 3 t titulo01("50") ,\
 'TempFluxProfile__N_20__T1_0.90__T2_0.70__A_0.00.DAT' u 1:2 w l ls 4 t titulo01("20") #,\

set print "-"
print OUTFILENAME
