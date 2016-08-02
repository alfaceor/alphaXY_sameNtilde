#!/usr/bin/gnuplot

#set term tikz size 9,6 standalone
set term epslatex size 8.6cm,7cm standalone color dl 3 header '\usepackage{grffile} \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
#set format "\\Large %s"
OUTFILENAME="SLOPE_FLUX__T1_0.90__T2_0.70__ALPHA.tex"
set out OUTFILENAME
set print "-"
print OUTFILENAME
load "setNum.pal"

set xlabel "\\Large $\\alpha$"
#set ylabel "\\Large $s$"
set key center right
ymin=-0.25
ymax=0.25

set xrange [0:5]
set yrange [ymin:ymax]

unset ylabel # offset 2,0
#set y2range [0.0002:0.005]
#set autoscale y2
set xtics add ("$\\infty$" 5)
#set y2tics
#set ytics nomirror
set label "$\\hl{//}$" at 4.5, ymin front
set label "$\\hl{//}$" at 4.5, ymax front
set label "$ NJ$"                  at 0.3,  0.15 front
set label "$ s_{bulk}$" at 0.3, -0.15 front

titulo001(Npart)=sprintf("\\scriptsize $%s$", Npart)
plot \
'./SLOPE_FLUX__N_20__T1_0.90__T2_0.70__ALPHA.DAT'   u ($2=='INFT'? 5:$2):5               w p  ls 1 lw 1 ps 1.0 pt 65  notitle, \
'./SLOPE_FLUX__N_50__T1_0.90__T2_0.70__ALPHA.DAT'   u ($2=='INFT'? 5:$2):5               w p  ls 1 lw 1 ps 1.0 pt 66  notitle, \
'./SLOPE_FLUX__N_100__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5               w p  ls 1 lw 1 ps 1.0 pt 67  notitle, \
'./SLOPE_FLUX__N_200__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5               w p  ls 1 lw 1 ps 1.0 pt 68  notitle, \
'./SLOPE_FLUX__N_400__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5               w p  ls 1 lw 1 ps 1.0 pt 69  notitle, \
'./SLOPE_FLUX__N_INFT__ALPHA.DAT'                   u ($2=='INFT'? 5:$2):5               w lp ls 1 lw 1 ps 1.0 pt 64  notitle, \
'./SLOPE_FLUX__N_20__T1_0.90__T2_0.70__ALPHA.DAT'   u ($2=='INFT'? 5:$2):5:6             w yerror  ls 1 lw 1 ps 1.0  notitle, \
'./SLOPE_FLUX__N_50__T1_0.90__T2_0.70__ALPHA.DAT'   u ($2=='INFT'? 5:$2):5:6             w yerror  ls 1 lw 1 ps 1.0  notitle, \
'./SLOPE_FLUX__N_100__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5:6             w yerror  ls 1 lw 1 ps 1.0  notitle, \
'./SLOPE_FLUX__N_200__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5:6             w yerror  ls 1 lw 1 ps 1.0  notitle, \
'./SLOPE_FLUX__N_400__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5:6             w yerror  ls 1 lw 1 ps 1.0  notitle, \
'./SLOPE_FLUX__N_INFT__ALPHA.DAT'                   u ($2=='INFT'? 5:$2):5:6             w yerror  ls 1 lw 1 ps 1.0  notitle, \
'./SLOPE_FLUX__N_20__T1_0.90__T2_0.70__ALPHA.DAT'   u ($2=='INFT'? 5:$2):($1*$7)         w p  ls 2 lw 2 ps 1.0 pt 65  t titulo001("  20"), \
'./SLOPE_FLUX__N_50__T1_0.90__T2_0.70__ALPHA.DAT'   u ($2=='INFT'? 5:$2):($1*$7)         w p  ls 2 lw 2 ps 1.0 pt 66  t titulo001("  50"), \
'./SLOPE_FLUX__N_100__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7)         w p  ls 2 lw 2 ps 1.0 pt 67  t titulo001(" 100"), \
'./SLOPE_FLUX__N_200__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7)         w p  ls 2 lw 2 ps 1.0 pt 68  t titulo001(" 200"), \
'./SLOPE_FLUX__N_400__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7)         w p  ls 2 lw 2 ps 1.0 pt 69  t titulo001(" 400"), \
'./SLOPE_FLUX__N_INFT__ALPHA.DAT'                   u ($2=='INFT'? 5:$2):($7)            w lp ls 2 lw 2 ps 1.0 pt 64  t titulo001("\\infty"), \
'./SLOPE_FLUX__N_20__T1_0.90__T2_0.70__ALPHA.DAT'   u ($2=='INFT'? 5:$2):($1*$7):($1*$8) w yerror  ls 2 lw 2 ps 1.0  notitle , \
'./SLOPE_FLUX__N_50__T1_0.90__T2_0.70__ALPHA.DAT'   u ($2=='INFT'? 5:$2):($1*$7):($1*$8) w yerror  ls 2 lw 2 ps 1.0  notitle , \
'./SLOPE_FLUX__N_100__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7):($1*$8) w yerror  ls 2 lw 2 ps 1.0  notitle , \
'./SLOPE_FLUX__N_200__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7):($1*$8) w yerror  ls 2 lw 2 ps 1.0  notitle #, \
'./SLOPE_FLUX__N_400__T1_0.90__T2_0.70__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7):($1*$8) w yerror  ls 2 lw 2 ps 1.0  notitle #, \
'./SLOPE_FLUX__N_INFT__ALPHA.DAT'                   u ($2=='INFT'? 5:$2):($7)            w yerror  ls 2 lw 2 ps 1.0  notitle #, \



#'./SLOPE_FLUX__N_20__ALPHA.DAT'   u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 65 axes x1y1 notitle, \
#'./SLOPE_FLUX__N_50__ALPHA.DAT'   u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 66 axes x1y1 notitle, \
#'./SLOPE_FLUX__N_100__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 68 axes x1y1 notitle, \
#'./SLOPE_FLUX__N_200__ALPHA.DAT'  u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 69 axes x1y1 notitle, \
#'./SLOPE_FLUX__N_INFT__ALPHA.DAT' u ($2=='INFT'? 5:$2):5             w p  ls 1 lw 3 ps 2 pt 64 axes x1y1 notitle, \
#
#
#'./SLOPE_FLUX__N_20__ALPHA.DAT'   u ($2=='INFT'? 5:$2):($1*$7)       w p  ls 2 lw 3 ps 2 pt 65 axes x1y1 t titulo001(" 20"), \
#'./SLOPE_FLUX__N_50__ALPHA.DAT'   u ($2=='INFT'? 5:$2):($1*$7)       w p  ls 2 lw 3 ps 2 pt 66 axes x1y1 t titulo001(" 50"), \
#'./SLOPE_FLUX__N_100__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7)       w p  ls 2 lw 3 ps 2 pt 68 axes x1y1 t titulo001("100"), \
#'./SLOPE_FLUX__N_200__ALPHA.DAT'  u ($2=='INFT'? 5:$2):($1*$7)       w p  ls 2 lw 3 ps 2 pt 69 axes x1y1 t titulo001("200"), \
#'./SLOPE_FLUX__N_INFT__ALPHA.DAT' u ($2=='INFT'? 5:$2):($7)          w p  ls 2 lw 2 ps 2 pt 64 axes x1y1 t titulo001("\\infty"), \

#./SLOPE_FLUX__N_20__T1_0.90__T2_0.70__ALPHA.DAT
#./SLOPE_FLUX__N_50__T1_0.90__T2_0.70__ALPHA.DAT
#./SLOPE_FLUX__N_100__T1_0.90__T2_0.70__ALPHA.DAT
#./SLOPE_FLUX__N_200__T1_0.90__T2_0.70__ALPHA.DAT
#./SLOPE_FLUX__N_400__T1_0.90__T2_0.70__ALPHA.DAT
