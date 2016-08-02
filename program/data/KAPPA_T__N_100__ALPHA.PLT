#!/usr/bin/gnuplot
set dummy x, y
#a=-3.2

#set term tikz size 9,6 standalone
OUTFILENAME="KAPPA_T__N_100__ALPHA.tex"
set term epslatex size 9cm,7cm standalone color dl 3 header '\newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
#set format "\\Large %s"
#set format y "$%.2t \\times 10^{%+03T}$" # "1.23*10^+04"
set format y "$10^{%+T}$" # "1.23*10^+04"
set style line  1 lt 1 lw 2 lc rgb '#66C2A5' # teal
set style line 11 lt 2 lw 2 lc rgb '#66C2A5' # teal
#set style line 12 lt 2 lw 2 lc rgb '#FC8D62' # orange

load "myown.pal" 


title_fit(Ae,aae)=sprintf("\\scriptsize $%.2f T^{%.2f}$",Ae,aae)
title_Li3(aae)=sprintf("\\scriptsize $ T^{%.2f}$",aae)
A=0.5
aa=-3.2
set xlabel "\\Large $T$"
set ylabel "\\Large $\\kappa$"
set logscale x
set logscale y
set ytics add ("$1$" 1)
set ytics add ("$10$" 10)
set mytics 1
#set key center right
#set key invert
set xrange [0.1:10]

set xtics add ("$0.5$" 0.5)

func(x)=A*x**aa
fit [0.5:2] func(x) 'KAPPA_T__N_100__A_0.00.DAT' u (0.5*($3+$4)):10 via A,aa; A0p00=A; aa0p00=aa;
fit [0.5:2] func(x) 'KAPPA_T__N_100__A_1.00.DAT' u (0.5*($3+$4)):10 via A,aa; A1p00=A; aa1p00=aa;
fit [0.5:2] func(x) 'KAPPA_T__N_100__A_2.00.DAT' u (0.5*($3+$4)):10 via A,aa; A2p00=A; aa2p00=aa;
fit [0.5:2] func(x) 'KAPPA_T__N_100__A_INFT.DAT' u (0.5*($3+$4)):10 via A,aa; AINFT=A; aaINFT=aa;

g(x)=( (x>=0.5 & x<=2)? 1.0 : (1/0) );

set out OUTFILENAME
set print "-"
print OUTFILENAME

set yrange [0.001:100]
set multiplot
set key invert
#set key at 10,80
plot \
g(x)*x**(-3.2) ls 1  t title_Li3(-3.2) #,\
#g(x)*A0p00*x**(aa0p00) ls 1 t title_fit(A0p00,aa0p00) ,\
#g(x)*A1p00*x**(aa1p00) ls 3 t title_fit(A1p00,aa1p00) ,\
#g(x)*A2p00*x**(aa2p00) ls 5 t title_fit(A2p00,aa2p00) ,\
#g(x)*AINFT*x**(aaINFT) ls 7 t title_fit(AINFT,aaINFT) #,\

set key at 14,30
set xrange [0.1:10]
plot \
'KAPPA_T__N_100__A_1.00.DAT'  u (0.5*($3+$4)):10 w lp ls  3  pt 2*3 ps 2 t "\\scriptsize $1.00$"   , \
'KAPPA_T__N_100__A_1.50.DAT'  u (0.5*($3+$4)):10 w lp ls  4  pt 2*4 ps 2 t "\\scriptsize $1.50$"   , \
'KAPPA_T__N_100__A_2.00.DAT'  u (0.5*($3+$4)):10 w lp ls  5  pt 2*5 ps 2 t "\\scriptsize $2.00$"   , \
'KAPPA_T__N_100__A_3.00.DAT'  u (0.5*($3+$4)):10 w lp ls  6  pt 2*6 ps 2 t "\\scriptsize $3.00$"   , \
'KAPPA_T__N_100__A_INFT.DAT'  u (0.5*($3+$4)):10 w lp ls  7  pt 2*7 ps 2 t "\\scriptsize $\\infty$"#, \

#'KAPPA_T__N_100__A_0.00.DAT'  u (0.5*($3+$4)):10 w lp ls  1  pt 2*1 ps 2 t "\\scriptsize $0.00$"   , \
#'KAPPA_T__N_100__A_0.50.DAT'  u (0.5*($3+$4)):10 w lp ls  2  pt 2*2 ps 2 t "\\scriptsize $0.50$"   , \

unset multiplot

#KAPPA_T__N_100__A_0.00.DAT
#KAPPA_T__N_100__A_0.50.DAT
#KAPPA_T__N_100__A_1.00.DAT
#KAPPA_T__N_100__A_1.50.DAT
#KAPPA_T__N_100__A_2.00.DAT
#KAPPA_T__N_100__A_3.00.DAT
#KAPPA_T__N_100__A_INFT.DAT
