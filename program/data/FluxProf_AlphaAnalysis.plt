#!/usr/bin/gnuplot

OUTFILENAME="FluxProf_AlphaAnalysis.tex"
#set term epslatex size 8.6cm,7cm standalone color dl 3 header '\usepackage{grffile} \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
set term epslatex size 20cm,18cm standalone color dl 3 header '\usepackage{grffile} \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'
set out OUTFILENAME

#load "myown.pal"
load "setNum.pal"
#Npart T1 T2 alpha flux[1] flux[Npart/2] flux[Npart-1]
set xlabel "\\Large $\\alpha$"
infinito=5
ymin=0.0
ymax=0.003

set yrange [ymin:ymax]

set key bottom
set key spacing 1.5

set title "\\scriptsize $N=100, T=0.8, \\Delta T=0.2$" #at 2.5, 0.5*(ymin+ymax)
set label "$\\hl{//}$" at 4.5,ymin front
set label "$\\hl{//}$" at 4.5,ymax front
set ytics 0.001
set xtics add ("$\\infty$" infinito)


plot \
'FluxProf_AlphaAnalysis.DAT' u ($4=='INFT'? infinito:$4):( 1*$5 ) w lp ls 1 lw 2 pt 67 t "\\scriptsize $ \\mathcal{J}^{L,\\alpha}_{2}   $ ", \
'FluxProf_AlphaAnalysis.DAT' u ($4=='INFT'? infinito:$4):( 1*$6 ) w lp ls 3 lw 2 pt 68 t "\\scriptsize $ \\mathcal{J}^{L,\\alpha}_{N/2} $ ", \
'FluxProf_AlphaAnalysis.DAT' u ($4=='INFT'? infinito:$4):( 1*$7 ) w lp ls 2 lw 2 pt 69 t "\\scriptsize $ \\mathcal{J}^{L,\\alpha}_{N}   $ ", \
'FluxProf_AlphaAnalysis.DAT' u ($4=='INFT'? infinito:$4):(-1*$8 ) w lp ls 1 lw 2 pt 64 t "\\scriptsize $-\\mathcal{J}^{R,\\alpha}_{N-1} $ ", \
'FluxProf_AlphaAnalysis.DAT' u ($4=='INFT'? infinito:$4):(-1*$9 ) w lp ls 3 lw 2 pt 65 t "\\scriptsize $-\\mathcal{J}^{R,\\alpha}_{N/2} $ ", \
'FluxProf_AlphaAnalysis.DAT' u ($4=='INFT'? infinito:$4):(-1*$10) w lp ls 2 lw 2 pt 66 t "\\scriptsize $-\\mathcal{J}^{R,\\alpha}_{1}   $ "#, \


set print "-"
print OUTFILENAME
