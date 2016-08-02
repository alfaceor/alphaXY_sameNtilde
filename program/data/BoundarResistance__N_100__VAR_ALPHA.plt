#!/usr/bin/gnuplot
OUTFILENAME="BoundarResistance__N_100__VAR_ALPHA.tex"
set term epslatex size 8.6cm,7cm standalone color dl 3 header '\usepackage{grffile} \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
set out OUTFILENAME

load 'TempProf.pal'

set xlabel "\\Large $\\alpha$"
#set ylabel "\\Large $T_L - T_2$" offset 2
titulo01(T1,T2)=sprintf("\\scriptsize $%.2f$",0.5*(T1+T2))
#titulo02(T1,T2)=sprintf("\\scriptsize %.2f$",0.5*(T1+T2))
#titulo03(T1,T2)=sprintf("\\scriptsize %.2f$",0.5*(T1+T2))
infinito=5
set xtic add ("$\\infty$" infinito)
ymin=0.0; ymax=0.03
xmin=0.0; xmax=5
set yrange [ymin:ymax]
set label "$\\hl{//}$" at 4.5,ymin front
set label "$\\hl{//}$" at 4.5,ymax front
plot \
'BoundarResistance__N_100__T1_0.50__T2_0.30__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):5 w l ls  1       t "\\scriptsize $T_{L}-T_1$", \
'BoundarResistance__N_100__T1_0.70__T2_0.50__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):5 w l ls  2       notitle, \
'BoundarResistance__N_100__T1_0.90__T2_0.70__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):5 w l ls  3       notitle, \
'BoundarResistance__N_100__T1_0.50__T2_0.30__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):6 w l ls 11       t "\\scriptsize $T_{N}-T_R$", \
'BoundarResistance__N_100__T1_0.70__T2_0.50__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):6 w l ls 12       notitle, \
'BoundarResistance__N_100__T1_0.90__T2_0.70__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):6 w l ls 13       notitle, \
'BoundarResistance__N_100__T1_0.50__T2_0.30__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):5 w p ls  1 pt 65 t titulo01(0.50,0.30), \
'BoundarResistance__N_100__T1_0.70__T2_0.50__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):5 w p ls  2 pt 67 t titulo01(0.70,0.50), \
'BoundarResistance__N_100__T1_0.90__T2_0.70__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):5 w p ls  3 pt 69 t titulo01(0.90,0.70), \
'BoundarResistance__N_100__T1_0.50__T2_0.30__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):6 w p ls 11 pt 65 notitle, \
'BoundarResistance__N_100__T1_0.70__T2_0.50__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):6 w p ls 12 pt 67 notitle, \
'BoundarResistance__N_100__T1_0.90__T2_0.70__VAR_ALPHA.DAT' u ($4=='INFT'? infinito:$4):6 w p ls 13 pt 69 notitle#, \

set print "-"
print OUTFILENAME





#'Jumps__N_100__T1_0.90__T2_0.70__VAR_ALPHA.DAT' u 4:6 w lp#, \
