#!/usr/bin/gnuplot

#set term tikz size 9,6 standalone
#set term epslatex size 8.6cm,7cm standalone color dl 3 header '\newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
##set format "\\Large %s"
OUTFILENAME="FLUX_vs_SLOPE__ALPHA.tex"
set out OUTFILENAME
set print "-"
print OUTFILENAME
load "setNum.pal"
#Npart alpha T1 T2 slope slope_std flux flux_std flux/slope kappa
set xlabel "\\Large $\\alpha$"
#set ylabel "\\Large $\\kappa$"
set ylabel "\\Large $J/ \\nabla T_{center}$"
#set key center right
#set xrange [1:5]
#set yrange [0.001:0.1]
ymin=0.1
ymax=2.0
#set yrange [ymin:ymax]

infinito=5
#unset ylabel # offset 2,0
#set y2range [0.0002:0.005]
#set autoscale y2
set xtics add ("$\\infty$" 5)
#set y2tics
#set ytics nomirror
#set label "$\\hl{//}$" at 4.5, ymin front
#set label "$\\hl{//}$" at 4.5, ymax front
set key bottom
#set logscale x
#set logscale y
plot \
'./SLOPE_FLUX__N_20__ALPHA.DAT'    u 5:7 w lp  ls 1 lw 3 ps 2 pt 65 axes x1y1 title "\\scriptsize $ 20$", \
'./SLOPE_FLUX__N_50__ALPHA.DAT'    u 5:7 w lp  ls 2 lw 3 ps 2 pt 66 axes x1y1 title "\\scriptsize $ 50$", \
'./SLOPE_FLUX__N_100__ALPHA.DAT'   u 5:7 w lp  ls 3 lw 3 ps 2 pt 68 axes x1y1 title "\\scriptsize $100$", \
'./SLOPE_FLUX__N_200__ALPHA.DAT'   u 5:7 w lp  ls 4 lw 3 ps 2 pt 69 axes x1y1 title "\\scriptsize $200$"#, \



