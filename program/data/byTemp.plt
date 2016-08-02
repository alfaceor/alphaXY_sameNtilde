#!/usr/bin/gnuplot

set logscale y
titulo01(T2,T1)=sprintf("$T_1=%s, T_2=%s$",T2,T1)

plot \
'byTemp.DAT' i  1 u ($2=='INFT'? 5:$2):10 w lp t titulo01("0.50","0.30"), \
'byTemp.DAT' i  2 u ($2=='INFT'? 5:$2):10 w lp t titulo01("0.70","0.50"), \
'byTemp.DAT' i  3 u ($2=='INFT'? 5:$2):10 w lp t titulo01("0.81","0.79"), \
'byTemp.DAT' i  4 u ($2=='INFT'? 5:$2):10 w lp t titulo01("0.90","0.70"), \
'byTemp.DAT' i  5 u ($2=='INFT'? 5:$2):10 w lp t titulo01("0.95","0.65"), \
'byTemp.DAT' i  6 u ($2=='INFT'? 5:$2):10 w lp t titulo01("1.30","1.10"), \
'byTemp.DAT' i  7 u ($2=='INFT'? 5:$2):10 w lp t titulo01("1.90","1.70"), \
'byTemp.DAT' i  8 u ($2=='INFT'? 5:$2):10 w lp t titulo01("2.50","2.30")#, \


