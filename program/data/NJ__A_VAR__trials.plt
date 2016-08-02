#!/usr/bin/gnuplot
strNpart="400"
strT1="0.90"
strT2="0.70"

OUTFILENAME=sprintf("NJ__N_%s__T1_%s__T2_%s__A_VAR__trials",strNpart,strT1,strT2)


#########################################################################
mpl_top    = 0.44 #inch  outer top margin, title goes here
mpl_bot    = 0.54 #inch  outer bottom margin, x label goes here
mpl_left   = 1.10 #inch  outer left margin, y label goes here
mpl_right  = 0.28 #inch  outer right margin, y2 label goes here
mpl_height = 3.2 #inch  height of individual plots
mpl_width  = 2.0*(7.0/5) #inch  width of individual plots
mpl_dx     = 0.65 #inch  inter-plot horizontal spacing
mpl_dy     = 0.2 #inch  inter-plot vertical spacing
mpl_ny     = 1   #number of rows
mpl_nx     = 1   #number of columns

# calculate full dimensions
xsize = mpl_left+mpl_right+(mpl_width*mpl_nx)+(mpl_nx-1)*mpl_dx
ysize = mpl_top+mpl_bot+(mpl_ny*mpl_height)+(mpl_ny-1)*mpl_dy

# placement functions
#   rows are numbered from bottom to top
bot(n) = (mpl_bot+(n-1)*mpl_height+(n-1)*mpl_dy)/ysize
top(n)  = 1-((mpl_top+(mpl_ny-n)*(mpl_height+mpl_dy))/ysize)
#   columns are numbered from left to right
left(n) = (mpl_left+(n-1)*mpl_width+(n-1)*mpl_dx)/xsize
right(n)  = 1-((mpl_right+(mpl_nx-n)*(mpl_width+mpl_dx))/xsize)



#set ter epslatex standalone color colortext 12 dl 1.5 size xsize,ysize #header "\\usepackage{cmbright}"
set term epslatex size xsize,ysize standalone color colortext 12 dl 3 header '\usepackage{grffile} \newcommand{\hl}[1]{\setlength{\fboxsep}{0.75pt}\colorbox{white}{#1}}'

set out sprintf("%s.tex",OUTFILENAME)

######################################################################




############# TEMPERATURE PROFILE ###########
r=1
c=1

set lmargin at screen left(c)
set rmargin at screen right(c)
set tmargin at screen top(r)
set bmargin at screen bot(r)

load "N_alpha.pal"
set title sprintf("$N=%s, T_L=%s, T_R=%s$", strNpart, strT1, strT2)

### X
xmin=0
xmax=10
#set xrange [xmin:xmax]
set xlabel "job id"


### Y
ymin=0
ymax=2
#set yrange [ymin:ymax]
set ylabel "$\\langle \\mathcal{J}^{L,\\alpha} \\rangle $"

arquivo001=sprintf("NJ__N_%s__T1_%s__T2_%s__A_VAR__trials.DAT",strNpart,strT1,strT2) 
titulo001(A)=sprintf("\\scriptsize $%s$",A)
plot \
arquivo001 \
   u 1:2 w lp ls 1  t titulo001("0.00") ,\
"" u 1:3 w lp ls 2  t titulo001("0.25"), \
"" u 1:4 w lp ls 3  t titulo001("0.50"), \
"" u 1:5 w lp ls 4  t titulo001("0.75"), \
"" u 1:6 w lp ls 5  t titulo001("1.00")#, \

set output
system(sprintf("latex %s.tex", OUTFILENAME))
system(sprintf("dvipdf %s.dvi", OUTFILENAME))
system('rm -f *.aux *dvi *tex *log *eps')
set print "-"
print sprintf("okular %s.pdf &",OUTFILENAME)

